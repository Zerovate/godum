#pragma once
#ifdef GODUM_MODULE
#include "modules/register_module_types.h"
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include "godot_cpp/core/class_db.hpp"
using namespace godot;
#endif // GODUM_GDEXTENSION

void initialize_godum_module(ModuleInitializationLevel p_level);
void uninitialize_godum_module(ModuleInitializationLevel p_level);
