#pragma once

#include <godot_cpp/classes/object.hpp>
using namespace godot;

class EntityManager : public Object {
	GDCLASS(EntityManager, Object)

    static EntityManager *singleton;

public:
	static EntityManager *get_singleton();
};
