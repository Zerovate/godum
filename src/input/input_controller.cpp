#include "input_controller.h"

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/signal.hpp>
#endif // GODUM_GDEXTENSION

void InputController::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	_setup_device_actions();
}

void InputController::set_device(const Ref<InputDevice> &p_device) {
	if (m_device == p_device) {
		return;
	}
	m_device = p_device;
	if (!Engine::get_singleton()->is_editor_hint()) {
		_setup_device_actions();
	}
}

void InputController::_setup_device_actions() {
	InputMap *input_map = InputMap::get_singleton();

	// remove all actions created before.
	if (!m_built_in_action_map.is_empty()) {
		for (auto action : m_built_in_action_map) {
			input_map->erase_action(action.key);
		}
		m_built_in_action_map.clear();
	}

	// add new actions.
	TypedArray<StringName> actions = input_map->get_actions();
	for (int i = 0; i < actions.size(); i++) {
		StringName action = actions[i];
		if (action.begins_with("ui_")) {
			continue;
		}
		TypedArray<InputEvent> events = input_map->action_get_events(action);
		TypedArray<InputEvent> filtered_events = _filter_events_by_device(events);
		if (filtered_events.is_empty()) {
			continue;
		}
		auto action_ext = _action_with_ext(action);
		if (action_ext != action) {
			input_map->add_action(action_ext);
			for (int j = 0; j < filtered_events.size(); j++) {
				input_map->action_add_event(action_ext, filtered_events[j]);
			}
		}
		m_built_in_action_map[action] = action_ext;
	}
}

StringName InputController::_action_with_ext(const StringName &p_action) const {
	if (m_device.is_valid()) {
		switch (m_device->get_type()) {
			case InputDevice::DeviceType::DEVICETYPE_KEYBOARD:
				return String(p_action) + "_k";
			case InputDevice::DeviceType::DEVICETYPE_JOYPAD:
				return String(p_action) + "_j_" + itos(m_device->get_id());
		}
	}
	return p_action;
}

TypedArray<InputEvent> InputController::_filter_events_by_device(const TypedArray<InputEvent> &p_events) {
	if (m_device.is_null() || m_device->get_type() == InputDevice::DEVICETYPE_ALL) {
		return p_events;
	}
	TypedArray<InputEvent> filtered_events;
	for (int i = 0; i < p_events.size(); i++) {
		Ref<InputEvent> event = p_events[i];
		switch (m_device->get_type()) {
			case InputDevice::DEVICETYPE_KEYBOARD:
				if (event->is_class("InputEventKey") || event->is_class("InputEventMouse")) {
					filtered_events.push_back(event);
				}
				break;
			case InputDevice::DEVICETYPE_JOYPAD:
				if (event->is_class("InputEventJoypadButton") || event->is_class("InputEventJoypadMotion")) {
					if (event->get_device() == m_device->get_id() || event->get_device() == InputEvent::DEVICE_ID_EMULATION || m_device->get_id() == InputEvent::DEVICE_ID_EMULATION) {
						event->set_device(m_device->get_id());
						filtered_events.push_back(event);
					}
				}
				break;
		}
	}
	return filtered_events;
}

void InputController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_device"), &InputController::get_device);
	ClassDB::bind_method(D_METHOD("set_device", "device"), &InputController::set_device);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "device", PROPERTY_HINT_RESOURCE_TYPE, "InputDevice"), "set_device", "get_device");

	ClassDB::bind_method(D_METHOD("get_built_in_action", "action"), &InputController::get_built_in_action);
}