#pragma once
#include "player_component.h"

#include "input/input_device.h"

#ifdef GODUM_MODULE
#include <core/input/input_event.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#endif

class InputPlayerComponent : public PlayerComponent {
	GDCLASS(InputPlayerComponent, PlayerComponent);

public:
	InputPlayerComponent();

	void register_device_actions(TypedArray<StringName> p_actions);
	void unregister_device_actions(TypedArray<StringName> p_actions);
	Ref<InputDevice> get_device() const;
	_FORCE_INLINE_ StringName get_device_action(const StringName &p_action) const;

private:
	HashMap<StringName, StringName> m_built_in_action_map;

	void _on_player_changed(Player *prev_player, Player *new_player);
	void _on_input_device_changed();
	_FORCE_INLINE_ StringName _action_with_ext(const StringName &p_action) const;
	TypedArray<InputEvent> _filter_events_by_device(const TypedArray<InputEvent> &p_events);

protected:
	static void _bind_methods();
};
