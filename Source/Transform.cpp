#include "Transform.h"

#include <glm\gtc\matrix_transform.hpp>

Transform::Transform(float x, float y, float z) :
	Transform(glm::vec3(x, y, z))
{
}

Transform::Transform(glm::vec3& pos) :
	mPosition(pos)
{
}

void Transform::Move(float x, float y, float z, Space space)
{
	Move(glm::vec3(x, y, z), space);
}

void Transform::Move(glm::vec3& pos, Space space)
{
	if (space == Space::Global)
		mPosition += pos;
	else
		mPosition += mRotation * pos;
}

void Transform::Rotate(float x, float y, float z)
{
	Rotate(glm::vec3(x, y, z));
}

void Transform::Rotate(glm::vec3& rot)
{
	glm::quat rotationX(glm::vec3(rot.x, 0.0f, 0.0f));
	glm::quat rotationY(glm::vec3(0.0f, rot.y, 0.0f));

	mRotation = rotationY * mRotation * rotationX;
}

glm::mat4&& Transform::GetMatrix() const
{
	glm::mat4 position = glm::translate(glm::mat4(), mPosition);
	glm::mat4 rotation = glm::mat4_cast(mRotation);

	return position * rotation;
}