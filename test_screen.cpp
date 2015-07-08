#include "test_screen.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include "game.h"

TestScreen::TestScreen(GLint width, GLint height, Game *game) : 
	Screen(width, height, game),
	renderer(&shader),
	view(this)
{
	shader.CompileFromFile("res/shaders/primitive.vs", "res/shaders/primitive.fs");
	renderer.SetContextSize(width, height);
	game->GetInput()->RegisterHandler(this);

	view.SetPosition(glm::vec2(0, 0));
	view.SetWidth(EXPANSION_ABSOLUTE, width);
	view.SetHeight(EXPANSION_ABSOLUTE, height);

	View *child = new View(this);
	child->SetGravity(GRAVITY_NEGATIVE, GRAVITY_CENTER);
	child->SetWidth(EXPANSION_PERCENT_PARENT, 0.5f);
	child->SetHeight(EXPANSION_PERCENT_PARENT, 0.5f);
	child->SetMargins(MARGIN_LEFT, MARGIN_PERCENT, 0.1f);
	view.AddChild(child);

	view.SetOnMouseDownListener([](int key, int mods) { std::cout << "Click!!!" << std::endl; return false; });

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

bool TestScreen::OnKeyDown(int key, int mods)
{
	return view.OnKeyDown(key, mods);
}

bool TestScreen::OnKeyUp(int key, int mods)
{
	return view.OnKeyUp(key, mods);
}

bool TestScreen::OnMouseDown(int button, int mods)
{
	return view.OnMouseDown(button, mods);
}

bool TestScreen::OnMouseUp(int button, int mods)
{
	return view.OnMouseUp(button, mods);
}

bool TestScreen::OnMouseScroll(float xOffset, float yOffset)
{
	return view.OnMouseScroll(xOffset, yOffset);
}

bool TestScreen::OnMouseMoved(float x, float y)
{
	return view.OnMouseMoved(x, y);
}