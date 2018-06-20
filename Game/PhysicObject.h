#pragma once
#include "Vector2.h"

/*
Physic Object is what the collidable game object is from the point of view of PhysicManager
Physic objects stores game entities internally and wrap them with physic related
data such as bounding box and collision group.

Each physic object corresponds a collision group.So that
the collision between physic objects correspoding the same
collision group is ignored.Doing this, we prevent making additional
unnecessary collision checks.

*/


class Entity;
class BoundingBox;


typedef unsigned char CollisionGroup;

#define		COLLISION_GROUP_NONE	(CollisionGroup)0
#define		COLLISION_GROUP_A		(CollisionGroup)(1)
#define		COLLISION_GROUP_B		(CollisionGroup)(1 << 1)
#define		COLLISION_GROUP_C		(CollisionGroup)(1 << 2)
#define		COLLISION_GROUP_D		(CollisionGroup)(1 << 3)
#define		COLLISION_GROUP_E		(CollisionGroup)(1 << 5)
#define		COLLISION_GROUP_G		(CollisionGroup)(1 << 6)
#define		COLLISION_GROUP_H		(CollisionGroup)(1 << 7)
#define		COLLISION_GROUP_ALL		(CollisionGroup)(255)

class PhysicObject
{
	public:
		PhysicObject(Entity*, CollisionGroup cg = COLLISION_GROUP_ALL);
		~PhysicObject(void);

		Vector2			get_position() const;	
		BoundingBox*	get_bounding_box();
		CollisionGroup	getCollisionGroup() const;
		void			set_bounding_box(int x, int y , int width, int height);
		Entity*			get_entity() const;	//returns the internal game entity

private:
	Entity*				entity;			//internal game entity
	BoundingBox*		bounding_box;	//bounding box for physic objects
	CollisionGroup		collision_group;//collision group of physic object
	friend class PhysicManager;

};

