#include "controller.h"
#include "player/player.h"

Player *Controller::get_player() const {
	return Object::cast_to<Player>(get_parent());
}

void Controller::_notification(int p_notification) {
	switch (p_notification) {
		case Node::NOTIFICATION_PARENTED:
			if (!get_parent()->is_class("Player")) {
				queue_free();
				ERR_PRINT("Controller must be a child of Player");
			}
			break;
	}
}

void Controller::_bind_methods() {}
