#pragma once
#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION

class Player;

class Controller : public Node {
	GDCLASS(Controller, Node);

public:
	Player *get_player() const;

protected:
	void _notification(int p_notification);

protected:
	static void _bind_methods();
};
