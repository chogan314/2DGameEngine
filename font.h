#ifndef FONT_H
#define FONT_H

#include <map>
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
	GLuint textureId;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};

class Font
{
public:
	Font(std::string filePath, int size);
	Character GetCharacter(GLchar c);
private:
	std::map<GLchar, Character> characters;
};

#endif