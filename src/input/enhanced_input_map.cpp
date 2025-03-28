#include "enhanced_input_map.h"

#include "godum.h"
#include "input/input_player_component.h"
#include "player/player.h"

bool EnhancedInputMap::bind_action(const StringName &p_action, const Callable &p_callback) {
	bool success = false;

	Player *player = Godum::get_player(Object::cast_to<Node>(p_callback.get_object()));
	auto controllers = player->get_player_components("InputPlayerComponent");
	for (auto idx = 0; idx < controllers.size(); idx++) {
		InputPlayerComponent *ctrl = Object::cast_to<InputPlayerComponent>(controllers[idx]);

		ERR_CONTINUE(!ctrl);

		if (ctrl->has_signal(p_action)) {
			ctrl->connect(p_action, p_callback);
			success = true;
		}
	}
	return success;
}

void EnhancedInputMap::_bind_methods() {
	ClassDB::bind_static_method("EnhancedInputMap", D_METHOD("bind_action", "action", "callback"), &EnhancedInputMap::bind_action);
}
