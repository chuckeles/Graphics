#pragma once

#include <memory>
#include <string>

class Actor;
typedef std::weak_ptr<Actor> ActorWeakPtr;

__interface IComponent
{

public:

	virtual const std::string GetType() const = 0;
	virtual void OnAttach(ActorWeakPtr actor) = 0;

};

// shared ptr
typedef std::shared_ptr<IComponent> ComponentPtr;