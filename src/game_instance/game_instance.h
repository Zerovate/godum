#pragma once
#include "../core/component_holder.h"
#include "gi_component.h"

#ifdef GODUM_MODULE
#include <core/object/object.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/object.hpp>
using namespace godot;
#endif

class WorldNode;

// 游戏实例，用于管理玩家、游戏设置等, 场景切换
class GameInstance : public Object, public ComponentHolder<GIComponent> {
	GDCLASS(GameInstance, Object);
	COMPONENT_HOLDER_IMPLEMENT(GIComponent);

private:
	static GameInstance *singleton;

public:
	GameInstance();
	static GameInstance *get_singleton();

	WorldNode *get_world() const;
	void set_world(WorldNode* world);

private:
	WorldNode *m_world = nullptr;

protected:
	static void _bind_methods();
};
