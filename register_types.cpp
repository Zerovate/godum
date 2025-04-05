#include "register_types.h"

#include <godot_cpp/classes/engine.hpp>

#include "godum.h"

#include "core/component.h"
#include "entity_component/entity_component.h"
#include "entity_component/entity_component_manager.h"
#include "game_instance/game_instance.h"
#include "game_instance/session_gi_component.h"
#include "input/enhanced_input_map.h"
#include "input/input_device.h"
#include "player/local_player.h"
#include "player/net_player.h"
#include "player/player.h"
#include "player_component/input_player_component.h"
#include "player_component/player_component.h"

void initialize_godum_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(Godum);
	GDREGISTER_CLASS(Component);
	GDREGISTER_CLASS(EntityComponent);
	GDREGISTER_CLASS(SessionGIComponent);
	GDREGISTER_CLASS(EnhancedInputMap);
	GDREGISTER_CLASS(InputDevice);
	GDREGISTER_CLASS(InputPlayerComponent);
	GDREGISTER_ABSTRACT_CLASS(Player);
	GDREGISTER_CLASS(LocalPlayer);
	GDREGISTER_CLASS(NetPlayer);
	GDREGISTER_ABSTRACT_CLASS(PlayerComponent);

#ifdef LIMBOAI_MODULE
	Engine::get_singleton()->add_singleton(Engine::Singleton("ECM", ECM::get_singleton()));
#elif GODUM_GDEXTENSION
	Engine::get_singleton()->register_singleton("GameInstance", GameInstance::get_singleton());
	Engine::get_singleton()->register_singleton("ECM", ECM::get_singleton());
#endif
}

void uninitialize_godum_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

#ifdef GODUM_GDEXTENSION
extern "C" {
GDExtensionBool GDE_EXPORT godum_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_godum_module);
	init_obj.register_terminator(uninitialize_godum_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
#endif // GODUM_GDEXTENSION