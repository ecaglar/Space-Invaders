#pragma once
#include "Vector2.h"
#include "BoundingBox.h"
#include <string>
/*
	Entity is the base class for all renderable game objects.
	So rendrable game objects such as game texts and sprites extends 
	entity. Scene manager operates over entity objects so that 
	we provide the flexibility of polymorphisms and code to interface rule
	of OOP It also provides easy integration of any future  objects
	to the game logic. Only thing to do is to extend entity class
	and implements pure virtual functions according to needs of new entity.
	Then scene manager will handle the rest.
*/

enum RENDER_TYPE
{
	RENDER2D,		//we will be using just for 2D now
	RENDER3D		//in order to support 3D rendering support in future
};

enum ENTITY_STATE
{
	ACTIVE,		//active on scene
	DEAD		//dead object
};

enum ENTITY_TYPE
{
	NONE,
	DEFENDER,
	BACKGROUND,
	DEVIL,
	SHOT_FROM_DEFENDER,
	SHOT_FROM_DEVIL,
	EXPLOSION,
	FONT,
	LIFE_ICON
};

class Entity
{
public:
	Entity(RENDER_TYPE type, ENTITY_TYPE e_type);
	~Entity(void);

	int				GetId() const			{ return m_id; }
	void			SetId(int val)			{ m_id = val; }
	bool			GetVisible() const		{ return m_visible; }
	void			SetVisible(bool val)	{ m_visible = val; }
	int				GetLifetime() const		{ return m_lifetime; }
	void			SetLifetime(int val)	{ m_lifetime = val; }
	RENDER_TYPE		GetRenderType() const	{ return m_render_type; }
	ENTITY_STATE	GetState() const		{ return m_state; }
	void			SetState(ENTITY_STATE val) { m_state = val; }
	Vector2			GetPosition() const { return m_position; }
	void			SetPosition(Vector2 val) { m_position = val; }

	ENTITY_TYPE		GetEntityType(){return m_entity_type;}
	int				GetHealth() const { return health; }
	void			SetHealth(int val) { health = val; }
	Vector2			GetSpawnPos() const { return m_spawnPos; }
	void			SetSpawnPos(Vector2 val) { m_spawnPos = val; }

	//any extender class has to implement them as they are called by scene manager
	virtual void move()		= 0;
	virtual void animate(std::string anim)	= 0;
	virtual void draw()		= 0; 


protected:
	int			m_id;			//unique id of the entity (for future support)
	bool		m_visible;		//if entity is visible or not (for future support)
	int			m_lifetime;		//lifetime of the object for self destruction (for future support)
	RENDER_TYPE m_render_type;	//render type of objects (Render2D for now but has support for render3D)
	ENTITY_STATE m_state;		//state of the entity dead or alive
	Vector2		m_position;		//position of the entity
	Vector2		m_spawnPos;		//first spawn position on screen

	ENTITY_TYPE m_entity_type;	//type of the entity
	int health;					//health of the entity







};

