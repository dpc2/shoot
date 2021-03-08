/*
 *
 */

#ifndef __PLAYER_H
#define __PLAYER_H

#include "object.h"
#include "terrain.h"
#include "audio.h"
#include "h.h"

class Player: public Object
{
private:
//	CAudioSystem *audioSys;
//	CAudio *rocketSound;
//	void SetAudioSystem(CAudioSystem *aSys) { audioSys = aSys; }
	void emit_rocket();

public:
	Player(Terrain * terrain);
	virtual ~Player();

	void update_input(float second);
	virtual void v_collision(Object *object) final;
	virtual void v_draw(float second) final;

//	bool player_go_forward_;
//	bool player_go_back_;
//	bool player_go_left_;
//	bool player_go_right_;
//	bool player_jump_;
//	bool player_turn_left_;
//	bool player_turn_right_;

//	bool player_go_upper_;
//	bool player_go_lower_;
//	int mouse_move_x_;

	int rocket_to_emit_;
	int emited_rocket_;
};

#endif
