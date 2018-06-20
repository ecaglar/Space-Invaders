#pragma once

/************************************************************************/
/* Bounding box of any game objects. used for collision detection
X and Y is top-left corner coordinate and with and height is values of the bounding box
*/
/************************************************************************/
class BoundingBox
{
public:
	BoundingBox(int x, int y, unsigned int width, unsigned int height);
	BoundingBox(){};
	~BoundingBox(void);

	int x;
	int y;
	unsigned int width;
	unsigned int height;
};

