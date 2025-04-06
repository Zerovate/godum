#include "game_instance.h"
#include "world/world_node.h"

GameInstance *GameInstance::singleton = nullptr;

GameInstance *GameInstance::get_singleton() {
	if (unlikely(singleton == nullptr)) {
		GDExtensionObjectPtr singleton_obj = internal::gdextension_interface_global_get_singleton(GameInstance::get_class_static()._native_ptr());
#ifdef DEBUG_ENABLED
		ERR_FAIL_NULL_V(singleton_obj, nullptr);
#endif // DEBUG_ENABLED
		singleton = reinterpret_cast<GameInstance *>(internal::gdextension_interface_object_get_instance_binding(singleton_obj, internal::token, &GameInstance::_gde_binding_callbacks));
#ifdef DEBUG_ENABLED
		ERR_FAIL_NULL_V(singleton, nullptr);
#endif // DEBUG_ENABLED
		if (likely(singleton)) {
			ClassDB::_register_engine_singleton(GameInstance::get_class_static(), singleton);
		}
	}
	return singleton;
}

WorldNode *GameInstance::get_world() const {
	return world;
}

void GameInstance::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(GameInstance);
}