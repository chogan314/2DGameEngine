#include "texture_region.h"

TextureRegion::TextureRegion(Texture *texture) : texture(texture)
{}

TextureRegion::TextureRegion(Texture *texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
: texture(texture), u(x), v(y), u2(x + width), v2(y + height)
{}

TextureRegion::~TextureRegion()
{
	delete texture;
}

void TextureRegion::SetRegionRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	u = x;
	v = y;
	u2 = x + width;
	v2 = y + height;
}

void TextureRegion::SetRegionPoints(GLfloat u, GLfloat v, GLfloat u2, GLfloat v2)
{
	this->u = u;
	this->v = v;
	this->u2 = u2;
	this->v2 = v2;
}

Texture *TextureRegion::GetTexture()
{
	return texture;
}

GLfloat TextureRegion::GetU() const
{
	return u / texture->GetWidth();
}

GLfloat TextureRegion::GetV() const
{
	return v / texture->GetHeight();
}

GLfloat TextureRegion::GetU2() const
{
	return u2 / texture->GetWidth();
}

GLfloat TextureRegion::GetV2() const
{
	return v2 / texture->GetHeight();
}
