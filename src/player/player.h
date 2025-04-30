#pragma once
#include "core/component_holder.h"
#include "player_component/player_component.h"

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION;

class EntityProxy;
class InputDevice;

class Player : public Node, public ComponentHolder<PlayerComponent> {
	GDCLASS(Player, Node);

public:
	COMPONENT_HOLDER_IMPLEMENT(PlayerComponent);

	enum Role {
		ROLE_None,
		ROLE_Local,
		ROLE_Remote
	};
	Role get_role() const { return m_role; }
	virtual void set_role(Role role) { m_role = role; }

	TypedArray<Node> get_pawns() const;
	bool register_pawn(EntityProxy *pawn);
	bool unregister_pawn(EntityProxy *pawn);

	Ref<InputDevice> get_input_device() const;
	void set_input_device(const Ref<InputDevice> &device);

public:
	void _enter_tree();

protected:
#ifdef GODUM_MODULE
	void _notification(int p_what);
#endif

protected:
	Role m_role = ROLE_None;
	Ref<InputDevice> m_input_device;

private:
	HashMap<StringName, HashSet<PlayerComponent *>> m_player_components_map;
	HashSet<EntityProxy *> m_pawns;

protected:
	static void _bind_methods();
};

VARIANT_ENUM_CAST(Player::Role);
