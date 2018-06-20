#include "Sprite.h"
#include <iostream>

Sprite::Sprite(ENTITY_TYPE e) : Entity(RENDER2D,e)
{
	m_width = 0;
	m_height = 0;
	m_frame_number = 0;
	m_current_frame = 0; 
	hit_score = 0;
	m_is_animation_mode = false;
}

Sprite::~Sprite(void)
{
}


void Sprite::move()
{

}

void Sprite::draw()
{
	if(!m_is_animation_mode || m_start_frame == m_end_frame) //if we are not animationg the sprite
	{
		m_image_list[m_current_frame]->render(m_position.x, m_position.y);

	}else{
		
		//in animation mode
		Uint32 t = SDL_GetTicks();
		if(t - m_anim_start_time > 5){

			if(m_start_frame > m_end_frame)
			{
				
				m_image_list[m_current_frame]->render(m_position.x, m_position.y);
				m_current_frame--;
				m_anim_start_time = t;
				if(m_current_frame < m_end_frame)
				{
					m_current_frame = m_end_frame;
					m_is_animation_mode = false;
					return;
				}


			}else if(m_start_frame < m_end_frame)
			{
				
				m_image_list[m_current_frame]->render(m_position.x, m_position.y);
				m_current_frame++;
				m_anim_start_time = t;
				if(m_current_frame > m_end_frame)
				{
					if(this->GetEntityType() == EXPLOSION)
					{
						//if animation is explosion we wont need it after animating once
						this->SetState(DEAD);
					}
					m_current_frame = m_end_frame;
					m_is_animation_mode = false;
					return;
				}
			}
				
		}

	}
}

void Sprite::play_animation( std::string animation_name )
{
	std::map<std::string, animation_frame>::iterator it = animations.find(animation_name);

	
	if(it != animations.end() && !m_is_animation_mode){

		if(it->second.from != -1)
		{
			m_start_frame = it->second.from;
			m_current_frame = m_start_frame;
		}else{
			m_start_frame = m_current_frame;
		}
		
		m_end_frame = it->second.to;
		m_is_animation_mode = true;
		m_anim_start_time = SDL_GetTicks();
	}
 }


void  Sprite::get_size( unsigned int& width, unsigned int& height, int index ) const
{

	m_image_list[index]->getSize(width, height);
}

void Sprite::draw_image( int index, int x, int y, int alpha /*= 1.0f*/ )
{
	m_image_list[index]->render(x,y,alpha);
}

void Sprite::load_image( std::string name )
{
	Image* i = new Image();
	i->loadBmp(name);
	m_image_list.push_back(i);
	m_frame_number = 1;
	m_current_frame = 0;
	i->getSize(m_width, m_height);

}

//loads a set of image instead of one image
void Sprite::load_image_set( std::vector<std::string> names )
{
	m_frame_number = names.size();

	Image* image  = 0;
	for(int i = 0 ; i < names.size() ; i++)
	{
		image = new Image();
		image->loadBmp(names[i]);
		m_image_list.push_back(image);
	}
	image->getSize(m_width, m_height); //consider all of them has same size


}

void Sprite::animate(std::string anim)
{
	play_animation(anim);
}

void Sprite::set_animation( std::string name, animation_frame interval )
{
	animations[name] = interval;
}

void Sprite::set_default_pose( int pose )
{
	default_pose = pose;
}

int Sprite::get_default_pose() const
{
	return default_pose;
}

void Sprite::set_is_animation_mode( bool b )
{
	m_is_animation_mode = b;
}

