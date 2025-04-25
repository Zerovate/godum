#include "register_types.h"

#ifdef GODUM_MODULE
#include <core/core_bind.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/engine.hpp>
#endif

#include "core/component.h"
#include "entity/entity_component.h"
#include "entity/entity_manager.h"
#include "entity/entity_proxy.h"
#include "game_instance/game_instance.h"
#include "game_instance/gi_component.h"
#include "game_instance/session_gi_component.h"
#include "input/enhanced_input_map.h"
#include "input/input_device.h"
#include "player/local_player.h"
#include "player/net_player.h"
#include "player/player.h"
#include "player_component/input_player_component.h"
#include "player_component/player_component.h"
#ifdef GODUM_SUPPORT_STEAM
#include "steam_multiplayer_peer/register_types.h"
#endif
#include "world/world_component.h"
#include "world/world_node.h"

static GameInstance *_game_instance = nullptr;
static EntityManager *_entity_component_manager = nullptr;

void initialize_godum_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
#ifdef GODUM_SUPPORT_STEAM
	initialize_steam_multiplayer_peer(p_level);
#endif
	GDREGISTER_CLASS(Component);

	GDREGISTER_CLASS(EntityManager);
	GDREGISTER_CLASS(EntityComponent);
	GDREGISTER_CLASS(EntityProxy);

	GDREGISTER_CLASS(GameInstance);
	GDREGISTER_CLASS(GIComponent);
	GDREGISTER_CLASS(SessionGIComponent);

	GDREGISTER_CLASS(EnhancedInputMap);
	GDREGISTER_CLASS(InputDevice);

	GDREGISTER_CLASS(Player);

	GDREGISTER_CLASS(PlayerComponent);
	GDREGISTER_CLASS(InputPlayerComponent);

	GDREGISTER_CLASS(WorldComponent);
	GDREGISTER_CLASS(WorldNode);

	_entity_component_manager = memnew(EntityManager);
	_game_instance = memnew(GameInstance);
#ifdef GODUM_MODULE
	Engine::get_singleton()->add_singleton(Engine::Singleton("GameInstance", GameInstance::get_singleton()));
	Engine::get_singleton()->add_singleton(Engine::Singleton("EntityManager", EntityManager::get_singleton()));
#elif GODUM_GDEXTENSION
	Engine::get_singleton()->register_singleton("GameInstance", GameInstance::get_singleton());
	Engine::get_singleton()->register_singleton("EntityManager", EntityManager::get_singleton());
#endif
}

void uninitialize_godum_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
#ifdef GODUM_SUPPORT_STEAM
	uninitialize_steam_multiplayer_peer(p_level);
#endif
	memdelete(_game_instance);
	memdelete(_entity_component_manager);
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