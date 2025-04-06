#pragma once
#include "core/component_holder.h"

#include "world_component.h"

#include <godot_cpp/classes/node2d.hpp>
using namespace godot;

class WorldNode : public Node, public ComponentHolder<WorldComponent> {
	GDCLASS(WorldNode, Node)
	COMPONENT_HOLDER_IMPLEMENT(WorldComponent);

public:
	WorldNode();

protected:
	static void _bind_methods();
};
