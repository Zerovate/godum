#pragma once
#include "core/component.h"

class WorldNode;

class WorldComponent : public Component {
	GDCLASS(WorldComponent, Component);

public:
	WorldComponent();

	WorldNode *get_world() const;
	void set_world(WorldNode *world);

protected:
	static void _bind_methods();
};
