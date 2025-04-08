#ifndef STEAMPEER_REGISTER_TYPES_H
#define STEAMPEER_REGISTER_TYPES_H
#ifdef GODUM_MODULE
#include "modules/register_module_types.h"
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include "godot_cpp/core/class_db.hpp"
using namespace godot;
#endif // GODUM_GDEXTENSION

void initialize_steam_multiplayer_peer(ModuleInitializationLevel level);
void uninitialize_steam_multiplayer_peer(ModuleInitializationLevel level);

#endif