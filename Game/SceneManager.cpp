
#include <sstream>
#include "SceneManager.h"
#include "Entity.h"
#include "Input.h"
#include "Sprite.h"
#include <iostream>
#include "ResourceManager.h"
#include "PhysicManager.h"
#include "SoundManager.h"


void SceneManager::tick()
{
	//remove dead entities
	clean_up();

	Uint32 new_ticks = SDL_GetTicks();
	
	//spawns shot from a random selected enemy in random time less then devil_shot_swapn_time seconds (in 3 seconds for now)
	if(new_ticks - old_ticks > devil_shot_swapn_time){ // in every (devil_shot_swapn_time) seconds
		//select a random devil
		int total_evil = get_num_of_enemy();
	
		int random_evil = rand() % total_evil; // selects a random enemy from whom we gonna spawn shot
		std::vector<Entity*>::iterator devil_it2;
		int selector = 0;

		//iterate all the enemy ships to get selected evil to spawn shot
		for(devil_it2 = m_entities.begin() ; m_entities.end() != devil_it2 ; devil_it2++ ){
			if((*devil_it2)->GetEntityType() == DEVIL)
			{
				if(selector == random_evil){
					Vector2 shot_pos = (*devil_it2)->GetPosition();
					(*devil_it2)->animate("play_all");
					shot_pos.y +=69;
					shot_pos.x +=24;
					spawn_entity(SHOT_FROM_DEVIL,shot_pos); //spawn a shot from evil
					SoundManager::Instance()->play_sound("vader_shot"); //play shot sound
					break;
				}
				++selector;
			}
		}
		
		old_ticks = new_ticks;
		devil_shot_swapn_time = rand() % 3000;
	}

	//run scene manager related function//

	//check if shots are out of the screen. if so destroy them.
	std::vector<Entity*>::iterator si;
	for(si = m_entities.begin() ; m_entities.end() != si ; si++ ){ 
		if((*si)->GetEntityType() == SHOT_FROM_DEFENDER)
		{
			if((*si)->GetPosition().y < 0){
				(*si)->SetState(DEAD);
			}else{
				Vector2 v = (*si)->GetPosition();
				v.y -=5;
				(*si)->SetPosition(v);
			}
		}else if((*si)->GetEntityType() == SHOT_FROM_DEVIL)
		{
			if((*si)->GetPosition().y >  480){
				(*si)->SetState(DEAD);
			}else{
				Vector2 v = (*si)->GetPosition();
				v.y +=5;
				(*si)->SetPosition(v);
			}
		}
		//moves enemy ships either right or left
		else if((*si)->GetEntityType() == DEVIL)
		{
			//TO DO: make that move CPU clock intependent
			Vector2 pos = (*si)->GetPosition();
			
			if(evil_move_dir){
				pos.x +=1;
			}else{
				pos.x -=1;
			}

			if((pos.x > (*si)->GetSpawnPos().x + 100) || ((pos.x < (*si)->GetSpawnPos().x))){
				evil_move_dir = !evil_move_dir;
			}

			(*si)->SetPosition(pos);
		}
	}
	//ticks all the managers registered to scene managers
	std::vector<IManager*>::iterator itr;
	for(itr = m_managers.begin() ; itr != m_managers.end() ; itr++)
	{
		(*itr)->tick();
	}

	//update defender position with mouse
	if(Input::mouseMotionX() != 0){
		if(get_defender()){
			Vector2 pos = get_defender()->GetPosition();

			pos.x =Input::mousePositionX();
			if(pos.x > 580) pos.x = 580;
			if(pos.x<0) pos.x=0;
			get_defender()->SetPosition(pos);
	}

	}

	//run turn right or left animation for defender depending on mouse movement
	if(Input::mouseMotionX() >0)
	{ if(get_defender())
		(get_defender())->animate("turn_right");

	}else if(Input::mouseMotionX() <0)
	{		
	 if(get_defender())
		(get_defender())->animate("turn_left");
	}else if(Input::mouseMotionX() == 0)
	{
		 if(get_defender()){
			 //if user does not move the mouse, dont animate defender
				if((static_cast<Sprite*>(get_defender()))->GetIs_animation_mode() == true){
					(static_cast<Sprite*>(get_defender()))->set_is_animation_mode(false);
				}
		 }

	}
	//we are firing
	if(Input::mouseDown())
	{
		//instantiate a shot from defender
		Vector2 pos = get_defender()->GetPosition();
		pos.x += 24;
		pos.y -=5; 
		spawn_entity(SHOT_FROM_DEFENDER,pos );
		SoundManager::Instance()->play_sound("player_shot");
	}
	
}

void SceneManager::add_manager( IManager* manager)
{
	m_managers.push_back(manager);
}


//callback function called from physic manager to inform scene manager that collision is occurred
void SceneManager::on_collision( Entity* collider1, Entity* collider2 )
{

	std::map<Entity*, Entity*>::iterator i1 = collision_tester.find(collider1);
	std::map<Entity*, Entity*>::iterator i2 = collision_tester.find(collider2);

	if(i1 == collision_tester.end() ||i2 == collision_tester.end()){
	
		//defender shot a evil
		if(collider2->GetEntityType() == SHOT_FROM_DEFENDER && collider1->GetEntityType() == DEVIL ){
			collider2->SetState(DEAD);	//set shot state to DEAD to destroy it next frame
			int h = collider1->GetHealth();
			h -= 50;	//increase the evil health by 50 (better to put them in XML!!)
			if (h<0){	//if enemy has no health
				collider1->SetState(DEAD); //set enemy state to dead
				std::stringstream ss; 
				total_score += static_cast<Sprite*>(collider1)->GetHit_score(); //since you destroyed a enemy, calculate your new score
				ss<<total_score;
				score_board->SetRender_text("Score: "+ss.str());	//update score board with your new score
				spawn_entity(EXPLOSION, collider1->GetPosition());	//spawn a explosion animation
				SoundManager::Instance()->play_sound("explosion"); //play sound
			}
			else{collider1->SetHealth(h);}	//if you cant destroy enemy, update its health only
		}
		
		//defender got a shot from enemu ship
		if(collider2->GetEntityType() == SHOT_FROM_DEVIL && collider1->GetEntityType() == DEFENDER ){
			collider2->SetState(DEAD);
			int h = collider1->GetHealth();
			h -= 50;
			if (h<0){
				Vector2 pre_pos = collider1->GetPosition();
				collider1->SetState(DEAD);

				//spawn multiple explosion for defender to make it much more notifiable
				spawn_entity(EXPLOSION, collider1->GetPosition());
				SoundManager::Instance()->play_sound("explosion");
				spawn_entity(EXPLOSION, Vector2(collider1->GetPosition().x-30, collider1->GetPosition().y-10));
				SoundManager::Instance()->play_sound("explosion");
				spawn_entity(EXPLOSION, Vector2(collider1->GetPosition().x+30, collider1->GetPosition().y-10));
				SoundManager::Instance()->play_sound("explosion");
				spawn_entity(EXPLOSION, Vector2(collider1->GetPosition().x, collider1->GetPosition().y-30));
				SoundManager::Instance()->play_sound("explosion");
				spawn_entity(EXPLOSION, Vector2(collider1->GetPosition().x-50, collider1->GetPosition().y-5));
				SoundManager::Instance()->play_sound("explosion");
				spawn_entity(EXPLOSION, Vector2(collider1->GetPosition().x+50, collider1->GetPosition().y-5));
				SoundManager::Instance()->play_sound("explosion");
				spawn_entity(EXPLOSION, Vector2(collider1->GetPosition().x, collider1->GetPosition().y-50));
				SoundManager::Instance()->play_sound("explosion");
				

				//if enemy destroy out ship, so render one less life icon
				bool is_set =false;
				std::vector<Entity*>::iterator icon_it;
				for(icon_it = m_entities.begin() ; m_entities.end() != icon_it ; icon_it++ ){
					if((*icon_it)->GetEntityType() == LIFE_ICON)
					{
						(*icon_it)->SetState(DEAD);
						
						break;
					}
				}

				exit = true;
				
				for(icon_it = m_entities.begin() ; m_entities.end() != icon_it ; icon_it++ ){
					if((*icon_it)->GetEntityType() == LIFE_ICON && (*icon_it)->GetState() != DEAD)
					{
						//we still have life so that spawn a new defender
						exit = false;
						spawn_entity(DEFENDER,pre_pos);
						break;
					}
				}
				

			}
			else{collider1->SetHealth(h);}
		}
		collision_tester[collider1] = collider2;
		collision_tester[collider2] = collider1;
	}
}
/*
Adds entity to the scene manager. Depending entity type, 
we add them different collision groups in order to reduce
extra collision checks.
*/
void SceneManager::add_entity( Entity* e)
{
	m_entities.push_back(e);
	//defender related objects are set to COLLISION_GROUP_A
	if(e->GetEntityType() == DEFENDER || e->GetEntityType() == SHOT_FROM_DEFENDER)
	{
		PhysicManager::Instance()->add_physic_object(e,COLLISION_GROUP_A);
	}
	//enemy related objects are set to COLLISION_GROUP_B
	else if(e->GetEntityType() == DEVIL || e->GetEntityType() == SHOT_FROM_DEVIL)
	{
		PhysicManager::Instance()->add_physic_object(e,COLLISION_GROUP_B);
	}else if (e->GetEntityType() == EXPLOSION)
	{
		(e)->animate("play_all");
	}
}

//render function for scene manager.It iterates over all game entities and calls their draw functions
void SceneManager::draw()
{
	std::vector<Entity*>::iterator it;
	for(it = m_entities.begin() ; it != m_entities.end() ; it++){
		(*it)->draw();
	}
}

//returns defender
Entity* SceneManager::get_defender()
{
	std::vector<Entity*>::iterator it;
	for(it = m_entities.begin() ; it != m_entities.end() ; it++){
		if((*it)->GetEntityType() == DEFENDER)
		{
			return (*it);
		}
	}
}


void SceneManager::spawn_entity( ENTITY_TYPE type, Vector2 location )
{

	Entity* swapn_e = 0;

	switch (type){
	case SHOT_FROM_DEFENDER:

		swapn_e = ResourceManager::Instance()->get_copy_of("shot");
		swapn_e->SetPosition(location);
		add_entity(swapn_e);
		break;

	case SHOT_FROM_DEVIL:
		swapn_e = ResourceManager::Instance()->get_copy_of("shot2");
		swapn_e->SetPosition(location);
		add_entity(swapn_e);
		break;
		

	case EXPLOSION:
		swapn_e = ResourceManager::Instance()->get_copy_of("explosion");
		swapn_e->SetPosition(location);		
		add_entity(swapn_e);
		break;

	case DEFENDER:
		swapn_e = ResourceManager::Instance()->get_copy_of("defender");
		swapn_e->SetPosition(location);		
		add_entity(swapn_e);
		break;
	default:
		break;
	}
}

void SceneManager::remove_entity( Entity* e)
{
	std::vector<Entity*>::iterator i = m_entities.begin();
	for( ; i != m_entities.end() ; i++)
	{
		if((*i) == e)
		{
			m_entities.erase(i);
			return ;
		}
	}
}

void SceneManager::clean_up()
{
	std::vector<Entity*>::iterator i;
	for(i = m_entities.begin() ; i != m_entities.end() ;)
	{
		if((*i)->GetState() == DEAD)
		{
			i = m_entities.erase(i);
		}else{
			i++;
		}
	}
}

void SceneManager::setScoreBoard( GameFont* gf)
{
	score_board = gf;
}

int SceneManager::get_num_of_enemy()
{
	int sum = 0;
	std::vector<Entity*>::iterator ite;
	for(ite = m_entities.begin() ; ite != m_entities.end() ; ite++)
	{
		if((*ite)->GetEntityType() == DEVIL)
		{
			sum++;
		}
	}

	return sum;
}

void SceneManager::clean()
{
	m_entities.clear();
	m_managers.clear();
	collision_tester.clear();
}


