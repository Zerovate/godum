#include "entity_component_manager.h"

#include "entity_component.h"

ECM *ECM::singleton = nullptr;

ECM::ECM() {
	singleton = this;
}

ECM *ECM::get_singleton() {
	return singleton;
}

bool ECM::register_component(Node *entity, EntityComponent *component) {
	if (!entity || !component) {
		return false;
	}
	if (!entity->is_in_group("entity")) {
		const bool is_in_editor = Engine::get_singleton()->is_editor_hint();
		if (is_in_editor) {
			entity->add_to_group("entity");
		} else {
			print_error(vformat("entity %s is not added to group 'entity'", entity->get_path()));
		}
	}
	if (m_components.has(component->get_class_name()) && m_components[component->get_class_name()].has(component)) {
		// unregister component first
		unregister_component(component->get_actor(), component);
	} else {
		m_components[component->get_class_name()].push_back(component);
		m_entity_components[entity].insert(component);
	}

	return true;
}

bool ECM::unregister_component(Node *entity, EntityComponent *component) {
	if (!entity || !component) {
		return false;
	}
	ERR_FAIL_COND_V_MSG(!m_entity_components.has(entity), false, "node is not entity");
	m_components[component->get_class_name()].erase(component);
	auto &components = m_entity_components.get(entity);
	components.erase(component);

	if (components.is_empty()) {
		m_entity_components.erase(entity);
		entity->remove_from_group("entity");
	}
	return true;
}

TypedArray<EntityComponent> ECM::entity_get_components(Node *entity) const {
	return entity_get_components_of_type(entity, "");
}

TypedArray<EntityComponent> ECM::entity_get_components_of_type(Node *entity, const StringName &type) const {
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

EntityComponent *ECM::entity_get_first_component(Node *entity, const StringName &type) const {
	ERR_FAIL_COND_V_MSG(!m_entity_components.has(entity), {}, "node is not entity");
	for (auto component : m_entity_components.get(entity)) {
		if (component->is_class(type)) {
			return component;
		}
	}
	return nullptr;
}

// component iterators.
TypedArray<EntityComponent> ECM::get_components(const StringName &p_name) const {
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

void ECM::_bind_methods() {
	ClassDB::bind_method(D_METHOD("register_component", "entity", "component"), &ECM::register_component);
	ClassDB::bind_method(D_METHOD("unregister_component", "entity", "component"), &ECM::unregister_component);
	ClassDB::bind_method(D_METHOD("entity_get_components", "entity"), &ECM::entity_get_components);
	ClassDB::bind_method(D_METHOD("entity_get_components_of_type", "entity", "type"), &ECM::entity_get_components_of_type);
	ClassDB::bind_method(D_METHOD("entity_get_first_component", "entity", "type"), &ECM::entity_get_first_component);
	ClassDB::bind_method(D_METHOD("get_components", "name"), &ECM::get_components, DEFVAL(""));
}
