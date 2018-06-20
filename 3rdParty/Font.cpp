#include "Font.h"
#include "System.h"
#include "Assert.h"

Font::Font() :
	m_font(0)
{
}

Font::~Font()
{
	TTF_CloseFont(m_font);
}

void
Font::loadTtf(const std::string& filename, unsigned int size)
{
	ASSERT_DESCRIPTION(!filename.empty(), "Cannot load font without a filename!");
	m_font = TTF_OpenFont(filename.c_str(), size);
	ASSERT_DESCRIPTION(m_font, "TTF_OpenFont failed: " << TTF_GetError());
}

void
Font::render(const std::string& text, int x, int y, float r, float g, float b) const
{
	ASSERT_DESCRIPTION(m_font, "No font exists! Did you forget to call loadTtf?");
	ASSERT_DESCRIPTION(!text.empty(), "Trying to render empty string of text!");
	ASSERT_DESCRIPTION(r >= 0.0f && r <= 1.0f, "r must be a value between 0.0 and 1.0! r = " << r);
	ASSERT_DESCRIPTION(g >= 0.0f && g <= 1.0f, "g must be a value between 0.0 and 1.0! g = " << g);
	ASSERT_DESCRIPTION(b >= 0.0f && b <= 1.0f, "b must be a value between 0.0 and 1.0! b = " << b);

	const SDL_Color forgroundColor = { static_cast<Uint8>(r * 255.0f), static_cast<Uint8>(g * 255.0f), static_cast<Uint8>(b * 255.0f), 0};
	SDL_Surface *textSurface = TTF_RenderText_Blended(m_font, text.c_str(), forgroundColor);
	ASSERT_DESCRIPTION(textSurface, "TTF_RenderText_Blended failed: " << TTF_GetError());

	SDL_Rect rect = {static_cast<Sint16>(x), static_cast<Sint16>(y), 0, 0};
	SDL_BlitSurface(textSurface, 0, System::screenSurface(), &rect);

	ASSERT_RESULT_DECL(const int sdlBlitSurfaceResult, SDL_BlitSurface(textSurface, 0, System::screenSurface(), &rect));
	ASSERT_DESCRIPTION(sdlBlitSurfaceResult == 0, "SDL_BlitSurface failed: " << SDL_GetError());

	SDL_FreeSurface(textSurface);
}

unsigned int
Font::height() const
{
	ASSERT_DESCRIPTION(m_font, "No font exists! Did you forget to call loadTtf?");
	return TTF_FontHeight(m_font);
}

void
Font::getTextSize(const std::string& text, unsigned int& width, unsigned int& height) const
{
	int textWidth;
	int textHeight;
	ASSERT_RESULT_DECL(const int result, TTF_SizeText(m_font, text.c_str(), &textWidth, &textHeight));
	ASSERT_DESCRIPTION(result == 0, "TTF_SizeText failed: " << TTF_GetError());

	width = textWidth;
	height = textHeight;
}
