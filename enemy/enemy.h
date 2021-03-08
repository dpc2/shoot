/*
 *
 */

#ifndef __ENEMY_H
#define __ENEMY_H

#include "object.h"
#include "audio.h"
#include "md2.h"

class Enemy: public Object
{
private:
	int hit_points_;           // hit points the Entity has left
	float animate_speed_;
	Object *player_;
	ModelMD2 *md2;
	int frame_start;
	int frame_end;        	// state keyframe start/end

	void process_AI();
	void update_status();
	float distance_from_player_ = 0;        // distance this Entity is from player

public:

	Enemy(Terrain * terrain, char * modelFile, char *skinFile);
	virtual ~Enemy();

	virtual void v_collision(Object *obj) final;
	virtual void v_draw(float second) final;

	void SetPlayer(Object *player);
	//	void PlaySound() { audioSys->Play(entitySound, 1); }
};

#endif
