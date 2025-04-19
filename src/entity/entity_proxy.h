#pragma once
#include <scene/main/node.h>

class Player;

class EntityProxy : public Object {
	GDCLASS(EntityProxy, Object)
public:
	EntityProxy(Node *entity);
	~EntityProxy();

	_FORCE_INLINE_ Node *get_entity() const;

	_FORCE_INLINE_ Player *get_player() const;
	_FORCE_INLINE_ void set_player(Player *player);

private:
	Node *m_entity;

	Player *m_player = nullptr;

	EntityProxy() = default;
	bool _try_find_player();

protected:
	static void _bind_methods();
};
