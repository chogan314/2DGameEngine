#include "sprite_renderer.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

SpriteRenderer::SpriteRenderer(Shader *shader) : shader(*shader), lastTexture(nullptr)
{
	InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::Draw(
	const Texture &texture,
	const glm::vec2 &position, 
	GLfloat width, 
	GLfloat height,
	GLfloat rotation, 
	const glm::vec4 &color)
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));

	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	shader.Use();

	shader.SetMatrix4("model", model);
	shader.SetVector4f("spriteColor", color);

	GLfloat vertices[] = {
		// Pos	    // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	texture.Bind();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	texture.Unbind();
}

void SpriteRenderer::Draw(
	TextureRegion &textureRegion,
	const glm::vec2 &position,
	GLfloat width,
	GLfloat height,
	GLfloat rotation,
	const glm::vec4 &color)
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));

	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	shader.Use();

	shader.SetMatrix4("model", model);
	shader.SetVector4f("spriteColor", color);

	float u = textureRegion.GetU();
	float v = textureRegion.GetV();
	float u2 = textureRegion.GetU2();
	float v2 = textureRegion.GetV2();

	GLfloat vertices[] = {
		// Pos	    // Tex
		0.0f, 1.0f, u, v2,
		1.0f, 0.0f, u2, v,
		0.0f, 0.0f, u, v,

		0.0f, 1.0f, u, v2,
		1.0f, 1.0f, u2, v2,
		1.0f, 0.0f, u2, v
	};

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	textureRegion.GetTexture()->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	textureRegion.GetTexture()->Unbind();
}

void SpriteRenderer::DrawWithRotationAroundOrigin(
	TextureRegion &textureRegion,
	const glm::vec2 &position,
	GLfloat width,
	GLfloat height,
	GLfloat rotation,
	const glm::vec4 &color)
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));

	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	shader.Use();

	shader.SetMatrix4("model", model);
	shader.SetVector4f("spriteColor", color);

	float u = textureRegion.GetU();
	float v = textureRegion.GetV();
	float u2 = textureRegion.GetU2();
	float v2 = textureRegion.GetV2();

	GLfloat vertices[] = {
		// Pos	    // Tex
		0.0f, 1.0f, u, v2,
		1.0f, 0.0f, u2, v,
		0.0f, 0.0f, u, v,

		0.0f, 1.0f, u, v2,
		1.0f, 1.0f, u2, v2,
		1.0f, 0.0f, u2, v
	};

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	textureRegion.GetTexture()->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	textureRegion.GetTexture()->Unbind();
}

void SpriteRenderer::InitRenderData()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) (2 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}