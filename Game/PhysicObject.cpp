#include "PhysicObject.h"
#include "Entity.h"
#include "Sprite.h"


PhysicObject::~PhysicObject(void)
{
}

Vector2 PhysicObject::get_position() const
{
	return entity->GetPosition();
}

BoundingBox* PhysicObject::get_bounding_box()
{
	return bounding_box;
}

/*
creates a physic object with given entity and collision group.
during the initializing process, bounding box is calculates and saved
automatically.
*/
PhysicObject::PhysicObject( Entity* e, CollisionGroup cg /*= COLLISION_GROUP_ALL*/ )
{
	//support for only 2D sprite now
	if (e->GetRenderType() == RENDER2D)
	{
		entity = e;
		collision_group = cg;
		bounding_box = new BoundingBox();
		bounding_box->x = e->GetPosition().x;
		bounding_box->y = e->GetPosition().y;
		Sprite* s  = static_cast<Sprite*>(e);
		s->get_size(bounding_box->width, bounding_box->height,0);
	}
}

CollisionGroup PhysicObject::getCollisionGroup() const
{
	return collision_group;
}

void PhysicObject::set_bounding_box( int x, int y , int width, int height )
{
	if(bounding_box)
	{
		bounding_box->x = x;
		bounding_box->y = y;
		bounding_box->width = width;
		bounding_box->height = height;
	}
}

Entity* PhysicObject::get_entity() const
{
	return entity;
}
