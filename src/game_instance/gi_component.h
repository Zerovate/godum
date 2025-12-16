#pragma once

#include "../core/component.h"

class GIComponent : public Component {
	GDCLASS(GIComponent, Component);

public:
	GIComponent();

private:
	void _on_registered();
	void _on_unregistered();

protected:
	static void _bind_methods();
};
