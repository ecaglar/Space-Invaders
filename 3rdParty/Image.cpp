#include "Image.h"
#include "System.h"
#include "Assert.h"

Image::Image() :
	m_surface(0)
{
}

Image::~Image()
{
	SDL_FreeSurface(m_surface);
}

void
Image::loadBmp(const std::string& filename)
{
	ASSERT_DESCRIPTION(!filename.empty(), "Cannot load image without a filename!");

	m_surface = SDL_LoadBMP(filename.c_str());
	ASSERT_DESCRIPTION(m_surface, "SDL_LoadBMP failed: " << SDL_GetError());

	m_surface = SDL_DisplayFormat(m_surface);
	ASSERT_DESCRIPTION(m_surface, "SDL_DisplayFormat failed: " << SDL_GetError());

	ASSERT_RESULT_DECL(const int result, SDL_SetColorKey(m_surface, SDL_SRCCOLORKEY, 
														SDL_MapRGB(m_surface->format, 255, 0, 255)));
	ASSERT_DESCRIPTION(result == 0, "SDL_SetColorKey failed: " << SDL_GetError());
}

void
Image::getSize(unsigned int& width, unsigned int& height) const
{
	ASSERT_DESCRIPTION(m_surface, "No image surface exists! Did you forget to call loadBmp?" << SDL_GetError());
	width = m_surface->w;
	height = m_surface->h;
}

void
Image::render(int x, int y, float alpha) const
{
	ASSERT_DESCRIPTION(m_surface, "No image surface exists! Did you forget to call loadBmp?");
	ASSERT_DESCRIPTION(alpha >= 0.0f && alpha <= 1.0f, "alpha must be a value between 0.0 and 1.0! alpha = " << alpha);

	SDL_Rect destinationRect;
	destinationRect.x = static_cast<Sint16>(x);
	destinationRect.y = static_cast<Sint16>(y);
	destinationRect.w = static_cast<Sint16>(m_surface->w);
	destinationRect.h = static_cast<Sint16>(m_surface->h);

	SDL_Rect sourceRect;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = static_cast<Sint16>(m_surface->w);
	sourceRect.h = static_cast<Sint16>(m_surface->h);

	ASSERT_RESULT_DECL(const int sdlSetAlphaResult, SDL_SetAlpha(m_surface, SDL_SRCALPHA, static_cast<Uint8>(alpha * 255.0f)));
	ASSERT_DESCRIPTION(sdlSetAlphaResult == 0, "SDL_SetAlpha failed: " << SDL_GetError());

	ASSERT_RESULT_DECL(int sdlBlitSurfaceResult, SDL_BlitSurface(m_surface, &sourceRect, System::screenSurface(), &destinationRect));
	ASSERT_DESCRIPTION(sdlBlitSurfaceResult == 0, "SDL_BlitSurface failed: " << SDL_GetError());
}