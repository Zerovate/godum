#include "world_node.h"
#include "../game_instance/game_instance.h"

WorldNode::WorldNode() {
}

void WorldNode::_enter_tree() {
	GameInstance().get_singleton()->set_world(this);
}

void WorldNode::_exit_tree() {
	if (GameInstance().get_singleton()->get_world() == this) {
		GameInstance().get_singleton()->set_world(nullptr);
	}
}

#ifdef GODUM_MODULE
void WorldNode::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_enter_tree();
		} break;
		case NOTIFICATION_EXIT_TREE: {
			_exit_tree();
		} break;
	}
}
#endif

void WorldNode::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(WorldNode);
}
