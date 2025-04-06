#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
using namespace godot;

class SteamConnection : public RefCounted {
	GDCLASS(SteamConnection, RefCounted);

public:
protected:
	static void _bind_methods();
};
