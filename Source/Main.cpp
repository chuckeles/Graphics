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
	glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&proj[0][0]);

	// arrays
	GLfloat vertexArray[] = 
	{
		100.0f, 100.0f,
		500.0f, 100.0f,
		700.0f, 300.0f,
		500.0f, 500.0f,
		100.0f, 500.0f
	};
	GLfloat colorArray[] = 
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f
	};

	glVertexPointer(2, GL_FLOAT, 0, vertexArray);
	glColorPointer(3, GL_FLOAT, 0, colorArray);

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
		glDrawArrays(GL_POLYGON, 0, 5);
		
		// swap buffers
		window.display();
	}

	return 0;
}