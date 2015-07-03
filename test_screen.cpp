#include "test_screen.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include "game.h"

TestScreen::TestScreen(GLint width, GLint height, Game *game) : 
	Screen(width, height, game),
	renderer(&shader),
	triangle(glm::vec2(200, 200),
			 glm::vec2(250, 400),
			 glm::vec2(300, 270))
{
	shader.CompileFromFile("res/shaders/primitive.vs", "res/shaders/primitive.fs");
	renderer.SetContextSize(width, height);
	game->GetInput()->RegisterHandler(this);
}

void TestScreen::Update(GLfloat delta)
{

}

void TestScreen::Render()
{
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (triangle.ContainsPoint(glm::vec2(x, y)))
			{
				renderer.DrawPoint(glm::vec2(x, y));
			}
		}
	}

	renderer.DrawTriangle(triangle.GetPointA(),
		triangle.GetPointB(),
		triangle.GetPointC(),
		glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
}

void TestScreen::onKeyDown(int key, int mods)
{

}

void TestScreen::onKeyUp(int key, int mods)
{

}

void TestScreen::onMouseDown(int button, int mods)
{

}

void TestScreen::onMouseUp(int button, int mods)
{
	glm::vec2 mousePos(game->GetInput()->GetMouseX(), game->GetInput()->GetMouseY());
	if (triangle.ContainsPoint(mousePos))
	{
		std::cout << "HIT" << std::endl;
	}
	else
	{
		std::cout << "MISS" << std::endl;
	}
}

void TestScreen::onMouseScroll(float xOffset, float yOffset)
{

}

void TestScreen::onMouseMoved(float x, float y)
{

}