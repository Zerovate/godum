#pragma once
#include "core/component.h"

#include <godot_cpp/classes/object.hpp>
using namespace godot;

class SessionGIComponent : public Component {
	GDCLASS(SessionGIComponent, Component);

public:
	// void HostSession();

	// void JoinSession();

protected:
	static void _bind_methods();
};
