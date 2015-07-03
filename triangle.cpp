#include "triangle.h"

bool Triangle::ContainsPoint(const glm::vec2 &point)
{
	return PointInRegion(a, b, c, point) &&
		PointInRegion(a, c, b, point) &&
		PointInRegion(b, c, a, point);
}

glm::vec2 &Triangle::GetPointA()
{
	return a;
}

glm::vec2 &Triangle::GetPointB()
{
	return b;
}

glm::vec2 &Triangle::GetPointC()
{
	return c;
}

bool Triangle::PointInRegion(
	const glm::vec2 &lineStart,
	const glm::vec2 &lineEnd,
	const glm::vec2 &otherPoint,
	const glm::vec2 &testPoint,
	bool edgeInclusive)
{
	glm::vec2 lineVec = glm::normalize(lineEnd - lineStart);
	glm::vec2 targetVec = glm::normalize(otherPoint - lineStart);
	glm::vec2 testVec = glm::normalize(testPoint - lineStart);
	glm::vec2 perpendicularVec = glm::vec2(-lineVec.y, lineVec.x);

	float targetDot = glm::dot(targetVec, perpendicularVec);
	float testDot = glm::dot(testVec, perpendicularVec);

	if (testDot == 0)
	{
		return edgeInclusive;
	}

	return (targetDot < 0 && testDot < 0) ||
		(targetDot > 0 && testDot > 0);
}