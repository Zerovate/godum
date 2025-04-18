#pragma once
#include <scene/main/node.h>

class EntityProxy {
public:
	EntityProxy() = delete;
	EntityProxy(Node *entity) :
			m_entity(entity) {}
	EntityProxy(const EntityProxy &) = delete;
	EntityProxy &operator=(const EntityProxy &) = delete;

	Node *get() { return m_entity; }

private:
	Node *m_entity;
};
