#pragma once
#include <string>
#include "Entity.h"

/*
It is the game entity responsible for texts on screen.

*/

class Font;
class GameFont :
	public Entity
{
public:
	GameFont(std::string name,int font_size,float r, float g, float b);
	void render_font(int x, int y);
	~GameFont(void);

	 void move();
	 void animate(std::string);
	 void draw();	//render text

	 std::string GetRender_text() const { return render_text; }
	 void SetRender_text(std::string val) { render_text = val; }
	 int GetSize() const { return size; }
	 void SetSize(int val) { size = val; }
	 void SetFont_name(std::string val) { font_name = val; }
	 std::string GetFont_name() const { return font_name; }
	 void set_color(float r, float g, float b){red = r; green = g; blue = b;}
	 float GetRed() const { return red; }
	 void SetRed(float val) { red = val; }
	 float GetBlue() const { return blue; }
	 void SetBlue(float val) { blue = val; }
	 float GetGreen() const { return green; }
	 void SetGreen(float val) { green = val; }

private:
	Font* font;		//actual font object
	int size;		//size of the font
	float red;		//red component of color
	float green;	//green component of color
	float blue;		//blue component of color
	std::string render_text;	//text to be rendered
	 std::string font_name;		//name of the fond to be loaded
	
	
};

