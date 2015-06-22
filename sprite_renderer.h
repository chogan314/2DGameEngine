#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"
#include "texture_region.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader *shader);
	~SpriteRenderer();

	void Draw(
		const Texture &texture,
		const glm::vec2 &position,
		GLfloat width,
		GLfloat height,
		GLfloat rotation = 0.0f,
		const glm::vec4 &color = glm::vec4(1.0f));

	void Draw(
		TextureRegion &textureRegion,
		const glm::vec2 &position,
		GLfloat width,
		GLfloat height,
		GLfloat rotation = 0.0f,
		const glm::vec4 &color = glm::vec4(1.0f));

	void DrawWithRotationAroundOrigin(
		TextureRegion &textureRegion,
		const glm::vec2 &position,
		GLfloat width, GLfloat height,
		GLfloat rotation = 0.0f,
		const glm::vec4 &color = glm::vec4(1.0f));

private:
	Shader &shader;
	GLuint VAO;
	GLuint VBO;
	const Texture *lastTexture;

	void InitRenderData();
};

#endif