#pragma once
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Player;

class Godum : public Object {
	GDCLASS(Godum, Object);

public:
	static Player *get_player(Node *node);

protected:
	static void _bind_methods();
};
