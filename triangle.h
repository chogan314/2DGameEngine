#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "intersectable.h"

class Triangle : public Intersectable
{
public:
	Triangle(const glm::vec2 &pointA, const glm::vec2 &pointB, const glm::vec2 &pointC) :
		a(pointA),
		b(pointB),
		c(pointC) { }

	bool ContainsPoint(const glm::vec2 &point);

	glm::vec2 &GetPointA();
	glm::vec2 &GetPointB();
	glm::vec2 &GetPointC();

private:
	glm::vec2 a;
	glm::vec2 b;
	glm::vec2 c;

	bool PointInRegion(
		const glm::vec2 &lineStart, 
		const glm::vec2 &lineEnd,
		const glm::vec2 &otherPoint,
		const glm::vec2 &testPoint,
		bool edgeInclusive = true);
};

#endif