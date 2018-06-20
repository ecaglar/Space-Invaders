#pragma once
#include <map>
#include <string>
#include <vector>

#include "Image.h"
#include "Entity.h"

/*

	2D game entity that can be drawn on screen as sprite
	It encapsulates sprite related data such as width, height, animations etc..	

*/

/*
Animation frame is used to define animation steps for sprite.
from and to shows the frame numbers for animation
and continueus defines if animation will be continueus
or to be played just once
if "from" is set to -1 then it means that use the current frame to start animation.
*/
struct animation_frame
{
	int from;
	int to;
	bool continueus;

	animation_frame(){from = 0; to = 0; continueus = false; }
	animation_frame(int t, bool c){from = -1;to = t; continueus = c;}
	animation_frame(int f, int t, bool c){from = f; to = t;continueus = c; }
	
};


class Sprite : public Entity
{
	
public:
	Sprite(ENTITY_TYPE en);
	~Sprite(void);

	 void move()	;
	 void draw()	;
	 void animate(std::string) ;
	
	 //sets gets
	void set_animation(std::string name, animation_frame interval);
	void load_image(std::string name);
	void load_image_set(std::vector<std::string> names);
	void get_size(unsigned int& width, unsigned int& height, int index) const;
	void draw_image(int index, int x, int y, int alpha = 1.0f);
	void set_default_pose(int pose);
	int get_default_pose() const;
	void set_is_animation_mode(bool b);
	int GetCurrent_frame() const { return m_current_frame; }
	void SetCurrent_frame(int val) { m_current_frame = val; }
	bool GetIs_animation_mode() const { return m_is_animation_mode; }
	void SetIs_animation_mode(bool val) { m_is_animation_mode = val; }
	int GetHit_score() const { return hit_score; }
	void SetHit_score(int val) { hit_score = val; }
	Uint32 m_anim_start_time;
	
private:
	unsigned int m_width;
	unsigned int m_height;
	int m_frame_number;
	int m_current_frame;

	int m_end_frame;
	int m_start_frame;
	bool m_is_animation_mode;

	int default_pose;	//which frame will be rendered if not in aniamtion mode
	std::vector<Image*> m_image_list;	//image list for sprite
	int hit_score;	//sprites hit score to be gained if this sprite can be destroyed

	 void play_animation(std::string animation_name);	

	 //maps the aniamtion names and its keyframes which allow us to call animations by their names
	std::map<std::string , animation_frame> animations;
	friend class ResourceManager;
	

};

