#include <Windows.h>

#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>

#include <gl\GL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// create window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL Laboratory");

	// set projection matrix
	glm::mat4 proj = glm::ortho(0.f, 800.f, 0.f, 600.f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&proj[0][0]);

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
		glClearColor(0, 0.2f, 0.4f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		// render
		window.display();
	}

	return 0;
}