#include "godum.h"

#include "player/player.h"

Player *Godum::get_player(Node *node) {
	Player *player = Object::cast_to<Player>(node);
	if (player) {
		return player;
	}
	Node *parent = node;
	while (parent) {
		parent = parent->get_parent();
		player = Object::cast_to<Player>(parent);
		if (player) {
			return player;
		}
	}
	return nullptr;
}

void Godum::_bind_methods() {
	ClassDB::bind_static_method("Godum", D_METHOD("get_player", "node"), &Godum::get_player);
}