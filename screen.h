#ifndef SCREEN_H
#define SCREEN_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "input_handler.h"
#include "view.h"

class Game;

class Screen
{
public:
	Screen(GLint width, GLint height, Game *game);
	virtual ~Screen();
	GLint GetWidth() const;
	GLint GetHeight() const;
	glm::vec2 GetMousePos() const;
	virtual void Update(GLfloat delta) = 0;
	virtual void Render() = 0;

	void AddInputHandler(InputHandler *handler);
	View *GetScreenView();
protected:
	Game *game;
	GLint width;
	GLint height;
private:
	class ScreenInputHandler : public InputHandler
	{
	public:
		ScreenInputHandler(View *view, std::vector<InputHandler*> *handlers) :
			view(view), handlers(*handlers)
		{}

		bool OnKeyDown(int key, int mods)
		{
			bool handled = view->OnKeyDown(key, mods);

			for (int i = 0; i < handlers.size(); i++)
			{
				if (handled)
				{
					break;
				}

				handled = handlers[i]->OnKeyDown(key, mods) || handled;
			}

			return handled;
		}

		bool OnKeyUp(int key, int mods)
		{
			bool handled = view->OnKeyUp(key, mods);

			for (int i = 0; i < handlers.size(); i++)
			{
				if (handled)
				{
					break;
				}

				handled = handlers[i]->OnKeyUp(key, mods) || handled;
			}

			return handled;
		}

		bool OnMouseDown(int button, int mods)
		{
			bool handled = view->OnMouseDown(button, mods);

			for (int i = 0; i < handlers.size(); i++)
			{
				if (handled)
				{
					break;
				}

				handled = handlers[i]->OnMouseDown(button, mods) || handled;
			}

			return handled;
		}

		bool OnMouseUp(int button, int mods)
		{
			bool handled = view->OnMouseUp(button, mods);

			for (int i = 0; i < handlers.size(); i++)
			{
				if (handled)
				{
					break;
				}

				handled = handlers[i]->OnMouseUp(button, mods) || handled;
			}

			return handled;
		}

		bool OnMouseScroll(float xOffset, float yOffset)
		{
			bool handled = view->OnMouseScroll(xOffset, yOffset);

			for (int i = 0; i < handlers.size(); i++)
			{
				if (handled)
				{
					break;
				}

				handled = handlers[i]->OnMouseScroll(xOffset, yOffset) || handled;
			}

			return handled;
		}

		bool OnMouseMoved(float x, float y)
		{
			bool handled = view->OnMouseMoved(x, y);

			for (int i = 0; i < handlers.size(); i++)
			{
				if (handled)
				{
					break;
				}

				handled = handlers[i]->OnMouseMoved(x, y) || handled;
			}

			return handled;
		}

	private:
		View *view;
		std::vector<InputHandler*> &handlers;
	};

	ScreenInputHandler screenInputHandler;
	View screenView;
	std::vector<InputHandler*> inputHandlers;
};

#endif