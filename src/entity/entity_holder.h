#pragma once
#include <scene/main/node.h>

class EntityHolder {
public:
	bool register_entity(Node *entity);
	bool unregister_entity(Node *entity);
};
