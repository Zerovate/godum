#include "local_player.h"

LocalPlayer::LocalPlayer() {
	m_role = ROLE_AutonomouseProxy;
	m_input_device = Ref<InputDevice>(memnew(InputDevice));
}

void LocalPlayer::set_role(Role role) {
	// local player always is autonomouse
}

Ref<InputDevice> LocalPlayer::get_input_device() const {
	return m_input_device;
}

void LocalPlayer::set_input_device(const Ref<InputDevice> &device) {
	m_input_device = device;
}

void LocalPlayer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_input_device"), &LocalPlayer::get_input_device);
	ClassDB::bind_method(D_METHOD("set_input_device", "device"), &LocalPlayer::set_input_device);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "input_device", PROPERTY_HINT_RESOURCE_TYPE, "InputDevice"), "set_input_device", "get_input_device");
}
