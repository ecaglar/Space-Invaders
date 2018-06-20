#include "ResourceManager.h"
#include "GameFont.h"

void ResourceManager::tick()
{
	//nothing to do every frame so maybe not extend IManager
}


void ResourceManager::loadSprites()
{
	std::vector<std::string> frames;
	frames.clear();

	defender	= new Sprite(DEFENDER);
	evil1		= new Sprite(DEVIL);
	evil2		= new Sprite(DEVIL);
	evil3		= new Sprite(DEVIL);
	evil4		= new Sprite(DEVIL);
	explosion	= new Sprite(EXPLOSION);
	background	= new Sprite(BACKGROUND);
	shot		= new Sprite(SHOT_FROM_DEFENDER);
	shot2		= new Sprite(SHOT_FROM_DEVIL);
	font		= new GameFont("../Data/font/arial.ttf", 20,1.0f,1.0f, 1.0f);
	life_icon	= new Sprite(LIFE_ICON);


	name_entity_map["font"] = font;

	//load and set defender related stuff
	frames.push_back("../Data/graphics/defender/defender_000.bmp");
	frames.push_back("../Data/graphics/defender/defender_001.bmp");
	frames.push_back("../Data/graphics/defender/defender_002.bmp");
	frames.push_back("../Data/graphics/defender/defender_003.bmp");
	frames.push_back("../Data/graphics/defender/defender_004.bmp");
	frames.push_back("../Data/graphics/defender/defender_005.bmp");
	frames.push_back("../Data/graphics/defender/defender_006.bmp");
	frames.push_back("../Data/graphics/defender/defender_007.bmp");
	frames.push_back("../Data/graphics/defender/defender_008.bmp");
	frames.push_back("../Data/graphics/defender/defender_009.bmp");
	frames.push_back("../Data/graphics/defender/defender_010.bmp");
	frames.push_back("../Data/graphics/defender/defender_011.bmp");
	frames.push_back("../Data/graphics/defender/defender_012.bmp");
	frames.push_back("../Data/graphics/defender/defender_013.bmp");
	frames.push_back("../Data/graphics/defender/defender_014.bmp");
	frames.push_back("../Data/graphics/defender/defender_015.bmp");
	frames.push_back("../Data/graphics/defender/defender_016.bmp");
	frames.push_back("../Data/graphics/defender/defender_017.bmp");
	frames.push_back("../Data/graphics/defender/defender_018.bmp");
	frames.push_back("../Data/graphics/defender/defender_019.bmp");
	frames.push_back("../Data/graphics/defender/defender_020.bmp");
	static_cast<Sprite*>(defender)->load_image_set(frames);	
	static_cast<Sprite*>(defender)->SetHealth(100);
	static_cast<Sprite*>(defender)->set_default_pose(10);
	static_cast<Sprite*>(defender)->set_animation("play_all", animation_frame(0,20,true));
	static_cast<Sprite*>(defender)->set_animation("turn_left", animation_frame(0,true));
	static_cast<Sprite*>(defender)->set_animation("turn_right", animation_frame(20,false));
	static_cast<Sprite*>(defender)->set_animation("return_to_default", animation_frame(10,false));
	name_entity_map["defender"] = defender;
	frames.clear();

	//load and set evil 1 related stuff
	frames.push_back("../Data/graphics/evil1/Evil1_031.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_032.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_033.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_034.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_035.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_036.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_037.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_038.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_039.bmp");
	frames.push_back("../Data/graphics/evil1/Evil1_040.bmp");
	static_cast<Sprite*>(evil1)->load_image_set(frames);
	static_cast<Sprite*>(evil1)->SetHealth(100);
	static_cast<Sprite*>(evil1)->set_default_pose(4);
	static_cast<Sprite*>(evil1)->SetHit_score(10);
	static_cast<Sprite*>(evil1)->set_animation("play_all", animation_frame(0,9,true));
	name_entity_map["evil1"] = evil1;
	frames.clear();

	//load and set evil 2 related stuff
	frames.push_back("../Data/graphics/evil2/Evil2_031.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_032.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_033.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_034.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_035.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_036.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_037.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_038.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_039.bmp");
	frames.push_back("../Data/graphics/evil2/Evil2_040.bmp");
	static_cast<Sprite*>(evil2)->load_image_set(frames);	
	static_cast<Sprite*>(evil2)->set_default_pose(4);
	static_cast<Sprite*>(evil2)->SetHealth(200);
	static_cast<Sprite*>(evil2)->SetHit_score(20);
	static_cast<Sprite*>(evil2)->set_animation("play_all", animation_frame(0,9,true));
	name_entity_map["evil2"] = evil2;
	frames.clear();

	//load and set evil3 related stuff
	frames.push_back("../Data/graphics/evil3/Evil3_031.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_032.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_033.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_034.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_035.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_036.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_037.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_038.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_039.bmp");
	frames.push_back("../Data/graphics/evil3/Evil3_040.bmp");
	static_cast<Sprite*>(evil3)->load_image_set(frames);	
	static_cast<Sprite*>(evil3)->set_default_pose(4);
	static_cast<Sprite*>(evil3)->SetHit_score(30);
	static_cast<Sprite*>(evil3)->SetHealth(300);
	static_cast<Sprite*>(evil3)->set_animation("play_all", animation_frame(0,9,true));
	name_entity_map["evil3"] = evil3;
	frames.clear();

	//load and set evil 4 related stuff
	frames.push_back("../Data/graphics/evil4/Evil4_031.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_032.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_033.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_034.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_035.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_036.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_037.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_038.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_039.bmp");
	frames.push_back("../Data/graphics/evil4/Evil4_040.bmp");
	static_cast<Sprite*>(evil4)->load_image_set(frames);	
	static_cast<Sprite*>(evil4)->set_default_pose(4);
	static_cast<Sprite*>(evil4)->SetHit_score(40);
	static_cast<Sprite*>(evil4)->SetHealth(400);
	static_cast<Sprite*>(evil4)->set_animation("play_all", animation_frame(0,9,true));
	name_entity_map["evil4"] = evil4;
	frames.clear();

	//load and set explosion related stuff
	frames.push_back("../Data/graphics/explosion/explosion_001.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_002.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_003.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_004.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_005.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_006.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_007.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_008.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_009.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_010.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_011.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_012.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_013.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_014.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_015.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_016.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_017.bmp");
	frames.push_back("../Data/graphics/explosion/explosion_018.bmp");

	static_cast<Sprite*>(explosion)->load_image_set(frames);	
	static_cast<Sprite*>(explosion)->set_default_pose(0);
	static_cast<Sprite*>(explosion)->set_animation("play_all", animation_frame(0,17,false));
	name_entity_map["explosion"] = explosion;
	frames.clear();

	////load and set background related stuff
	static_cast<Sprite*>(background)->load_image("../Data/graphics/backdrop.bmp");
	name_entity_map["background"] = background;
	static_cast<Sprite*>(background)->set_is_animation_mode(false);
	frames.clear();

	////load and set shot related stuff
	static_cast<Sprite*>(shot)->load_image("../Data/graphics/shot.bmp");
	name_entity_map["shot"] = shot;
	static_cast<Sprite*>(shot)->set_is_animation_mode(false);
	frames.clear();

	////load and set shot2 related stuff
	static_cast<Sprite*>(shot2)->load_image("../Data/graphics/shot2.bmp");
	name_entity_map["shot2"] = shot2;
	static_cast<Sprite*>(shot2)->set_is_animation_mode(false);
	frames.clear();

	//life icon
	static_cast<Sprite*>(life_icon)->load_image("../Data/graphics/icon.bmp");
	name_entity_map["life_icon"] = life_icon;
	static_cast<Sprite*>(life_icon)->set_is_animation_mode(false);
	frames.clear();
}


//makes deep copy
Entity* ResourceManager::get_copy_of( std::string name )
{
	Entity* copy_sprite = 0;

	std::map<std::string, Entity*>::iterator i;
	i = name_entity_map.find(name);

	if(i != name_entity_map.end()){
		ENTITY_TYPE type = (i)->second->GetEntityType();

		if(type == DEVIL || type == SHOT_FROM_DEFENDER || type == SHOT_FROM_DEVIL || type ==DEFENDER || type ==BACKGROUND || type==EXPLOSION || type == LIFE_ICON){
			Sprite* s = static_cast<Sprite*>(i->second);
			copy_sprite = new Sprite(s->GetEntityType());

			static_cast<Sprite*>(copy_sprite)->m_image_list.resize(s->m_image_list.size());
			std::copy(s->m_image_list.begin(), s->m_image_list.end(), static_cast<Sprite*>(copy_sprite)->m_image_list.begin());
			static_cast<Sprite*>(copy_sprite)->animations.insert(s->animations.begin(), s->animations.end());

			static_cast<Sprite*>(copy_sprite)->m_width = s->m_width;
			static_cast<Sprite*>(copy_sprite)->m_height = s->m_height;
			static_cast<Sprite*>(copy_sprite)->m_frame_number = s->m_frame_number;
			static_cast<Sprite*>(copy_sprite)->m_current_frame = s->m_current_frame;
			static_cast<Sprite*>(copy_sprite)->m_end_frame = s->m_end_frame;
			static_cast<Sprite*>(copy_sprite)->m_is_animation_mode = false;
			static_cast<Sprite*>(copy_sprite)->default_pose = s->default_pose;
			static_cast<Sprite*>(copy_sprite)->health = s->health;
			static_cast<Sprite*>(copy_sprite)->hit_score = s->hit_score;
		}else if(type == FONT)
		{
			GameFont* gf =  static_cast<GameFont*>(i->second);
			copy_sprite = new GameFont(gf->GetFont_name(),gf->GetSize(),gf->GetRed(), gf->GetGreen(), gf->GetBlue());
		}
	}	

	return copy_sprite;
}

void ResourceManager::clean()
{
	name_entity_map.clear();
	
}
