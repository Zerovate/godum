#include "input_player_component.h"

#include "input/input_device_pc.h"
#include "player/player.h"

#ifdef GODUM_MODULE
#include <core/input/input_map.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/signal.hpp>
#endif // GODUM_GDEXTENSION

InputPlayerComponent::InputPlayerComponent() {
	// input player component only support for local players.
	m_support_actor_types = { "Player" };
	connect("player_changed", Callable(this, "_on_player_changed"));
}

void InputPlayerComponent::register_device_actions(TypedArray<StringName> p_actions) {
	InputMap *input_map = InputMap::get_singleton();

	for (String action : p_actions) {
		ERR_CONTINUE_EDMSG(!input_map->has_action(action),
				vformat("InputPlayerComponent::register_device_actions: action %s not found in InputMap", action));
		ERR_CONTINUE_EDMSG(action.ends_with("_keyboard") || action.ends_with("_joypad"),
				vformat("InputPlayerComponent::register_device_actions: action %s ends with _keyboard or _joypad", action));
		if (m_device_action_map.has(action)) {
			continue;
		}
		TypedArray<InputEvent> events = input_map->call("action_get_events", action);
		TypedArray<InputEvent> filtered_events = _filter_events_by_device(events);
		if (filtered_events.is_empty()) {
			continue;
		}
		StringName action_ext = _action_with_ext(action);
		if (action_ext != action && !input_map->has_action(action_ext)) {
			input_map->add_action(action_ext);
			for (int j = 0; j < filtered_events.size(); j++) {
				input_map->action_add_event(action_ext, filtered_events[j]);
			}
			print_line("InputMap add action: ", action, "-> ", action_ext);
		}
		m_device_action_map[action] = action_ext;
	}
}

void InputPlayerComponent::unregister_device_actions(TypedArray<StringName> p_actions) {
	for (StringName action : p_actions) {
		ERR_CONTINUE_EDMSG(!m_device_action_map.has(action),
				vformat("InputPlayerComponent::unregister_device_actions: action %s not found in built_in_action_map", action));
		m_device_action_map.erase(action);
	}
}

StringName InputPlayerComponent::get_device_action(const StringName &p_action) const {
	return m_device_action_map.has(p_action) ? m_device_action_map[p_action] : "";
}

Ref<InputDevice> InputPlayerComponent::_get_device() const {
	Player *player = get_player();
	if (!player) {
		return nullptr;
	}
	if (!player->get_role() == Player::Role::ROLE_Local) {
		return nullptr;
	}
	InputDevicePC *input_device_pc = Object::cast_to<InputDevicePC>(player->get_component("InputDevicePC"));
	return input_device_pc->get_input_device();
}

void InputPlayerComponent::_on_player_changed(Player *p_prev_player, Player *p_new_player) {
	if (p_prev_player) {
		InputDevicePC *input_device_pc = Object::cast_to<InputDevicePC>(p_prev_player->get_component("InputDevicePC"));
		if (input_device_pc) {
			input_device_pc->disconnect("input_device_changed", Callable(this, "_on_input_device_changed"));
		}
	}
	if (p_new_player) {
		InputDevicePC *new_input_device_pc = Object::cast_to<InputDevicePC>(p_new_player->get_component("InputDevicePC"));
		if (new_input_device_pc) {
			new_input_device_pc->connect("input_device_changed", Callable(this, "_on_input_device_changed"));
		}
	}
	_on_input_device_changed();
}

void InputPlayerComponent::_on_input_device_changed() {
	TypedArray<StringName> active_actions;
	for (auto pair : m_device_action_map) {
		active_actions.push_back(pair.key);
	}
	unregister_device_actions(active_actions);
	register_device_actions(active_actions);
}

StringName InputPlayerComponent::_action_with_ext(const StringName &p_action) const {
	Ref<InputDevice> device = _get_device();
	if (device.is_null() || device->get_type() == InputDevice::DEVICETYPE_ALL) {
		return p_action;
	}
	switch (device->get_type()) {
		case InputDevice::DeviceType::DEVICETYPE_KEYBOARD:
			return String(p_action) + "_keyboard";
		case InputDevice::DeviceType::DEVICETYPE_JOYPAD:
			return String(p_action) + "_" + itos(device->get_id()) + "_joypad";
		default:
			break;
	}
	return p_action;
}

TypedArray<InputEvent> InputPlayerComponent::_filter_events_by_device(const TypedArray<InputEvent> &p_events) {
	Ref<InputDevice> device = _get_device();
	if (device.is_null() || device->get_type() == InputDevice::DEVICETYPE_ALL) {
		return p_events;
	}
	TypedArray<InputEvent> filtered_events;
	for (int i = 0; i < p_events.size(); i++) {
		Ref<InputEvent> event = p_events[i];
		switch (device->get_type()) {
			case InputDevice::DEVICETYPE_KEYBOARD:
				if (event->is_class("InputEventKey") || event->is_class("InputEventMouse")) {
					filtered_events.push_back(event);
				}
				break;
			case InputDevice::DEVICETYPE_JOYPAD:
				if (event->is_class("InputEventJoypadButton") || event->is_class("InputEventJoypadMotion")) {
					if (event->get_device() == device->get_id() || event->get_device() == InputEvent::DEVICE_ID_EMULATION || device->get_id() == InputEvent::DEVICE_ID_EMULATION) {
						event->set_device(device->get_id());
						filtered_events.push_back(event);
					}
				}
				break;
			default:
				break;
		}
	}
	return filtered_events;
}

void InputPlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("register_device_actions", "actions"), &InputPlayerComponent::register_device_actions);
	ClassDB::bind_method(D_METHOD("unregister_device_actions", "actions"), &InputPlayerComponent::unregister_device_actions);
	ClassDB::bind_method(D_METHOD("get_device_action", "action"), &InputPlayerComponent::get_device_action);

	ClassDB::bind_method(D_METHOD("_on_player_changed"), &InputPlayerComponent::_on_player_changed);
	ClassDB::bind_method(D_METHOD("_on_input_device_changed"), &InputPlayerComponent::_on_input_device_changed);
}