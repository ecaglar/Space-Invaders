#pragma once
#include <map>
#include "IManager.h"
#include "Singleton.h"
#include "Sprite.h"

/************************************************************************/
/* Handles resource related stuff like loading assets, defining animation frames, 
loading fonts and creating templates etc. The better design is making resource management
with XML files dynamically however, due to limited time i have implemented in that way.

With resource manager, you never make resource loading and setting directly.
Instead of that YOU ASK TO RESOURCE MANAGER for needed resource. During initializing phase
of the game, resource loader reads all the graphics and fonts, defines their attributes 
and animation steps, and creates their template classes. So whenever we need a resource in game,
resource manager copies the related object and send its copy.
/************************************************************************/

class ResourceManager :
	public IManager, public Singleton<ResourceManager>
{
public:	

	void tick();
	void clean();
	
	//reads and loads sprites, defines animation frames and related attributes
	void loadSprites();

	//Creates the game object defined by name and returns it with its template(default) attributes
	Entity* get_copy_of(std::string name);


protected:
	ResourceManager(void){};
		ResourceManager(ResourceManager& const);
		void operator= (ResourceManager& const);
		friend class Singleton<ResourceManager>;

private:
	//maps the name of the entity with the entity object
	std::map<std::string, Entity*> name_entity_map;

	//followings are game object templetes used in games
	Entity* defender;
	Entity* evil1;
	Entity* evil2;
	Entity* evil3;
	Entity* evil4;
	Entity* explosion;
	Entity* background;
	Entity* shot;
	Entity* shot2;
	Entity* font;
	Entity* life_icon;

};

