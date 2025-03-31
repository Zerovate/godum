#pragma once

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION;

class PlayerComponent;

class Player : public Node {
	GDCLASS(Player, Node);

public:
	Player();
	~Player();

	TypedArray<PlayerComponent> get_player_components(const StringName &name) const;
	bool try_bind_player_component(Node *node);
	bool try_unbind_player_controller(Node *node);

private:
	HashMap<StringName, HashSet<PlayerComponent *>> m_player_components_map;

protected:
	static void _bind_methods();
};
