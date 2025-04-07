#pragma once
#include "core/component_holder.h"

#include "world_component.h"

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif

class WorldNode : public Node, public ComponentHolder<WorldComponent> {
	GDCLASS(WorldNode, Node)
	COMPONENT_HOLDER_IMPLEMENT(WorldComponent);

public:
	WorldNode();

protected:
	static void _bind_methods();
};
