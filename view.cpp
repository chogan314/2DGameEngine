#include "view.h"
#include "screen.h"
#include "game.h"

View::View(Screen *screen) : context(screen) { }

View::~View()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}

void View::SetGravity(GravityDirection xDirection, GravityDirection yDirection)
{
	gravity.xDir = xDirection;
	gravity.yDir = yDirection;
}

void View::SetPosition(const glm::vec2 &position)
{
	gravity.defaultPos = glm::vec2(position);
	gravity.xDir = GRAVITY_NONE;
	gravity.yDir = GRAVITY_NONE;
}

void View::SetWidth(ExpansionType type, float width)
{
	expansionStyle.xType = type;
	expansionStyle.width = width;
}

void View::SetHeight(ExpansionType type, float height)
{
	expansionStyle.yType = type;
	expansionStyle.height = height;
}

void View::SetMargins(MarginDirection direction, MarginType type, float amount)
{
	if (direction == MARGIN_LEFT || MARGIN_HORIZONTAL || MARGIN_ALL)
	{
		marginStyle.leftType = type;
		marginStyle.leftAmount = amount;
	}

	if (direction == MARGIN_RIGHT || MARGIN_HORIZONTAL || MARGIN_ALL)
	{
		marginStyle.rightType = type;
		marginStyle.rightAmount = amount;
	}

	if (direction == MARGIN_TOP || MARGIN_VERTICAL || MARGIN_ALL)
	{
		marginStyle.topType = type;
		marginStyle.topAmount = amount;
	}

	if (direction == MARGIN_BOTTOM || MARGIN_VERTICAL || MARGIN_ALL)
	{
		marginStyle.bottomType = type;
		marginStyle.bottomAmount = amount;
	}
}

void View::AddChild(View *view)
{
	view->parent = this;
	view->hasParent = true;
	children.push_back(view);
}

View *View::GetChild(int index)
{
	return children[index];
}

void View::Remeasure()
{
	float leftMargin = marginStyle.CalcLeftMargin(*this);
	float rightMargin = marginStyle.CalcRightMargin(*this);
	float topMargin = marginStyle.CalcTopMargin(*this);
	float bottomMargin = marginStyle.CalcBottomMargin(*this);

	width = expansionStyle.CalcViewWidth(*this, leftMargin, rightMargin);
	height = expansionStyle.CalcViewHeight(*this, topMargin, bottomMargin);
	pos = gravity.CalcViewPosition(*this, leftMargin, rightMargin, topMargin, bottomMargin);
	bounds.Resize(pos, width, height);

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Remeasure();
	}
}

glm::vec2 View::GetPosition() const
{
	return pos;
}

float View::GetWidth() const
{
	return width;
}

float View::GetHeight() const
{
	return height;
}

bool View::OnKeyDown(int key, int mods)
{
	bool handled = false;
	if (onKeyDownListener)
	{
		handled = onKeyDownListener(key, mods);
	}

	for (int i = 0; i < children.size(); i++)
	{
		handled = children[i]->OnKeyDown(key, mods) || handled;
	}

	return handled;
}

bool View::OnKeyUp(int key, int mods)
{
	bool handled = false;
	if (onKeyUpListener)
	{
		handled = onKeyUpListener(key, mods);
	}

	for (int i = 0; i < children.size(); i++)
	{
		handled = children[i]->OnKeyUp(key, mods) || handled;
	}

	return handled;
}

bool View::OnMouseDown(int button, int mods)
{
	glm::vec2 mousePos = context->GetMousePos();

	if (containsMouse)
	{
		pressedDown = true;
	}

	bool handled = false;
	if (onMouseDownListener)
	{
		handled = onMouseDownListener(button, mods);
	}

	for (int i = 0; i < children.size(); i++)
	{

		handled = children[i]->OnMouseDown(button, mods) || handled;
	}

	return handled;
}

bool View::OnMouseUp(int button, int mods)
{
	if (pressedDown && containsMouse)
	{
		if (onClickListener)
		{
			onClickListener(button, mods);
		}
	}

	pressedDown = false;

	bool handled = false;
	if (onMouseUpListener)
	{
		handled = onMouseUpListener(button, mods);
	}

	for (int i = 0; i < children.size(); i++)
	{
		handled = children[i]->OnMouseUp(button, mods) || handled;
	}

	return handled;
}

bool View::OnMouseScroll(float xOffset, float yOffset)
{
	bool handled = false;
	if (onMouseScrollListener)
	{
		handled = onMouseScrollListener(xOffset, yOffset);
	}

	for (int i = 0; i < children.size(); i++)
	{
		if (handled)
		{
			break;
		}

		handled = children[i]->OnMouseScroll(xOffset, yOffset) || handled;
	}

	return handled;
}

bool View::OnMouseMoved(float x, float y)
{
	bool inBounds = bounds.ContainsPoint(glm::vec2(x, y));

	if (inBounds && !containsMouse)
	{
		if (onEnterListener)
		{
			onEnterListener(x, y);
		}
	}

	if (!inBounds && containsMouse)
	{
		if (onExitListener)
		{
			onExitListener(x, y);
		}
	}

	containsMouse = inBounds;

	bool handled = false;
	if (onMouseMovedListener)
	{
		handled = onMouseMovedListener(x, y);
	}

	for (int i = 0; i < children.size(); i++)
	{
		if (handled)
		{
			break;
		}

		handled = children[i]->OnMouseMoved(x, y) || handled;
	}

	return handled;
}

void View::SetOnKeyDownListener(KeyEventListener listener)
{
	onKeyDownListener = listener;
}

void View::SetOnKeyUpListener(KeyEventListener listener)
{
	onKeyUpListener = listener;
}

void View::SetOnMouseDownListener(MouseButtonEventListener listener)
{
	onMouseDownListener = listener;
}

void View::SetOnMouseUpListener(MouseButtonEventListener listener)
{
	onMouseUpListener = listener;
}

void View::SetOnMouseScrollListener(MouseScrollEventListener listener)
{
	onMouseScrollListener = listener;
}

void View::SetOnMouseMovedListener(MouseMovedEventListener listener)
{
	onMouseMovedListener = listener;
}

void View::SetOnClickListener(MouseButtonEventListener listener)
{
	onClickListener = listener;
}

void View::SetOnMouseEnterListener(MouseMovedEventListener listener)
{
	onEnterListener = listener;
}

void View::SetOnMouseExitListener(MouseMovedEventListener listener)
{
	onExitListener = listener;
}