#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "Cube.h"

int main(int argc, char *argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Template", sf::Style::Titlebar | sf::Style::Close);

	bool keyHeld = false, up = false, down = false, one = true, two = false, three = false, four = false;

	/*sf::Texture dogeTexture;
	bool success = dogeTexture.loadFromFile("res/doge.jpg");

	sf::Sprite dogeSprite;
	dogeSprite.setTexture(dogeTexture);
	dogeSprite.setScale(0.25f, 0.25f);*/

	sf::Image dogeImage;
	sf::Image rickImage;
	dogeImage.loadFromFile("res/doge.jpg");
	rickImage.loadFromFile("res/rick.jpg");
	

	// Tell OpenGL that we want to use 2D textures. 
	glEnable(GL_TEXTURE_2D);

	// Tell OpenGL that we want to use lighting.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	/* Tell OpenGL that we want to test the depth of each vertex to make sure that things that
	* are closer appear closer. */
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);
	// Generate a texture in OpenGL, and retrieve its ID so that we can access it.
	GLuint dogeTextureID;
	glGenTextures(1, &dogeTextureID);

	/* 'Bind' our texture to the active texture space so that all of our operations
	* are done to it. */
	glBindTexture(GL_TEXTURE_2D, dogeTextureID);

	glTexImage2D(GL_TEXTURE_2D, // specifies that we're working on the active texture.
		0, // ignore.
		GL_RGBA, // specifies that making a texture that has RGBA data.
		dogeImage.getSize().x, // specify the width of the texture.
		dogeImage.getSize().y, // specify the height of the texture.
		0, // no border
		GL_RGBA, // specifies that we're working with an image that has RGBA data.
		GL_UNSIGNED_BYTE, // specifies the format of the RGBA data (in this case, everything is 0-255)
		dogeImage.getPixelsPtr() // specifies the actual image data.
		);

	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	Cube cube1 = Cube(dogeTextureID);

	GLuint rickTextureID;
	glGenTextures(1, &rickTextureID);

	/* 'Bind' our texture to the active texture space so that all of our operations
	* are done to it. */
	glBindTexture(GL_TEXTURE_2D, rickTextureID);

	glTexImage2D(GL_TEXTURE_2D, // specifies that we're working on the active texture.
		0, // ignore.
		GL_RGBA, // specifies that making a texture that has RGBA data.
		rickImage.getSize().x, // specify the width of the texture.
		rickImage.getSize().y, // specify the height of the texture.
		0, // no border
		GL_RGBA, // specifies that we're working with an image that has RGBA data.
		GL_UNSIGNED_BYTE, // specifies the format of the RGBA data (in this case, everything is 0-255)
		rickImage.getPixelsPtr() // specifies the actual image data.
		);

	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	Cube cube2 = Cube(rickTextureID);

	float positionZ = 0.5f;
	float angle1 = 0.0f;
	float angle2 = 0.0f;
	
	
	
	sf::Event evt;
	sf::Clock appTimer;
	while (window.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();

		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			else if (evt.type == sf::Event::KeyPressed){
				if (evt.key.code == sf::Keyboard::Key::Up){

					keyHeld = true;
					up = true;
					down = false;
				}
				else if (evt.key.code == sf::Keyboard::Key::Down){

					keyHeld = true;
					up = false;
					down = true;
				}
				if (evt.key.code == sf::Keyboard::Key::Num1 || evt.key.code == sf::Keyboard::Key::Numpad1)
				{
					one = true;
					two = false;
					three = false;
					four = false;

				}
				else if (evt.key.code == sf::Keyboard::Key::Num2 || evt.key.code == sf::Keyboard::Key::Numpad2)
				{
					one = false;
					two = true;
					three = false;
					four = false;
				}
				else if (evt.key.code == sf::Keyboard::Key::Num3 || evt.key.code == sf::Keyboard::Key::Numpad3)
				{
					one = false;
					two = false;
					three = true;
					four = false;
				}
				else if (evt.key.code == sf::Keyboard::Key::Num4 || evt.key.code == sf::Keyboard::Key::Numpad4)
				{
					one = false;
					two = false;
					three = false;
					four = true;

				}
			}
			else if (evt.type == sf::Event::KeyReleased){
				keyHeld = false;
				up = false;
				down = false;
			}

		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum error = glGetError();

		float offset = 0.25f;
		angle1 += 90.0f * deltaTime;
		angle2 += -90.0f * deltaTime;

		//draw stuff
		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glPushMatrix();
		if (keyHeld){
			if (up){
				glRotatef(angle1, 1.0f, 0.0f, 0.0f); // rotate at 90 degrees/second on the X axis. 
			}
			if (down){
				glRotatef(angle2, 1.0f, 0.0f, 0.0f); // rotate at 90 degrees/second on the X axis. 
			}
		}
		if (one)
		{
			
			cube1.Draw(GL_QUADS);
			cube1.Update(deltaTime);
		}
		else if (two)
		{
			
			cube1.Draw(GL_TRIANGLES);
			cube1.Update(deltaTime);
		}
		else if (three)
		{
			
			cube2.Draw(GL_QUAD_STRIP);
			cube2.Update(deltaTime);
		}
		else if (four)
		{
			
			cube2.Draw(GL_TRIANGLE_STRIP);
			cube2.Update(deltaTime);

		}		

		window.display();
	}

	return 0;
}