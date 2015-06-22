#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class InputHandler
{
public:
	virtual void onKeyDown(int key, int mods) = 0;
	virtual void onKeyUp(int key, int mods) = 0;
	virtual void onMouseDown(int button, int mods) = 0;
	virtual void onMouseUp(int button, int mods) = 0;
	virtual void onMouseScroll(float xOffset, float yOffset) = 0;
	virtual void onMouseMoved(float x, float y) = 0;
};

#endif