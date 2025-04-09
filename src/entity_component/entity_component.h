#pragma once
#include "core/component.h"

class EntityComponent : public Component {
	GDCLASS(EntityComponent, Component)
public:
	EntityComponent();
	~EntityComponent();

private:
	void _on_actor_changed(Node* prev_actor, Node* new_actor);

protected:
	static void _bind_methods();
};
