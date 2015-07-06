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

	void onKeyDown(int key, int mods);
	void onKeyUp(int key, int mods);
	void onMouseDown(int button, int mods);
	void onMouseUp(int button, int mods);
	void onMouseScroll(float xOffset, float yOffset);
	void onMouseMoved(float x, float y);

private:
	Shader shader;
	PrimitiveRenderer renderer;
	View view;
};

#endif