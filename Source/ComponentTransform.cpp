#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(float x, float y, float z) :
	Transform(x, y, z)
{
}

ComponentTransform::ComponentTransform(glm::vec3& pos) :
	Transform(pos)
{
}

ComponentTransform::ComponentTransform(const Transform& transform) :
	Transform(transform)
{
}

std::string ComponentTransform::GetType() const
{
	return "Transform";
}

void ComponentTransform::OnAttach(ActorWeakPtr actor)
{
}