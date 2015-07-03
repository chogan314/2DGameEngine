#include "primitive_renderer.h"
#include <glm\gtc\matrix_transform.hpp>

PrimitiveRenderer::PrimitiveRenderer(Shader * const shader) : shader(shader)
{
	InitRenderData();
}

PrimitiveRenderer::~PrimitiveRenderer()
{
	glDeleteVertexArrays(1, &VAO);
}

void PrimitiveRenderer::SetContextSize(GLint width, GLint height)
{
	contextWidth = width;
	contextHeight = height;
}

void PrimitiveRenderer::DrawTriangle(
	const glm::vec2 &pointA,
	const glm::vec2 &pointB,
	const glm::vec2 &pointC,
	const glm::vec4 &color)
{
	shader->Use();
	shader->SetVector4f("spriteColor", color);

	GLfloat vertices[] = {
		ToGLSpace(pointA.x, false), ToGLSpace(pointA.y, true),
		ToGLSpace(pointB.x, false), ToGLSpace(pointB.y, true),
		ToGLSpace(pointC.x, false), ToGLSpace(pointC.y, true)
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

void PrimitiveRenderer::DrawRectangle(
	const glm::vec2 &position,
	float width,
	float height,
	const glm::vec4 &color)
{
	shader->Use();
	shader->SetVector4f("spriteColor", color);

	GLfloat vertices[] = {
		ToGLSpace(position.x, false), ToGLSpace(position.y + height, true),
		ToGLSpace(position.x + width, false), ToGLSpace(position.y, true),
		ToGLSpace(position.x, false), ToGLSpace(position.y, true),

		ToGLSpace(position.x, false), ToGLSpace(position.y + height, true),
		ToGLSpace(position.x + width, false), ToGLSpace(position.y + height, true),
		ToGLSpace(position.x + width, false), ToGLSpace(position.y, true)
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

void PrimitiveRenderer::DrawPoint(const glm::vec2 &point, const glm::vec4 &color)
{
	DrawRectangle(point, 1, 1, color);
}

void PrimitiveRenderer::InitRenderData()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 2, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

float PrimitiveRenderer::ToGLSpace(float value, bool isYCoord)
{
	float newVal = 0.0f;

	if (isYCoord)
	{
		newVal = (value / contextHeight) * 2 - 1;
		newVal *= -1;
	}
	else
	{
		newVal = (value / contextWidth) * 2 - 1;
	}

	return newVal;
}