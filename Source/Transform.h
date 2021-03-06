#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

class Transform
{

public:

	enum class Space
	{
		Local,
		Global
	};

	Transform() = default;
	Transform(float x, float y, float z);
	Transform(glm::vec3& pos);

	void Move(float x, float y, float z, Space space = Space::Local);
	void Move(glm::vec3& pos, Space space = Space::Local);

	void Rotate(glm::vec3& axis, float angle, Space space = Space::Local);
	void Rotate(glm::quat& quat, Space space = Space::Local);
	void Pitch(float angle, Space space = Space::Local);
	void Yaw(float angle, Space space = Space::Local);
	void Roll(float angle, Space space = Space::Local);

	glm::mat4 GetMatrix() const;
	glm::mat4 GetInverse() const;

private:

	glm::vec3 mPosition;
	glm::quat mRotation;

};