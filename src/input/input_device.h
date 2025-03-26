#pragma once

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION

class InputDevice : public Resource {
	GDCLASS(InputDevice, Resource);

public:
	enum DeviceType {
		DEVICETYPE_ALL = -1,
		DEVICETYPE_KEYBOARD,
		DEVICETYPE_JOYPAD
	};

	DeviceType get_type() const;
	void set_type(DeviceType p_type);

	int get_id() const;
	void set_id(int p_id);

private:
	DeviceType m_type = DeviceType::DEVICETYPE_ALL;
	int m_id = InputEvent::DEVICE_ID_EMULATION;

protected:
	static void _bind_methods();
};

VARIANT_ENUM_CAST(InputDevice::DeviceType);
