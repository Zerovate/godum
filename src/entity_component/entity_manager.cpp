#include "entity_manager.h"

#include "godot_cpp/core/class_db.hpp"

EntityManager *EntityManager::singleton = nullptr;

EntityManager* EntityManager::get_singleton() {
	if (unlikely(singleton == nullptr)) {
		GDExtensionObjectPtr singleton_obj = internal::gdextension_interface_global_get_singleton(EntityManager::get_class_static()._native_ptr());
#ifdef DEBUG_ENABLED
		ERR_FAIL_NULL_V(singleton_obj, nullptr);
#endif // DEBUG_ENABLED
		singleton = reinterpret_cast<EntityManager *>(internal::gdextension_interface_object_get_instance_binding(singleton_obj, internal::token, &EntityManager::_gde_binding_callbacks));
#ifdef DEBUG_ENABLED
		ERR_FAIL_NULL_V(singleton, nullptr);
#endif // DEBUG_ENABLED
		if (likely(singleton)) {
			ClassDB::_register_engine_singleton(EntityManager::get_class_static(), singleton);
		}
	}
	return singleton;
}
