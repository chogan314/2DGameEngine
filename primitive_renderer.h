#ifndef PRIMITIVE_RENDERER_H
#define PRIMITIVE_RENDERER_H

#include "shader.h"

class PrimitiveRenderer
{
public:
	PrimitiveRenderer(Shader * const shader);
	~PrimitiveRenderer();

	void SetContextSize(GLint width, GLint height);

	void DrawTriangle(
		const glm::vec2 &pointA,
		const glm::vec2 &pointB,
		const glm::vec2 &pointC,
		const glm::vec4 &color = glm::vec4(1.0f));

	void DrawRectangle(
		const glm::vec2 &position,
		float width,
		float height,
		const glm::vec4 &color = glm::vec4(1.0f));

	void DrawPoint(const glm::vec2 &point, const glm::vec4 &color = glm::vec4(1.0f));

private:
	Shader *shader;
	GLuint VAO;
	GLuint VBO;

	GLint contextWidth = 1;
	GLint contextHeight = 1;

	void InitRenderData();

	float ToGLSpace(float value, bool isYCoord);
};

#endif