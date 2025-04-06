#include "steam_multiplayer_peer.h"

#include <steam/steam_gameserver.h>

#define INADDR_ANY (unsigned long)0x00000000

Error SteamMultiplayerPeer::create_server(int p_game_port, int p_query_port) {
	SteamErrMsg errMsg = { 0 };

#ifdef USE_GS_AUTH_API
	EServerMode eMode = eServerModeAuthenticationAndSecure;
#else
	EServerMode eMode = eServerModeAuthentication;
#endif
	if (SteamGameServer_InitEx(INADDR_ANY, p_game_port, p_query_port, eMode, "1.0.0.0", &errMsg) != k_ESteamAPIInitResult_OK) {
		return Error::ERR_COMPILATION_FAILED;
	}
	return Error::OK;
}
