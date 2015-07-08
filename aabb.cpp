#include "aabb.h"

bool AABB::ContainsPoint(const glm::vec2 &point)
{
	return point.x >= pos.x &&
		point.x <= pos.x + width &&
		point.y >= pos.y &&
		point.y <= pos.y + height;
}

void AABB::Resize(const glm::vec2 &position, float width, float height)
{
	pos = glm::vec2(position);
	this->width = width;
	this->height = height;
}