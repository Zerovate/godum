#pragma once

#include "core/component.h"

class GIComponent : public Component {
	GDCLASS(GIComponent, Component);

public:
	GIComponent();

protected:
	static void _bind_methods();
};
