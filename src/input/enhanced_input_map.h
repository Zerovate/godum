#pragma once

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/object.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION

class EnhancedInputMap : public Object {
	GDCLASS(EnhancedInputMap, Object);

public:
	static bool bind_action(const StringName &p_action, const Callable &p_callback);

protected:
	static void _bind_methods();
};