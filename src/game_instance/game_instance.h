#pragma once
#include "core/component_holder.h"
#include "gi_component.h"

#ifdef GODUM_MUDULE
#include <core/object/ref_counted.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/scene_tree.hpp>
using namespace godot;
#endif

class LocalPlayer;
class WorldNode;

// 游戏实例，用于管理玩家、游戏设置等, 场景切换
class GameInstance : public Object, public ComponentHolder<GIComponent> {
	GDCLASS(GameInstance, Object);
	COMPONENT_HOLDER_IMPLEMENT(GIComponent);

private:
	static GameInstance *singleton;

public:
	static GameInstance *get_singleton();

	WorldNode *get_world() const;

protected:
	Vector<LocalPlayer *> local_players;

private:
	WorldNode *world = nullptr;

protected:
	static void _bind_methods();
};
