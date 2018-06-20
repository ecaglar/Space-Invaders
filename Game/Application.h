#ifndef Application_h
#define Application_h
#include "Image.h"
#include "Vector2.h"

class Sprite;
class SceneManager;
class Font;
class Application
{
public:
	Application();
	virtual ~Application();

	bool update(float deltaTime);

	void render() const;
private:
	SceneManager* scene_manager;
	Sprite* defender;
	Sprite* defender2;
	Sprite* background;

	//GUI components they are created with native calls to SDL
	bool menu_mode;
	Image* menu;
	Font* start;
	Font* quit;
	Vector2 start_pos;
	Vector2 quit_pos;
	unsigned int start_width,start_height;
	unsigned int quit_width,quit_height;

	Image* evil1;
	Image* evil2;
	Image* evil3;
	Image* evil4;
	
	Font* evil1_point;
	Font* evil2_point;
	Font* evil3_point;
	Font* evil4_point;

	void init_scene();
	
};

#endif
