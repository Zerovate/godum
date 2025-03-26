#include "input_device.h"

InputDevice::DeviceType InputDevice::get_type() const {
	return m_type;
}

void InputDevice::set_type(DeviceType p_type) {
	m_type = p_type;
}

int InputDevice::get_id() const {
	return m_id;
}

void InputDevice::set_id(int p_id) {
	m_id = p_id;
}

void InputDevice::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &InputDevice::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "p_type"), &InputDevice::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type"), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_id"), &InputDevice::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "p_id"), &InputDevice::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	BIND_ENUM_CONSTANT(DEVICETYPE_ALL);
	BIND_ENUM_CONSTANT(DEVICETYPE_KEYBOARD);
	BIND_ENUM_CONSTANT(DEVICETYPE_JOYPAD);
}