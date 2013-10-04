#include "Actor.h"

#include <utility>

#include "Exception.h"
#include "ActorManager.h"

Actor::Actor(const ActorId id) :
	mId(id)
{
}

const ActorId& Actor::GetId() const
{
	return mId;
}

void Actor::AddComponent(ComponentPtr component)
{
	if (mComponents.count(component->GetType()))
		THROW_ERROR("Component " + component->GetType() + " already added");
	mComponents[component->GetType()] = component;
	component->OnAttach(ActorWeakPtr(ActorManager::GetSingleton().GetActor(mId)));
}

ComponentPtr Actor::GetComponent(const std::string& type) const
{
	if (!mComponents.count(type))
		THROW_ERROR("Unknown component " + type);
	return mComponents.at(type);
}

ComponentPtr Actor::RemoveComponent(const std::string& type)
{
	ComponentPtr c = GetComponent(type);
	mComponents.erase(type);
	return c;
}

void Actor::ClearComponents()
{
	mComponents.clear();
}