#pragma once
#include "player.h"

#include "input/input_device.h"

// local player made by input device.
class LocalPlayer : public Player {
	GDCLASS(LocalPlayer, Player);

public:
	LocalPlayer();

	virtual void set_role(Role role) override;

	Ref<InputDevice> get_input_device() const;
	void set_input_device(const Ref<InputDevice> &device);

protected:
	Ref<InputDevice> m_input_device;

protected:
	static void _bind_methods();
};
