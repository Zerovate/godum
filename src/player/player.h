#pragma once

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION;

class PlayerComponent;

class Player : public Node {
	GDCLASS(Player, Node);

public:
	Player();
	~Player();

	TypedArray<PlayerComponent> get_controllers(const StringName &name) const;
	_FORCE_INLINE_ bool try_add_player_component(Node *node);
	_FORCE_INLINE_ bool try_erase_player_controller(Node *node);

private:
	Vector<PlayerComponent *> m_player_components;

protected:
	static void _bind_methods();
};
