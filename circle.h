#ifndef CIRCLE_H
#define CIRCLE_H

#include "intersectable.h"

class Circle : public Intersectable
{
public:
	Circle(float radius, const glm::vec2 &position = glm::vec2(0, 0)) :
		radius(radius),
		pos(position) { }

	bool ContainsPoint(const glm::vec2 &point);

private:
	glm::vec2 pos;
	float radius;
};

#endif