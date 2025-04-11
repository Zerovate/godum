#pragma once
#include "component.h"

#include <type_traits>

#ifdef GODUM_MODULE
#include <core/templates/hash_map.h>
#include <core/templates/hash_set.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
using namespace godot;
#endif

template <typename T = Component>
class ComponentHolder {
	static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

public:
	virtual TypedArray<T> get_components(const StringName &name) const;
	virtual T *get_component(const StringName &name) const;
	virtual bool register_component(T *component);
	virtual bool unregister_component(T *component);

protected:
	HashMap<StringName, HashSet<T *>> m_components_map;
};

template <typename T>
TypedArray<T> ComponentHolder<T>::get_components(const StringName &name) const {
	TypedArray<T> res;
	if (m_components_map.has(name)) {
		for (auto c : m_components_map[name]) {
			res.append(c);
		}
	}
	return res;
}

template <typename T>
T *ComponentHolder<T>::get_component(const StringName &name) const {
	if (m_components_map.has(name)) {
		return *(m_components_map[name].begin());
	}
	return nullptr;
}

template <typename T>
bool ComponentHolder<T>::register_component(T *component) {
	ERR_FAIL_COND_V(!component, false);
	StringName class_name = component->get_class();
	while (class_name != StringName("Component")) {
		if (!m_components_map.has(class_name)) {
			m_components_map.insert(class_name, {});
		}
		m_components_map[class_name].insert(component);
		class_name = ClassDB::get_parent_class(class_name);
		ERR_FAIL_COND_V_MSG(class_name.is_empty(), false, "Invalid parent class");
	}
	component->emit_signal("registered");
	return true;
}

template <typename T>
bool ComponentHolder<T>::unregister_component(T *component) {
	ERR_FAIL_COND_V(!component, false);
	StringName class_name = component->get_class();
	while (class_name != StringName("Component")) {
		m_components_map[class_name].erase(component);
		class_name = ClassDB::get_parent_class(class_name);
		ERR_FAIL_COND_V_MSG(class_name.is_empty(), false, "Invalid parent class");
	}
	component->emit_signal("unregistered");
	return true;
}

#define COMPONENT_HOLDER_IMPLEMENT(m_class)                                             \
public:                                                                                 \
	virtual TypedArray<m_class> get_components(const StringName &name) const override { \
		return ComponentHolder<m_class>::get_components(name);                          \
	}                                                                                   \
	virtual m_class *get_component(const StringName &name) const override {             \
		return ComponentHolder<m_class>::get_component(name);                           \
	}                                                                                   \
	virtual bool register_component(m_class *component) override {                      \
		return ComponentHolder<m_class>::register_component(component);                 \
	}                                                                                   \
	virtual bool unregister_component(m_class *component) override {                    \
		return ComponentHolder<m_class>::unregister_component(component);               \
	}

#define COMPONENT_HOLDER_BIND_METHODS(m_class)                                                       \
	ClassDB::bind_method(D_METHOD("get_components", "name"), &m_class::get_components);              \
	ClassDB::bind_method(D_METHOD("get_component", "name"), &m_class::get_component);                \
	ClassDB::bind_method(D_METHOD("register_component", "component"), &m_class::register_component); \
	ClassDB::bind_method(D_METHOD("unregister_component", "component"), &m_class::unregister_component);
