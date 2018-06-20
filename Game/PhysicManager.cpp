#include "PhysicManager.h"
#include "SceneManager.h"
#include "Entity.h"
#include "PhysicObject.h"

void PhysicManager::tick()
{
	//first update all physic objects so that we can make calculation on them
	update_physic_objects();

	/*
	Makes collision detection between physic objects in scene. Using collision groups, 
	It can make faster collision detection as it checks collision between just different groups

	*/
	if(!physic_objects.empty())
	{
		for(int i = 0 ; i < physic_objects.size() ; i++)
		{
			for(int j = 0 ; j < physic_objects.size() ; j++)
			{
				if((physic_objects[i]->getCollisionGroup() != COLLISION_GROUP_NONE) && (physic_objects[j]->getCollisionGroup() != COLLISION_GROUP_NONE) )
				{			

					if((physic_objects[i] != physic_objects[j]) && 
					  ((physic_objects[i]->getCollisionGroup() != physic_objects[j]->getCollisionGroup()) || 
					  ((physic_objects[i]->getCollisionGroup() == (physic_objects[j]->getCollisionGroup() == COLLISION_GROUP_ALL )))))
					{
						if (check_collision(physic_objects[i], physic_objects[j]))
						{
							SceneManager::Instance()->on_collision(physic_objects[i]->entity,physic_objects[j]->entity);

						}
					}
				}
			}
		}
	}
}


void PhysicManager::add_physic_object( Entity* e, CollisionGroup c )
{
	physic_objects.push_back(new PhysicObject(e,c));
}

//performs bounding box collision detection
bool PhysicManager::check_collision( PhysicObject* p1, PhysicObject* p2)
{
	if((p1->get_bounding_box()->y + p1->get_bounding_box()->height) < (p2->get_bounding_box()->y)) return false;
	if((p1->get_bounding_box()->y) > (p2->get_bounding_box()->y + p2->get_bounding_box()->height)) return false;
	if((p1->get_bounding_box()->x + p1->get_bounding_box()->width) < (p2->get_bounding_box()->x)) return false;
	if((p1->get_bounding_box()->x) > (p2->get_bounding_box()->x + p2->get_bounding_box()->width)) return false;
	return true;
}

void PhysicManager::update_physic_objects()
{
	//iterates over all physic objects
	std::vector<PhysicObject*>::iterator physic_it;
	for(physic_it = physic_objects.begin() ; physic_it != physic_objects.end() ; ){
		if((*physic_it)->get_entity()->GetState() == DEAD){ //if game entity is in DEAD state remove it from phsyic object list
			physic_it = physic_objects.erase(physic_it);
		}else{
			physic_it++;
		}
	}
	for(physic_it = physic_objects.begin() ; physic_it != physic_objects.end() ; physic_it++)
	{
		//Update bounding boxes using new positions
		(*physic_it)->set_bounding_box((*physic_it)->get_entity()->GetPosition().x,(*physic_it)->get_entity()->GetPosition().y,(*physic_it)->get_bounding_box()->width, (*physic_it)->get_bounding_box()->height );
	}
}

void PhysicManager::clean()
{
	physic_objects.clear();
	
}
