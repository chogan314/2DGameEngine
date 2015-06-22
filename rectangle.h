#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm\glm.hpp>

class Rectangle
{
public:
	Rectangle(const glm::vec2 &pointA,
		const glm::vec2 &pointB,
		const glm::vec2 &pointC,
		const glm::vec2 &pointD) :
		a(pointA),
		b(pointB),
		c(pointC),
		d(pointD) { }

private:
	glm::vec2 a;
	glm::vec2 b;
	glm::vec2 c;
	glm::vec2 d;
};

#endif