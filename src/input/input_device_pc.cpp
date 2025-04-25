#include "input_device_pc.h"

Ref<InputDevice> InputDevicePC::get_input_device() {
	return m_input_device;
}

void InputDevicePC::set_input_device(const Ref<InputDevice> &device) {
	m_input_device = device;
}

void InputDevicePC::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_input_device"), &InputDevicePC::get_input_device);
	ClassDB::bind_method(D_METHOD("set_input_device", "device"), &InputDevicePC::set_input_device);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "input_device", PROPERTY_HINT_RESOURCE_TYPE, "InputDevice"), "set_input_device", "get_input_device");

	ADD_SIGNAL(MethodInfo("input_device_changed"));
}
