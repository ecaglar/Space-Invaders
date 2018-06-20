#pragma once
#include <vector>
#include "IManager.h"
#include "Singleton.h"
#include "SceneManager.h"
#include "PhysicObject.h"

class PhysicObject;
class Entity;


/************************************************************************/
/* Responsible for physic related game logic. For our game physic manager
handles only collision detection but it can be extended for further needs
Physic managers can make calculation on physic objects only. So that
you should add the game object to the physic manager as physic object so that
Physic manager can handle it.*/
/************************************************************************/
class PhysicManager :	public IManager, public Singleton<PhysicManager>
{
public:
	
	//handles every frame related physic calculations
	void tick();
	void clean();
	//Adds game entities to the physic manager as physic objects. 
	void add_physic_object(Entity*, CollisionGroup c=COLLISION_GROUP_ALL);


private:
	PhysicManager(void){};
	PhysicManager(PhysicManager& const);
	void operator= (PhysicManager& const);
	friend class Singleton<PhysicManager>;

	//Stores all the physic objects that physic manager makes calculation
	std::vector<PhysicObject*> physic_objects;
	//checks collision between two physic objects
	bool check_collision(PhysicObject*, PhysicObject*);
	//updates all physic objects with their new positions and states
	void update_physic_objects();
};

