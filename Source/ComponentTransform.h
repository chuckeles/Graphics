#pragma once

#include "IComponent.h"
#include "Transform.h"

class ComponentTransform :
	public IComponent,
	public Transform
{

public:

	ComponentTransform() = default;
	ComponentTransform(float x, float y, float z);
	ComponentTransform(glm::vec3& pos);
	ComponentTransform(const Transform& transform);

	virtual std::string GetType() const;
	virtual void OnAttach(ActorWeakPtr actor);

};