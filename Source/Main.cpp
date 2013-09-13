#include <Windows.h>

#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>

#include <gl\glew.h>
#include <gl\gl.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
	glm::mat4 proj = glm::perspective(80.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&proj[0][0]);

	// set view matrix
	glm::mat4 camera;

	glm::mat4 view = glm::inverse(camera);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&view[0][0]);

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
	GLuint vertices, colors, indices;
	glGenBuffers(1, &vertices);
	glGenBuffers(1, &colors);
	glGenBuffers(1, &indices);

	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorArray), colorArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

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
		}

		// get input
		camera = glm::translate(camera, glm::vec3(
			(float)sf::Keyboard::isKeyPressed(sf::Keyboard::D) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::A),
			(float)sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::LControl),
			(float)sf::Keyboard::isKeyPressed(sf::Keyboard::S) - (float)sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			));

		// move camera
		view = glm::inverse(camera);

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&view[0][0]);

		// clear the window
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render polygon
		glBindBuffer(GL_ARRAY_BUFFER, vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, colors);
		glColorPointer(3, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
		glIndexPointer(GL_UNSIGNED_BYTE, 0, 0);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
		
		// swap buffers
		window.display();
	}

	return 0;
}