#include <Windows.h>

#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>

#include <gl\glew.h>
#include <gl\gl.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

#include "BufferObject.h"

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// create window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL Laboratory", sf::Style::Close);

	// fire up glew
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		MessageBoxA(0, LPSTR(glewGetErrorString(err)), "GLEW error", MB_ICONWARNING);
	}

	// set culling
	glEnable(GL_CULL_FACE);
	// enable arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// set projection matrix
	glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&proj[0][0]);

	// camera
	glm::vec3 cameraPosition(0.0f, 200.0f, 300.0f);
	glm::quat cameraRotation;

	// arrays
	float size = 100.0f;
	GLfloat vertexArray[] =
	{
		-size, -size, -size,
		-size, -size, size,
		-size, size, size,
		-size, size, -size,
		size, -size, -size,
		size, -size, size,
		size, size, size,
		size, size, -size
	};
	GLfloat colorArray[] =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f
	};
	GLubyte indexArray[] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6,
		1, 5, 6,
		1, 6, 2,
		0, 3, 7,
		0, 7, 4,
		0, 4, 5,
		0, 5, 1,
		2, 6, 7,
		2, 7, 3
	};

	// buffers
	BufferObject vertex, color, index;
	vertex.Create(BufferObject::Type::Vertex);
	vertex.Copy(sizeof(vertexArray), vertexArray);
	color.Create(BufferObject::Type::Color);
	color.Copy(sizeof(colorArray), colorArray);
	index.Create(BufferObject::Type::Index);
	index.Copy(sizeof(indexArray), indexArray);

	// set mouse
	window.setMouseCursorVisible(false);
	bool mouseSnap = true;
	sf::Mouse::setPosition(sf::Vector2i(400, 300), window);

	// begin loop
	bool looping = true;
	while (looping)
	{
		// retreive events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				looping = false;
			if (event.type == sf::Event::LostFocus)
				mouseSnap = false;
			if (event.type == sf::Event::GainedFocus)
				mouseSnap = true;
		}

		// input settings
		float moveSpeed = 0.5f;
		float rotateSpeed = 0.004f;

		// get input
		float tX = ((float)sf::Keyboard::isKeyPressed(sf::Keyboard::D)      - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::A))        * moveSpeed;
		float tY = ((float)sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) * moveSpeed;
		float tZ = ((float)sf::Keyboard::isKeyPressed(sf::Keyboard::S)      - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::W))        * moveSpeed;
		float rX = -(sf::Mouse::getPosition(window).x - 400) * rotateSpeed;
		float rY = -(sf::Mouse::getPosition(window).y - 300) * rotateSpeed;

		// translation
		glm::vec3 translationV(tX, 0.0f, tZ);
		glm::vec3 translationV2(0.0f, tY, 0.0f);
		cameraPosition += cameraRotation * translationV + translationV2;
		glm::mat4 translation = glm::translate(glm::mat4(), cameraPosition);

		// rotation
		glm::quat rotationX(glm::vec3(rY, 0.0f, 0.0f));
		glm::quat rotationY(glm::vec3(0.0f, rX, 0.0f));
		cameraRotation = rotationY * cameraRotation * rotationX;
		glm::mat4 rotation = glm::mat4_cast(cameraRotation);

		// camera matrix
		glm::mat4 camera = translation * rotation;

		// reset mouse
		if (mouseSnap)
			sf::Mouse::setPosition(sf::Vector2i(400, 300), window);

		// set view matrix
		glm::mat4 view = glm::inverse(camera);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&view[0][0]);

		// clear the window
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render polygon
		vertex.Bind();
		color.Bind();
		index.Bind();

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
		
		// swap buffers
		window.display();
	}

	return 0;
}