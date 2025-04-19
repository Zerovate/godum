#pragma once

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
using namespace godot;
#endif

class EntityComponent;
class EntityProxy;

class EntityManager : public Object {
	GDCLASS(EntityManager, Object)

	static EntityManager *singleton;

public:
	EntityManager();
	static EntityManager *get_singleton();

	_FORCE_INLINE_ bool is_entity_registered(Node *entity) const;
	EntityProxy *get_entity_proxy(Node *entity) const;

	bool register_entity(Node *entity);
	bool unregister_entity(Node *entity);

	bool register_component(Node *entity, EntityComponent *component);
	bool unregister_component(Node *entity, EntityComponent *component);
	// entity get component
	TypedArray<EntityComponent> entity_get_components(Node *entity) const;
	TypedArray<EntityComponent> entity_get_components_of_type(Node *entity, const StringName &type) const;
	EntityComponent *entity_get_first_component(Node *entity, const StringName &type) const;

	// component iterators.
	TypedArray<EntityComponent> get_components(const StringName &p_name = "") const;

protected:
	static void _bind_methods();

private:
	HashMap<Node *, EntityProxy *> m_entity_proxies;

	HashMap<Node *, HashSet<EntityComponent *>> m_entity_components;
	HashMap<StringName, Vector<EntityComponent *>> m_components;
};
