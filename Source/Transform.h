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
	void Rotate(float x, float y, float z);
	void Rotate(glm::vec3& rot);

	glm::mat4&& GetMatrix() const;

private:

	glm::vec3 mPosition;
	glm::quat mRotation;

};