#include "test_screen.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include "game.h"

TestScreen::TestScreen(GLint width, GLint height, Game *game) : 
	Screen(width, height, game),
	renderer(&shader),
	textRenderer(&textShader, width, height),
	spriteRenderer(&spriteShader),
	font("res/fonts/arial.ttf", 48)
{
	shader.CompileFromFile("res/shaders/primitive.vs", "res/shaders/primitive.fs");
	renderer.SetContextSize(width, height);

	textShader.CompileFromFile("res/shaders/text.vs", "res/shaders/text.fs");

	spriteShader.CompileFromFile("res/shaders/sprite.vs", "res/shaders/sprite.fs");
	white.LoadFromFile("res/textures/white.png");

	View *child = new View(this);
	child->SetGravity(GRAVITY_NEGATIVE, GRAVITY_CENTER);
	child->SetWidth(EXPANSION_PERCENT_PARENT, 0.5f);
	child->SetHeight(EXPANSION_PERCENT_PARENT, 0.5f);
	child->SetMargins(MARGIN_LEFT, MARGIN_PERCENT, 0.1f);

	child->SetOnMouseEnterListener([](float x, float y)
	{ 
		std::cout << "ENTER" << std::endl; return false; 
	});

	child->SetOnMouseExitListener([](float x, float y)
	{
		std::cout << "EXIT" << std::endl; return false;
	});

	GetScreenView()->AddChild(child);
	GetScreenView()->Remeasure();
	GetScreenView()->SetBackgroundColor(1.0f, 0.0f, 0.0f, 1.0f);
	child->SetBackgroundColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void TestScreen::Update(GLfloat delta)
{
	timePassed += delta;
}

void TestScreen::Render()
{
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 projection = glm::ortho(0.0f, (float) width, (float) height, 0.0f);
	spriteShader.SetMatrix4("projection", projection);

	GetScreenView()->Draw(spriteRenderer, textRenderer);
}