#pragma once
#include "../engine/controller.h"

class Player;
class Pawn;

class PlayerController : public Controller {
	GDCLASS(PlayerController, Controller);

public:
	Ref<Player> player;
	Pawn *pawn;

	// protected:
	// void on_posses(Pawn * pawn_in_posses);
};
