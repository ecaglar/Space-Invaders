#ifndef Font_h
#define Font_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font();
	~Font();

	void loadTtf(const std::string& filename, unsigned int size);

	void render(const std::string& text, int x, int y, float r, float g, float b) const;

	unsigned int height() const;

	void getTextSize(const std::string& text, unsigned int& width, unsigned int &height) const;

private:
	Font(const Font&);
	Font& operator=(const Font&);

	TTF_Font* m_font;
};

#endif
