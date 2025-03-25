#pragma once

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION;

class Player : public Node {
	GDCLASS(Player, Node);

public:
	static void _bind_methods() {}
};
