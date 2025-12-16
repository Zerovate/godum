#pragma once
#include "../core/component.h"

class WorldNode;

class WorldComponent : public Component {
	GDCLASS(WorldComponent, Component);

public:
	WorldComponent();
	~WorldComponent();

	WorldNode *get_world() const;
	void set_world(WorldNode *world);

	virtual PackedStringArray _get_configuration_warnings() const;

private:
	void on_actor_changed(Node *prev_actor, Node *new_actor);

protected:
	static void _bind_methods();
};
