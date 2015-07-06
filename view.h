#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <glm\glm.hpp>
#include "aabb.h"

enum GravityDirection
{
	POSITIVE,
	NEGATIVE,
	CENTER,
	NONE
};

enum ExpansionType
{
	FILL_PARENT,
	PERCENT_PARENT,
	ABSOLUTE
};

class View
{
public:
	~View();

	void SetGravity(GravityDirection xDirection, GravityDirection yDirection);
	void SetPosition(const glm::vec2 &position);
	void SetWidth(ExpansionType type, float width);
	void SetHeight(ExpansionType type, float height);

	void AddChild(View *view);
	View *GetChild(int index);
	void Remeasure();

	glm::vec2 GetPosition() const;
	float GetWidth() const;
	float GetHeight() const;

private:
	struct Gravity
	{
		glm::vec2 defaultPos;
		GravityDirection xDir = NEGATIVE;
		GravityDirection yDir = NEGATIVE;

		glm::vec2 CalcViewPosition(const View &view)
		{
			if (!view.hasParent)
			{
				return defaultPos;
			}

			View &parent = *view.parent;

			glm::vec2 pos;

			switch (xDir)
			{
			case NEGATIVE:
				pos.x = parent.pos.x;
				break;
			case POSITIVE:
				pos.x = parent.pos.x + parent.width - view.width;
				break;
			case CENTER:
				pos.x = parent.pos.x + parent.width / 2 - view.width / 2;
				break;
			case NONE:
				pos.x = defaultPos.x;
			default:
				break;
			}

			switch (yDir)
			{
			case NEGATIVE:
				pos.y = parent.pos.y;
				break;
			case POSITIVE:
				pos.y = parent.pos.y + parent.height - view.height;
				break;
			case CENTER:
				pos.y = parent.pos.y + parent.height / 2 - view.height / 2;
				break;
			case NONE:
				pos.y = defaultPos.y;
			default:
				break;
			}

			return pos;
		}
	};

	struct ExpansionStyle
	{
		ExpansionType xType = FILL_PARENT;
		ExpansionType yType = FILL_PARENT;
		float width = 0.0f;
		float height = 0.0f;

		float CalcViewWidth(const View &view)
		{
			if (!view.hasParent)
			{
				return width;
			}

			View &parent = *view.parent;

			switch (xType)
			{
			case FILL_PARENT:
				return parent.width;
				break;
			case PERCENT_PARENT:
				return parent.width * width;
				break;
			case ABSOLUTE:
				return width;
				break;
			default:
				break;
			}
		}

		float CalcViewHeight(const View &view)
		{
			if (!view.hasParent)
			{
				return height;
			}

			View &parent = *view.parent;

			switch (yType)
			{
			case FILL_PARENT:
				return parent.height;
				break;
			case PERCENT_PARENT:
				return parent.height * height;
				break;
			case ABSOLUTE:
				return height;
				break;
			default:
				break;
			}
		}
	};

	View *parent = nullptr;
	bool hasParent = false;
	std::vector<View *> children;

	glm::vec2 pos;
	float width;
	float height;

	ExpansionStyle expansionStyle;
	Gravity gravity;
};

#endif