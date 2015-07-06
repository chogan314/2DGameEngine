#include "test_screen.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include "game.h"

TestScreen::TestScreen(GLint width, GLint height, Game *game) : 
	Screen(width, height, game),
	renderer(&shader)
{
	shader.CompileFromFile("res/shaders/primitive.vs", "res/shaders/primitive.fs");
	renderer.SetContextSize(width, height);
	game->GetInput()->RegisterHandler(this);

	view.SetPosition(glm::vec2(0, 0));
	view.SetWidth(ABSOLUTE, width);
	view.SetHeight(ABSOLUTE, height);

	View *child = new View();
	child->SetGravity(POSITIVE, POSITIVE);
	child->SetWidth(PERCENT_PARENT, 0.5f);
	child->SetHeight(FILL_PARENT, 0.0f);
	view.AddChild(child);

	view.Remeasure();
}

void TestScreen::Update(GLfloat delta)
{

}

void TestScreen::Render()
{
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer.DrawRectangle(view.GetPosition(), view.GetWidth(), view.GetHeight(),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	View *child = view.GetChild(0);

	renderer.DrawRectangle(child->GetPosition(), child->GetWidth(), child->GetHeight(),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
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

}

void TestScreen::onMouseScroll(float xOffset, float yOffset)
{

}

void TestScreen::onMouseMoved(float x, float y)
{

}