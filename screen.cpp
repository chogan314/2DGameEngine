#include "screen.h"
#include "game.h"

Screen::Screen(GLint width, GLint height, Game *game) :
	width(width),
	height(height),
	game(game),
	screenView(this),
	screenInputHandler(&screenView, &inputHandlers)
{
	screenView.SetPosition(glm::vec2(0.0f));
	screenView.SetWidth(EXPANSION_ABSOLUTE, (float) width);
	screenView.SetHeight(EXPANSION_ABSOLUTE, (float) height);
	game->GetInput()->RegisterHandler(&screenInputHandler);
}

Screen::~Screen()
{
	for (int i = 0; i < inputHandlers.size(); i++)
	{
		delete inputHandlers[i];
	}
}

GLint Screen::GetHeight() const
{
	return height;
}

GLint Screen::GetWidth() const
{
	return width;
}

glm::vec2 Screen::GetMousePos() const
{
	return glm::vec2(game->GetInput()->GetMouseX(), game->GetInput()->GetMouseY());
}

void Screen::AddInputHandler(InputHandler *handler)
{
	inputHandlers.push_back(handler);
}

View *Screen::GetScreenView()
{
	return &screenView;
}