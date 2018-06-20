#include "BoundingBox.h"


BoundingBox::BoundingBox(int x, int y,unsigned int width, unsigned int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
BoundingBox::~BoundingBox(void)
{
}
