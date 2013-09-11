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
	// glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 1000.0f);
	glm::mat4 proj = glm::perspective(80.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&proj[0][0]);

	// set view matrix
	glm::mat4 camera = glm::lookAt(glm::vec3(50.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&camera[0][0]);

	// arrays
	float z = -100.0f;
	GLfloat vertexArray[] =
	{
		-80.0f, -50.0f, z,
		50.0f, -50.0f, z,
		80.0f, 0.0f, z,
		50.0f, 50.0f, z,
		-80.0f, 50.0f, z
	};
	GLfloat colorArray[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f
	};
	GLubyte indexArray[] =
	{
		0, 1, 3,
		1, 2, 3,
		0, 3, 4
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

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, 0);
		
		// swap buffers
		window.display();
	}

	return 0;
}