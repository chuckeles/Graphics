#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IComponent.h"

// container for components with assigned id
class Actor
{

public:

	typedef unsigned long Id;
	typedef std::unordered_map<std::string, ComponentPtr> ComponentMap;

	Actor(Id id);

	const Id& GetId() const;

	void AddComponent(ComponentPtr component);
	ComponentPtr GetComponent(const std::string& type) const;
	ComponentPtr RemoveComponent(const std::string& type);
	void ClearComponents();

private:

	Id mId = 0;
	ComponentMap mComponents;

};

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::weak_ptr<Actor> ActorWeakPtr;