#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
	//returns the current ComponentID
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	//generates a new last ID and will put that in typeID, then return typeID
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

//check if an entity has a component attached

constexpr std::size_t maxComponents = 32; //max amount of components that system can hold
constexpr std::size_t maxGroups = 32; //max amount of groups for render and collision layers, each entity can be member of multiple groups

using ComponentBitSet = std::bitset<maxComponents>;//finds if entity has a selection of components by matching
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*,maxComponents>;//array of component pointers

class Component
{
public:
	Entity* entity;

	virtual void init() {} //accesses other components
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component(){}

};


//Entity class: keeps a list of components
class Entity {
private:
	Manager& manager;
	bool active = true; //if false, remove it from game
	std::vector<std::unique_ptr<Component>> components; //list of all the components the entity is holding

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitset groupBitset;
public:
	Entity(Manager& mManager) : manager(mManager) {}
	void update() {
		//entity will loop through all of its components and update them
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	//check if it's in a group, returns true or false if
	//a certain bit is 0 or 1 in the bitset
	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}
	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}

	//the entity class needs to be able to see if it has components
	template<typename T> bool hasComponent() const
	{
		//return from the bitset if it has component from a position component
		return componentBitSet[getComponentTypeID<T>()];
	}

	//be able to add a component to entity
	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		//after adding all components, init them

		c->init();
		return *c;
	}

	//get component
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};
//managing class that keeps a list of all the entities

class  Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	//update all entities
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	//every frame move through the entities and remove the ones who aren't there
	void refresh() {
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{e};

		//add this entity to the entity list
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
