#ifndef INTERSECTABLE
#define INTERSECTABLE

#include <glm\glm.hpp>

class Intersectable
{
public:
	virtual bool ContainsPoint(const glm::vec2 &point) = 0;
};

#endif