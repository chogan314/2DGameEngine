#include "aabb.h"

bool AABB::ContainsPoint(const glm::vec2 &point)
{
	return point.x >= pos.x &&
		point.x <= pos.x + width &&
		point.y >= pos.y &&
		point.y <= pos.y + height;
}