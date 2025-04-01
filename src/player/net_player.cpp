#include "net_player.h"

void NetPlayer::set_role(Role role) {
	switch (role) {
		case ROLE_Authority:
		case ROLE_SimulatedProxy:
			m_role = role;
			break;
		default:
			break;
	}
}
