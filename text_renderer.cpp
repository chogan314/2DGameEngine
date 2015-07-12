#include "text_renderer.h"
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

TextRenderer::TextRenderer(Shader *shader, int width, int height)
: shader(shader), width(width), height(height)
{
	Init();
}

void TextRenderer::RenderText(Font &font, std::string text, 
	float x, float y, float scale, glm::vec3 color)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glm::mat4 projection = glm::ortho(0.0f, (float) width, 0.0f, (float) height);
	glm::mat4 projection = glm::ortho(0.0f, (float) width, (float) height, 0.0f);
	glm::vec4 transform = projection * glm::vec4(x, y, 0, 1);

	//std::cout << "(" << transform.x << ", " << transform.y << ", " << transform.z << ", " << transform.w << ")" << std::endl;

	shader->Use();
	shader->SetVector3f("textColor", color);
	shader->SetMatrix4("projection", projection);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = font.GetCharacter(*c);
		
		float xPos = x + ch.bearing.x * scale;
		float yPos = y + (font.GetCharacter('H').bearing.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		GLfloat vertices[6][4] = {
			{ xPos,     yPos,     0, 0 },
			{ xPos,     yPos + h, 0, 1 },
			{ xPos + w, yPos + h, 1, 1 },

			{ xPos,     yPos,     0, 0 },
			{ xPos + w, yPos + h, 1, 1 },
			{ xPos + w, yPos,     1, 0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureId);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}