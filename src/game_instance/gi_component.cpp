#include "gi_component.h"

GIComponent::GIComponent() {
	m_allowed_actor_types = {
		"GameInstance"
	};
}

void GIComponent::_bind_methods() {
}
