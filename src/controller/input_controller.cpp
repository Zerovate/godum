#include "input_controller.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/signal.hpp>

void InputController::_notification(int p_what) {
	switch (p_what) {
		case Node::NOTIFICATION_PROCESS:
			// on_process(get_process_delta_time());
			break;
		case Node::NOTIFICATION_READY:
			set_process(true);
			break;
	}
}

// void InputController::on_process(double p_delta) {
// 	if (!Engine::get_singleton()->is_editor_hint()) {
// 		InputMap *input_map = InputMap::get_singleton();
// 	}
// }

void InputController::_input(const Ref<InputEvent> &p_event) {
}

void InputController::_bind_methods() {
}