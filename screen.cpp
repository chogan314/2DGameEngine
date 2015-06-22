#include "screen.h"

Screen::Screen(GLint width, GLint height, Game *game)
: width(width), height(height), game(game)
{}

GLint Screen::GetHeight() const
{
	return height;
}

GLint Screen::GetWidth() const
{
	return width;
}