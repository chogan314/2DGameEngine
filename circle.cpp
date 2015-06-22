#include "circle.h"

bool Circle::ContainsPoint(const glm::vec2 &point)
{
	return glm::distance(pos, point) <= radius;
}