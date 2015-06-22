#ifndef TEXTURE_REGION_H
#define TEXTURE_REGION_H

#include "texture.h"

class TextureRegion
{
public:
	TextureRegion(Texture *texture);
	TextureRegion(Texture *texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	~TextureRegion();

	void SetRegionRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	void SetRegionPoints(GLfloat u, GLfloat v, GLfloat u2, GLfloat v2);

	Texture *GetTexture();
	GLfloat GetU() const;
	GLfloat GetV() const;
	GLfloat GetU2() const;
	GLfloat GetV2() const;
private:
	Texture *texture;
	GLfloat u, v;
	GLfloat u2, v2;
};

#endif