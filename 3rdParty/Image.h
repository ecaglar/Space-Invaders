#ifndef Image_h
#define Image_h

#include <SDL.h>
#include <string>

class Image
{
public:
	Image();
	~Image();

	void loadBmp(const std::string& fileName);

	void getSize(unsigned int& width, unsigned int& height) const;

	void render(int x, int y, float alpha = 1.0f) const;

private:
	Image(const Image&);
	Image& operator=(const Image&);

	SDL_Surface* m_surface;
};

#endif
