#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	//returns the current ComponentID
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	//generates a new last ID and will put that in typeID, then return typeID
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

//check if an entity has a component attached

constexpr std::size_t maxComponents = 32; //max amount of components that system can hold

using ComponentBitSet = std::bitset<maxComponents>;//finds if entity has a selection of components by matching
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
	bool active = true; //if false, remove it from game
	std::vector<std::unique_ptr<Component>> components; //list of all the components the entity is holding

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void update() {
		//entity will loop through all of its components and update them
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

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
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity;
		std::unique_ptr<Entity> uPtr{e};

		//add this entity to the entity list
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
