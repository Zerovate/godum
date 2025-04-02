#pragma once
#include "player_component.h"

#include "input/input_device.h"

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/templates/hash_map.hpp>

class InputPlayerComponent : public PlayerComponent {
	GDCLASS(InputPlayerComponent, PlayerComponent);

public:
	InputPlayerComponent();

	void _ready();

	Ref<InputDevice> get_device() const { return m_device; }
	void set_device(const Ref<InputDevice> &p_device);

	_FORCE_INLINE_ StringName get_built_in_action(const StringName &p_action) const;

private:
	Ref<InputDevice> m_device;
	HashMap<StringName, StringName> m_built_in_action_map;

	void _setup_device_actions();
	_FORCE_INLINE_ StringName _action_with_ext(const StringName &p_action) const;
	TypedArray<InputEvent> _filter_events_by_device(const TypedArray<InputEvent> &p_events);

protected:
	static void _bind_methods();
};
