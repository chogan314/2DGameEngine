#ifndef TEST_SCREEN_H
#define TEST_SCREEN_H

#include "screen.h"
#include "primitive_renderer.h"
#include "triangle.h"
#include "input_handler.h"
#include "view.h"

class TestScreen : public Screen, public InputHandler
{
public:
	TestScreen(GLint width, GLint height, Game *game);

	void Update(GLfloat delta);
	void Render();

	bool OnKeyDown(int key, int mods);
	bool OnKeyUp(int key, int mods);
	bool OnMouseDown(int button, int mods);
	bool OnMouseUp(int button, int mods);
	bool OnMouseScroll(float xOffset, float yOffset);
	bool OnMouseMoved(float x, float y);

private:
	Shader shader;
	PrimitiveRenderer renderer;
	View view;
};

#endif