#pragma once

#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>
#include "IManager.h"
#include "Singleton.h"
#include "Entity.h"
#include "GameFont.h"
#include "SDL.h"
class Entity;

/*

It is the core of the game. It handles all the game objects, their logics and
other managers. It handles game play as well. Stores all the game elements, updated them and
updates the manager for their specific jobs(Collision for PhysicManager etc)

Managers which implements the IManager interface and added to scene manager
is going to be updated by scene manager every frame. 

*/
class SceneManager : public IManager, public Singleton<SceneManager>
{
	public:
		void tick();
		void clean();

		void add_manager(IManager*);		//add manager to scene manager so that it can be called by scene manager every frame
		void add_entity(Entity*);			//adds game object (entity) to the manager. So that they can be rendered and updated aoutomaticly
		void remove_entity(Entity*);		//removes the game entity from manager
		void clean_up();

		//callback function to notify scene manager from physic manager when a collision occurs
		//Scene manager and physic manager communicates using this callback.
		void on_collision(Entity* collider1, Entity* collider2); 

		//TO DO: make it static dont take it with function call
		Entity* get_defender(); //returns the defender for easy access
		int get_num_of_enemy() ; //returns the number of enemy ships left
		void draw();			//render function

		void spawn_entity(ENTITY_TYPE type, Vector2 location); //spawn an entity with given type at given location
		void setScoreBoard(GameFont*);	// sets score board with given game text so that we can update it with current score
		int Total_score() const { return total_score; } //gets the total score
		bool exit;	//exit game?
		
protected:
	SceneManager(void) : evil_move_dir(true){
		old_ticks = SDL_GetTicks();		//stores first tick when scene manager is initialized
		srand ( time(NULL) );			//seed the randomizer
		devil_shot_swapn_time = 1000;	//first initial value for creating enemy shot
		total_score = 0;				//init total score
		exit = false;
	};
	~SceneManager(void){};

private:
		std::vector<IManager*> m_managers;		//stores the game related managers
		std::vector<Entity*> m_entities;		//game objects
		friend class Singleton<SceneManager>;
		Entity* defender;						
		bool evil_move_dir;						//direction for enemy ships if they will move to the right or left
		Uint32 old_ticks;						//stores the old tick after updating new tick

		std::map<Entity*, Entity*> collision_tester;	//use to prevent getting multiple collision while shot is passing through the object
		GameFont* score_board;
		int devil_shot_swapn_time;
		int total_score;
		
	



};

