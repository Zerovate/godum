#pragma once
#include "core/component_holder.h"
#include "gi_component.h"

#ifdef GODUM_MUDULE
#include <core/object/ref_counted.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/ref_counted.hpp>
using namespace godot;
#endif

class LocalPlayer;

// 游戏实例，用于管理玩家、游戏设置等, 场景切换
class GameInstance : public Object, public ComponentHolder<GIComponent> {
	GDCLASS(GameInstance, Object);
	COMPONENT_HOLDER_IMPLEMENT(GIComponent);

private:
	static GameInstance *singleton;

public:
	static GameInstance *get_singleton();

protected:
	Vector<LocalPlayer *> local_players;

protected:
	static void _bind_methods();

private:
};
