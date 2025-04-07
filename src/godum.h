#pragma once

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif

#ifdef GODUM_EXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif

class Player;

class Godum : public Object {
	GDCLASS(Godum, Object);

public:
	static Player *get_player(Node *node);

protected:
	static void _bind_methods();
};
