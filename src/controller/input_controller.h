#pragma once
#include "controller.h"

class InputController : public Controller {
	GDCLASS(InputController, Controller);

protected:
	void _notification(int p_what);

	virtual void _input(const Ref<InputEvent> &p_event) override;

protected:
	static void _bind_methods();
};
