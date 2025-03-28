#include "register_types.h"

#include "godum.h"
#include "input/enhanced_input_map.h"
#include "input/input_device.h"
#include "input/input_player_component.h"
#include "player/local_player.h"
#include "player/player.h"
#include "player/player_component.h"

void initialize_godum_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(Godum);
	GDREGISTER_CLASS(PlayerComponent);
	GDREGISTER_CLASS(EnhancedInputMap);
	GDREGISTER_CLASS(InputPlayerComponent);
	GDREGISTER_CLASS(InputDevice);
	GDREGISTER_CLASS(Player);
	GDREGISTER_CLASS(LocalPlayer);
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