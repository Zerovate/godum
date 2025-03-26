#pragma once
#include "engine/controller.h"
#include "input_device.h"

#include <godot_cpp/classes/input_event.hpp>

class InputController : public Controller {
	GDCLASS(InputController, Controller);

public:
	void _ready();

	Ref<InputDevice> get_device() const { return m_device; }
	void set_device(const Ref<InputDevice> &p_device);

private:
	Ref<InputDevice> m_device;
	Vector<StringName> m_device_actions;

	void _setup_device_actions();
	_FORCE_INLINE_ StringName _action_with_ext(StringName p_action);
	TypedArray<InputEvent> _filter_events_by_device(const TypedArray<InputEvent> &p_events);

protected:
	static void _bind_methods();
};
