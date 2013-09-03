#include <Windows.h>

#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>

#include <gl\GL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// create window
	sf::Window window(sf::VideoMode(800, 600), "OpenGL Laboratory", sf::Style::Close);

	// set projection matrix
	glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

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
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render something
		glColor3f(0.6f, 0.1f, 0.1f);

		glBegin(GL_POLYGON);
		glVertex2f(100.0f, 100.0f);
		glVertex2f(100.0f, 500.0f);
		glVertex2f(400.0f, 500.0f);
		glVertex2f(700.0f, 300.0f);
		glVertex2f(400.0f, 100.0f);
		glEnd();

		// render
		window.display();
	}

	return 0;
}