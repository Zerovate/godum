#pragma once
#include <scene/main/scene_tree.h>

class World : public SceneTree {
	GDCLASS(World, SceneTree);

protected:
	static void _bind_methods();

public:
	Vector<WeakRef> get_controllers() const;

private:
	Vector<WeakRef> controller_list;
};
