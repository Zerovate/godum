#include "local_player.h"

LocalPlayer::LocalPlayer() {
	m_role = ROLE_AutonomouseProxy;
}

void LocalPlayer::set_role(Role role) {
	// local player always is autonomouse
}
