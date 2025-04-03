#include "entity_manager.h"

#include "entity_component.h"

ECM *ECM::singleton = nullptr;

ECM *ECM::get_singleton() {
	if (unlikely(singleton == nullptr)) {
		GDExtensionObjectPtr singleton_obj = internal::gdextension_interface_global_get_singleton(ECM::get_class_static()._native_ptr());
#ifdef DEBUG_ENABLED
		ERR_FAIL_NULL_V(singleton_obj, nullptr);
#endif // DEBUG_ENABLED
		singleton = reinterpret_cast<ECM *>(internal::gdextension_interface_object_get_instance_binding(singleton_obj, internal::token, &ECM::_gde_binding_callbacks));
#ifdef DEBUG_ENABLED
		ERR_FAIL_NULL_V(singleton, nullptr);
#endif // DEBUG_ENABLED
		if (likely(singleton)) {
			ClassDB::_register_engine_singleton(ECM::get_class_static(), singleton);
		}
	}
	return singleton;
}

bool ECM::register_component(Node *entity, EntityComponent *component) {
	if (!entity || !component) {
		return false;
	}
	if (m_components.has(component)) {
		// unregister component first
		unregister_component(component->get_actor(), component);
	} else {
		m_components.insert(component);
		m_entity_components[entity].insert(component);
	}

	return true;
}

bool ECM::unregister_component(Node *entity, EntityComponent *component) {
	if (!entity || !component) {
		return false;
	}
	ERR_FAIL_COND_V_MSG(!m_entity_components.has(entity), false, "node is not entity");
	m_components.erase(component);
	m_entity_components[entity].erase(component);
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
TypedArray<EntityComponent> ECM::get_components() const {
	TypedArray<EntityComponent> result;
	for (auto component : m_components) {
		result.append(component);
	}
	return result;
}

void ECM::_bind_methods() {
	ClassDB::bind_method(D_METHOD("register_component", "entity", "component"), &ECM::register_component);
	ClassDB::bind_method(D_METHOD("unregister_component", "entity", "component"), &ECM::unregister_component);
	ClassDB::bind_method(D_METHOD("entity_get_components", "entity"), &ECM::entity_get_components);
	ClassDB::bind_method(D_METHOD("entity_get_components_of_type", "entity", "type"), &ECM::entity_get_components_of_type);
	ClassDB::bind_method(D_METHOD("entity_get_first_component", "entity", "type"), &ECM::entity_get_first_component);
	ClassDB::bind_method(D_METHOD("get_components"), &ECM::get_components);
}
