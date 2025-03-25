#pragma once
#include <core/object/ref_counted.h>

class LocalPlayer;

class GameInstance : public Object {
	GDCLASS(GameInstance, Object);

public:
	static GameInstance *get_singleton();

protected:
	Vector<Ref<LocalPlayer>> local_players;

protected:
	static void _bind_methods();
};
