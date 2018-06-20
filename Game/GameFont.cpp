#include "GameFont.h"
#include "Font.h"

GameFont::GameFont(std::string name,int font_size,float r, float g, float b) : Entity(RENDER2D, FONT)
{
	font_name = name;
	blue = b;
	green = g;
	red = r;
	size = font_size;
	font = new Font();
	font->loadTtf(font_name,size);
	SetPosition(Vector2(0,0));
}


GameFont::~GameFont(void)
{
}

void GameFont::draw()
{
	font->render(render_text,m_position.x, m_position.y,red, green,blue);
}

void GameFont::move()
{

}

void GameFont::animate(std::string anim)
{

}


