#include "view.h"

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
	gravity.xDir = NONE;
	gravity.yDir = NONE;
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
	width = expansionStyle.CalcViewWidth(*this);
	height = expansionStyle.CalcViewHeight(*this);
	pos = gravity.CalcViewPosition(*this);

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