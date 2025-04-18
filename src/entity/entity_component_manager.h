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

class ECM : public Object {
	GDCLASS(ECM, Object)

	static ECM *singleton;

public:
	ECM();
	static ECM *get_singleton();

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
	HashMap<Node *, HashSet<EntityComponent *>> m_entity_components;
	HashMap<StringName, Vector<EntityComponent *>> m_components;
};
