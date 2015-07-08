#ifndef AABB_H
#define AABB_H

#include "intersectable.h"

class AABB : public Intersectable
{
public:
	AABB(float width = 1.0f, float height = 1.0f, const glm::vec2 &position = glm::vec2(0, 0)) :
		pos(position),
		width(width),
		height(height) { }

	bool ContainsPoint(const glm::vec2 &point);

	void Resize(const glm::vec2 &position, float width, float height);

private:
	glm::vec2 pos;
	float width;
	float height;
};

#endif