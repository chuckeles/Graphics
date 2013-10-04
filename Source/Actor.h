#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IComponent.h"

typedef unsigned long ActorId;

// container for components with assigned id
class Actor
{

	typedef std::unordered_map<std::string, ComponentPtr> ComponentMap;

public:

	Actor(const ActorId id);

	const ActorId& GetId() const;

	void AddComponent(ComponentPtr component);
	ComponentPtr GetComponent(const std::string& type) const;
	ComponentPtr RemoveComponent(const std::string& type);
	void ClearComponents();

private:

	ActorId mId;
	ComponentMap mComponents;

};

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::weak_ptr<Actor> ActorWeakPtr;