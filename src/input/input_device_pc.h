#pragma once
#include "input_device.h"
#include "player_component/player_component.h"

class InputDevicePC : public PlayerComponent {
	GDCLASS(InputDevicePC, PlayerComponent)

public:
	Ref<InputDevice> get_input_device();
	void set_input_device(const Ref<InputDevice> &device);

private:
	// InputDevice
	Ref<InputDevice> m_input_device;

protected:
	static void _bind_methods();
};
