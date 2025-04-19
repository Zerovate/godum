#pragma once
#include "core/component.h"

class EntityProxy;

class EntityComponent : public Component {
	GDCLASS(EntityComponent, Component)
public:
	EntityComponent();
	~EntityComponent();

	Node *get_entity() const;
	void set_entity(Node *entity);

	EntityProxy *get_entity_proxy() const;

private:
	void _on_actor_changed(Node *prev_actor, Node *new_actor);

protected:
	static void _bind_methods();
};
