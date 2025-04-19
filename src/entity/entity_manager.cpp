#include "entity_manager.h"

#include "entity_component.h"
#include "entity_proxy.h"

EntityManager *EntityManager::singleton = nullptr;

EntityManager::EntityManager() {
	singleton = this;
}

EntityManager *EntityManager::get_singleton() {
	return singleton;
}

bool EntityManager::is_entity_registered(Node *entity) const {
	return m_entity_proxies.has(entity);
}

EntityProxy *EntityManager::get_entity_proxy(Node *entity) const {
	if (is_entity_registered(entity)) {
		return m_entity_proxies[entity];
	}
	return nullptr;
}

bool EntityManager::register_entity(Node *entity) {
	if (!entity) {
		return false;
	}
	if (is_entity_registered(entity)) {
		return true;
	}
	EntityProxy *proxy = memnew(EntityProxy(entity));
	m_entity_proxies[entity] = proxy;
	return true;
}

bool EntityManager::unregister_entity(Node *entity) {
	if (!entity) {
		return false;
	}
	if (is_entity_registered(entity)) {
		EntityProxy *proxy = m_entity_proxies[entity];
		m_entity_proxies.erase(entity);
		memdelete(proxy);
	}
	return true;
}

bool EntityManager::register_component(Node *entity, EntityComponent *component) {
	if (!entity || !component) {
		return false;
	}
	register_entity(entity);
	if (m_components.has(component->get_class_name()) && m_components[component->get_class_name()].has(component)) {
		// unregister component first
		unregister_component(component->get_actor(), component);
	} else {
		m_components[component->get_class_name()].push_back(component);
		m_entity_components[entity].insert(component);
	}

	return true;
}

bool EntityManager::unregister_component(Node *entity, EntityComponent *component) {
	if (!entity || !component) {
		return false;
	}
	ERR_FAIL_COND_V_MSG(!m_entity_components.has(entity), false, "node is not entity");
	m_components[component->get_class_name()].erase(component);
	auto &components = m_entity_components.get(entity);
	components.erase(component);

	if (components.is_empty()) {
		m_entity_components.erase(entity);
		unregister_entity(entity);
	}
	return true;
}

TypedArray<EntityComponent> EntityManager::entity_get_components(Node *entity) const {
	return entity_get_components_of_type(entity, "");
}

TypedArray<EntityComponent> EntityManager::entity_get_components_of_type(Node *entity, const StringName &type) const {
	ERR_FAIL_COND_V_MSG(!m_entity_components.has(entity), {}, "node is not entity");
	TypedArray<EntityComponent> result;
	for (auto component : m_entity_components.get(entity)) {
		if (!type.is_empty() && !component->is_class(type)) {
			continue;
		}
		result.append(component);
	}
	return result;
}

EntityComponent *EntityManager::entity_get_first_component(Node *entity, const StringName &type) const {
	ERR_FAIL_COND_V_MSG(!m_entity_components.has(entity), {}, "node is not entity");
	for (auto component : m_entity_components.get(entity)) {
		if (component->is_class(type)) {
			return component;
		}
	}
	return nullptr;
}

// component iterators.
TypedArray<EntityComponent> EntityManager::get_components(const StringName &p_name) const {
	TypedArray<EntityComponent> result;
	if (p_name != "") {
		for (auto component : m_components[p_name]) {
			result.append(component);
		}
	} else {
		for (auto pair : m_components) {
			for (auto component : pair.value) {
				result.append(component);
			}
		}
	}
	return result;
}

void EntityManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("is_entity_registered", "entity"), &EntityManager::is_entity_registered);
	ClassDB::bind_method(D_METHOD("get_entity_proxy", "entity"), &EntityManager::get_entity_proxy);
	ClassDB::bind_method(D_METHOD("register_entity", "entity"), &EntityManager::register_entity);

	ClassDB::bind_method(D_METHOD("register_component", "entity", "component"), &EntityManager::register_component);
	ClassDB::bind_method(D_METHOD("unregister_component", "entity", "component"), &EntityManager::unregister_component);

	ClassDB::bind_method(D_METHOD("entity_get_components", "entity"), &EntityManager::entity_get_components);
	ClassDB::bind_method(D_METHOD("entity_get_components_of_type", "entity", "type"), &EntityManager::entity_get_components_of_type);
	ClassDB::bind_method(D_METHOD("entity_get_first_component", "entity", "type"), &EntityManager::entity_get_first_component);
	ClassDB::bind_method(D_METHOD("get_components", "name"), &EntityManager::get_components, DEFVAL(""));
}
