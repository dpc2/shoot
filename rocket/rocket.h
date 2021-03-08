/*
 *
 */

#ifndef __ROCKET_H
#define __ROCKET_H

#include "../object/object.h"
#include "enemy.h"
#include "bomb.h"
#include "texture.h"
#include "md2.h"

class Rocket: public Object
{
private:
	ModelMD2 *md2_;

	Bomb *bomb_;
	Texture *bomb_texture_;
//	void load_bomb_texture();
	bool is_bombing_;

public:
	Rocket(Terrain *terrain);
	~Rocket();

	virtual void v_collision(Object *collisionObject) final;
	virtual void v_draw(float second) final;
};

#endif
