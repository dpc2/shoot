/*
 *
 */

#ifndef __WORLD_H
#define __WORLD_H

#include "object.h"
#include "terrain.h"
#include "camera.h"
#include "player.h"
#include "audio.h"
#include "enemy.h"
#include "gui.h"
#include "h.h"

class World
{
private:
	float max_seconds_of_one_game_;		// s
	float timeElapsed_;		// s
	bool game_over_;

	void generate_enemy();
	int count_object_by_type(Object::object_type type);
	void FadeScreen();
	void Animate(float ms_passed);        // ms

public:
	Terrain * terrain_;
	Player * player_;			// the player
	Camera * camera_;			// the camera
	CGUI *gui_;
	//	CAudioSystem *audioSystem;	// the audio system
	//	CAudio *worldSound;			// the world ambient sound

	World();
	~World();

	void display();
};

#endif

