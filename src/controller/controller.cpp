#include "controller.h"
#include "player/player.h"

Player *Controller::get_player() const {
	return Object::cast_to<Player>(get_parent());
}

void Controller::_notification(int p_notification) {
	switch (p_notification) {
		case Node::NOTIFICATION_READY:
			print_line("Controller Ready");
			break;
		case Node::NOTIFICATION_ENTER_TREE:
			print_line("Controller Enter Tree");
			break;
		case Node::NOTIFICATION_PARENTED:
			print_line("Controller Parented");
			if (!get_parent()->is_class("Player")) {
				ERR_PRINT("Controller must be a child of Player");
				queue_free();
			}
			break;
		case Node::NOTIFICATION_SCENE_INSTANTIATED:
			print_line("Controller Scene Instantiated");
			break;
		case Node::NOTIFICATION_POST_ENTER_TREE:
			print_line("Controller Post Enter Tree");
			break;
	}
}

void Controller::_bind_methods() {}
