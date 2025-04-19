#include "gi_component.h"

#include "game_instance.h"

#include <scene/main/scene_tree.h>
#include <scene/main/window.h>

GIComponent::GIComponent() {
	m_find_actor_by_tree = false;
	connect("registered", Callable(this, "_on_registered"));
	connect("unregistered", Callable(this, "_on_unregistered"));
}

void GIComponent::_on_registered() {
	SceneTree *scene_tree = Object::cast_to<SceneTree>(::OS::get_singleton()->get_main_loop());
	if (scene_tree) {
		scene_tree->get_root()->call_deferred("add_child", this);
	}
}

void GIComponent::_on_unregistered() {
	if (get_parent()) {
		get_parent()->call_deferred("remove_child", this);
	}
}

void GIComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_registered"), &GIComponent::_on_registered);
	ClassDB::bind_method(D_METHOD("_on_unregistered"), &GIComponent::_on_unregistered);
}
