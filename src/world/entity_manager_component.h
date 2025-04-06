#pragma once
#include "world_component.h"

class EntityManagerComponent : public WorldComponent {
	GDCLASS(EntityManagerComponent, WorldComponent);

public:
protected:
	static void _bind_methods();
};
