#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "font.h"
#include "shader.h"

class TextRenderer
{
public:
	TextRenderer(Shader *shader, int width, int height);
	void RenderText(Font &font, std::string text, float x, float y, float scale, glm::vec3 color);
private:
	Shader *shader;
	GLuint VAO, VBO;
	int width;
	int height;

	void Init();
};

#endif