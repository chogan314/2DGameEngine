#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <glm\glm.hpp>
#include <functional>
#include "aabb.h"
#include "input_handler.h"

class Screen;

typedef std::function<bool(int key, int mods)> KeyEventListener;
typedef std::function<bool(int button, int mods)> MouseButtonEventListener;
typedef std::function<bool(float xOffset, float yOffset)> MouseScrollEventListener;
typedef std::function<bool(float x, float y)> MouseMovedEventListener;

enum GravityDirection
{
	GRAVITY_POSITIVE,
	GRAVITY_NEGATIVE,
	GRAVITY_CENTER,
	GRAVITY_NONE
};

enum MarginType
{
	MARGIN_PERCENT,
	MARGIN_ABSOLUTE
};

enum MarginDirection
{
	MARGIN_LEFT,
	MARGIN_RIGHT,
	MARGIN_TOP,
	MARGIN_BOTTOM,
	MARGIN_HORIZONTAL,
	MARGIN_VERTICAL,
	MARGIN_ALL
};

enum ExpansionType
{
	EXPANSION_FILL_PARENT,
	EXPANSION_PERCENT_PARENT,
	EXPANSION_ABSOLUTE
};

class View : public InputHandler
{
public:
	View(Screen *screen);
	virtual ~View();

	void SetGravity(GravityDirection xDirection, GravityDirection yDirection);
	void SetPosition(const glm::vec2 &position);
	void SetWidth(ExpansionType type, float width);
	void SetHeight(ExpansionType type, float height);
	void SetMargins(MarginDirection direction, MarginType type, float amount);

	void AddChild(View *view);
	View *GetChild(int index);
	void Remeasure();

	glm::vec2 GetPosition() const;
	float GetWidth() const;
	float GetHeight() const;

	bool OnKeyDown(int key, int mods);
	bool OnKeyUp(int key, int mods);
	bool OnMouseDown(int button, int mods);
	bool OnMouseUp(int button, int mods);
	bool OnMouseScroll(float xOffset, float yOffset);
	bool OnMouseMoved(float x, float y);
	bool OnClick(int button, int mods);

	void SetOnKeyDownListener(KeyEventListener listener);
	void SetOnKeyUpListener(KeyEventListener listener);
	void SetOnMouseDownListener(MouseButtonEventListener listener);
	void SetOnMouseUpListener(MouseButtonEventListener listener);
	void SetOnMouseScrollListener(MouseScrollEventListener listener);
	void SetOnMouseMovedListener(MouseMovedEventListener listener);
	void SetOnClickListener(MouseButtonEventListener listener);

private:
	struct Gravity
	{
		glm::vec2 defaultPos;
		GravityDirection xDir = GRAVITY_NEGATIVE;
		GravityDirection yDir = GRAVITY_NEGATIVE;

		glm::vec2 CalcViewPosition(const View &view, float leftMargin, float rightMargin, float topMargin, float bottomMargin)
		{
			if (!view.hasParent)
			{
				return defaultPos;
			}

			View &parent = *view.parent;

			glm::vec2 pos;

			switch (xDir)
			{
			case GRAVITY_NEGATIVE:
				pos.x = parent.pos.x + leftMargin;
				break;
			case GRAVITY_POSITIVE:
				pos.x = parent.pos.x + parent.width - view.width - rightMargin;
				break;
			case GRAVITY_CENTER:
				pos.x = parent.pos.x + parent.width / 2 - view.width / 2;
				break;
			case GRAVITY_NONE:
				pos.x = defaultPos.x;
			default:
				break;
			}

			switch (yDir)
			{
			case GRAVITY_NEGATIVE:
				pos.y = parent.pos.y;
				break;
			case GRAVITY_POSITIVE:
				pos.y = parent.pos.y + parent.height - view.height;
				break;
			case GRAVITY_CENTER:
				pos.y = parent.pos.y + parent.height / 2 - view.height / 2;
				break;
			case GRAVITY_NONE:
				pos.y = defaultPos.y;
			default:
				break;
			}

			return pos;
		}
	};

	struct MarginStyle
	{
		MarginType leftType = MARGIN_ABSOLUTE;
		MarginType rightType = MARGIN_ABSOLUTE;
		MarginType topType = MARGIN_ABSOLUTE;
		MarginType bottomType = MARGIN_ABSOLUTE;

		float leftAmount = 0.0f;
		float rightAmount = 0.0f;
		float topAmount = 0.0f;
		float bottomAmount = 0.0f;

		float CalcLeftMargin(const View &view)
		{
			if (!view.hasParent)
			{
				return leftAmount;
			}

			return leftType == MARGIN_PERCENT ? leftAmount * view.parent->width : leftAmount;
		}

		float CalcRightMargin(const View &view)
		{
			if (!view.hasParent)
			{
				return rightAmount;
			}

			return rightType == MARGIN_PERCENT ? rightAmount * view.parent->width : rightAmount;
		}

		float CalcTopMargin(const View &view)
		{
			if (!view.hasParent)
			{
				return topAmount;
			}

			return topType == MARGIN_PERCENT ? topAmount * view.parent->height : topAmount;
		}

		float CalcBottomMargin(const View &view)
		{
			if (!view.hasParent)
			{
				return bottomAmount;
			}

			return bottomType == MARGIN_PERCENT ? bottomAmount * view.parent->height : bottomAmount;
		}
	};

	struct ExpansionStyle
	{
		ExpansionType xType = EXPANSION_FILL_PARENT;
		ExpansionType yType = EXPANSION_FILL_PARENT;
		float width = 0.0f;
		float height = 0.0f;

		float CalcViewWidth(const View &view, float leftMargin, float rightMargin)
		{
			if (!view.hasParent)
			{
				return width;
			}

			View &parent = *view.parent;

			switch (xType)
			{
			case EXPANSION_FILL_PARENT:
				return parent.width - leftMargin - rightMargin;
				break;
			case EXPANSION_PERCENT_PARENT:
				return parent.width * width;
				break;
			case EXPANSION_ABSOLUTE:
				return width;
				break;
			default:
				return width;
				break;
			}
		}

		float CalcViewHeight(const View &view, float topMargin, float bottomMargin)
		{
			if (!view.hasParent)
			{
				return height;
			}

			View &parent = *view.parent;

			switch (yType)
			{
			case EXPANSION_FILL_PARENT:
				return parent.height - topMargin - bottomMargin;
				break;
			case EXPANSION_PERCENT_PARENT:
				return parent.height* height;
				break;
			case EXPANSION_ABSOLUTE:
				return height;
				break;
			default:
				return height;
				break;
			}
		}
	};

	Screen *context = nullptr;
	View *parent = nullptr;
	bool hasParent = false;
	std::vector<View *> children;

	glm::vec2 pos;
	float width;
	float height;

	Gravity gravity;
	MarginStyle marginStyle;
	ExpansionStyle expansionStyle;

	AABB bounds;

	KeyEventListener onKeyDownListener = nullptr;
	KeyEventListener onKeyUpListener = nullptr;
	MouseButtonEventListener onMouseDownListener = nullptr;
	MouseButtonEventListener onMouseUpListener = nullptr;
	MouseScrollEventListener onMouseScrollListener = nullptr;
	MouseMovedEventListener onMouseMovedListener = nullptr;
	MouseButtonEventListener onClickListener = nullptr;

	bool pressedDown = false;
};

#endif