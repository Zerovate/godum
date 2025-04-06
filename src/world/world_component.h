#pragma once
#include "core/component.h"

class WorldComponent : public Component {
	GDCLASS(WorldComponent, Component);

public:
	WorldComponent();

protected:
	static void _bind_methods();
};
