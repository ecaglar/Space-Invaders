#include "Application.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PhysicManager.h"
#include "SoundManager.h"
#include "Input.h"
#include "GameFont.h"
#include "Font.h"
#include "System.h"
#include <iostream>


Application::Application() : menu_mode(true)
{
	if(menu_mode){

		//show the menu
		SDL_ShowCursor(1);
		menu = new Image();
		start = new Font();
		quit = new Font();
		evil1_point = new Font();
		evil2_point = new Font();
		evil3_point = new Font();
		evil4_point = new Font();
		evil1 = new Image();
		evil2 = new Image();
		evil3 = new Image();
		evil4 = new Image();


		start_pos = Vector2(230,240);
		quit_pos = Vector2(250,330);

		start->loadTtf("../Data/font/arial.ttf", 60);
		quit->loadTtf("../Data/font/arial.ttf", 60);
		menu->loadBmp("../Data/graphics/SpaceInvaders001.bmp");

		evil1->loadBmp("../Data/graphics/evil1/Evil1_035.bmp");
		evil2->loadBmp("../Data/graphics/evil2/Evil2_035.bmp");
		evil3->loadBmp("../Data/graphics/evil3/Evil3_035.bmp");
		evil4->loadBmp("../Data/graphics/evil4/Evil4_035.bmp");

		evil1_point->loadTtf("../Data/font/arial.ttf", 20);
		evil2_point->loadTtf("../Data/font/arial.ttf", 20);
		evil3_point->loadTtf("../Data/font/arial.ttf", 20);
		evil4_point->loadTtf("../Data/font/arial.ttf", 20);

		start->getTextSize("START",start_width, start_height);
		quit->getTextSize("QUIT",quit_width, quit_height);
		
	}
}

Application::~Application()
{
}

bool
Application::update(float deltaTime)
{

	
	deltaTime = deltaTime;
	if(!menu_mode){
		if(SceneManager::Instance()->get_num_of_enemy() == 0 || SceneManager::Instance()->exit)
		{
			SoundManager::Instance()->play_sound("voice_game_over");
			menu_mode = true;
			SDL_ShowCursor(1);

		}else{
			SceneManager::Instance()->tick();
		}
	}else{
		if(Input::mouseDown())
		{
			//check if we click on any menu item
			int x = Input::mousePositionX();
			int y = Input::mousePositionY();
			if((x < start_pos.x + start_width) &&
				x > start_pos.x &&
				y > start_pos.y &&
				y < start_pos.y + start_height )
			{
				SDL_ShowCursor(0);
			
				init_scene();
				menu_mode = false;
				SceneManager::Instance()->exit = false;
				SoundManager::Instance()->play_sound("voice_get_ready");
			}

			if((x < quit_pos.x + quit_width) &&
				x > quit_pos.x &&
				y > quit_pos.y &&
				y < quit_pos.y + quit_height )
			{
				return false;
			}		
		}	
	}
	// Insert code here :o) return false when you want to quit the application
	return true;
}

void
Application::render() const
{
	static float r = 0.0f; 

	// Insert render code here
	if(!menu_mode){
		SceneManager::Instance()->draw();
	}else{
		menu->render(-80,-100,1.0f);
		
		start->render("START",start_pos.x,start_pos.y,1.0f,1.0f,1.0f);
		quit->render("QUIT",quit_pos.x,quit_pos.y,1.0f,1.0f,1.0f);

		evil1->render(450,100);
		evil2->render(450,170);
		evil3->render(450,240);
		evil4->render(450,310);

		evil1_point->render("10 Points",520,120,1.0f,1.0f,1.0f);
		evil2_point->render("20 Points",520,190,1.0f,1.0f,1.0f);
		evil3_point->render("30 Points",520,260,1.0f,1.0f,1.0f);
		evil4_point->render("40 Points",520,330,1.0f,1.0f,1.0f);
	}	
}

void Application::init_scene()
{
	//creates the level

	PhysicManager::Instance()->clean();
	ResourceManager::Instance()->clean();
	
	 SceneManager::Instance()->clean();
	
	ResourceManager::Instance()->loadSprites();
	SoundManager::Instance()->init();
	//scene_manager = SceneManager::Instance();
	SceneManager::Instance()->add_manager(PhysicManager::Instance());


	Sprite* icons[3]; 
	Sprite* defender = static_cast<Sprite*>(ResourceManager::Instance()->get_copy_of("defender"));
	Sprite* background = static_cast<Sprite*>(ResourceManager::Instance()->get_copy_of("background"));
	icons[0] = static_cast<Sprite*>(ResourceManager::Instance()->get_copy_of("life_icon"));
	icons[1] = static_cast<Sprite*>(ResourceManager::Instance()->get_copy_of("life_icon"));
	icons[2] = static_cast<Sprite*>(ResourceManager::Instance()->get_copy_of("life_icon"));

	icons[0]->SetPosition(Vector2(500,5));
	icons[1]->SetPosition(Vector2(540,5));
	icons[2]->SetPosition(Vector2(580,5));

	defender->SetPosition(Vector2(200,400));
	defender->SetCurrent_frame(10);

	Input::setMousePosition(200,400);
	SceneManager::Instance()->add_entity(background);
	SceneManager::Instance()->add_entity(defender);
	SceneManager::Instance()->add_entity(icons[0]);
	SceneManager::Instance()->add_entity(icons[1]);
	SceneManager::Instance()->add_entity(icons[2]);

	Entity* devil  = 0;
	for(int i = 0 ; i < 8 ; i++){
		
		devil = ResourceManager::Instance()->get_copy_of("evil1");

		Vector2 pos = Vector2(30 + i*64,100);
		devil->SetPosition(pos);
		devil->SetSpawnPos(pos);
		SceneManager::Instance()->add_entity(devil);
	}
	for(int i = 0 ; i < 8 ; i++){
		
		devil = ResourceManager::Instance()->get_copy_of("evil2");

		Vector2 pos = Vector2(20 + i*64,160);
		devil->SetPosition(pos);
		devil->SetSpawnPos(pos);
		SceneManager::Instance()->add_entity(devil);
	}
	for(int i = 0 ; i < 8 ; i++){
	
		devil = ResourceManager::Instance()->get_copy_of("evil3");

		Vector2 pos = Vector2(30 + i*64,220);
		devil->SetPosition(pos);
		devil->SetSpawnPos(pos);
		SceneManager::Instance()->add_entity(devil);
	}
	GameFont* f = static_cast<GameFont*>(ResourceManager::Instance()->get_copy_of("font"));
	f->SetPosition(Vector2(0,0));
	f->SetRender_text("Score: 0");
	 SceneManager::Instance()->add_entity(f);
	SceneManager::Instance()->setScoreBoard(f);

}
