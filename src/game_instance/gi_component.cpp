#include "gi_component.h"

#include <scene/main/window.h>

GIComponent::GIComponent() {
	m_allowed_actor_types = {
		"GameInstance"
	};
	connect("registered", Callable(this, "_on_registered"));
	connect("unregistered", Callable(this, "_on_unregistered"));
}

void GIComponent::_on_registered() {
	get_tree()->get_root()->add_child(this);
}

void GIComponent::_on_unregistered() {
	get_tree()->get_root()->remove_child(this);
}

void GIComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_registered"), &GIComponent::_on_registered);
	ClassDB::bind_method(D_METHOD("_on_unregistered"), &GIComponent::_on_unregistered);
}
