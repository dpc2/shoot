/*
 * enemy.cpp
 *
 *  Created on: 2019年1月2日
 *      Author: x
 */

#include "enemy.h"
#include "rocket.h"
#include "h.h"

Enemy::Enemy(Terrain * terrain, char * modelFile, char *skinFile)
		: Object(terrain)
{
//	load_md2((char*)"models/sodf8/tris.md2", (char*)"models/sodf8/abarlith.pcx");
//	load_md2((char*)"models/ogro/tris.md2", (char*)"models/ogro/ogrobase.pcx");

	object_type_ = ENEMY;
	md2 = new ModelMD2;
	md2->Load(modelFile, skinFile);
	md2->interpol = 3.0f;
	md2->SetState(MODEL_RUN);

	frame_start = 0;
	frame_end = 39;
	hit_points_ = 100;        // start with 100 hit points

	speed() = 2;
	animate_speed_ = speed();
//	yaw() = -90;
	collision_radius() = 0.9;

	player_ = nullptr;
	status() = Object::object_status::DEFAULT;
	Object::object_list_.push_back(this);
}
Enemy::~Enemy()
{
}
void Enemy::SetPlayer(Object *player)
{
	player_ = player;
}
void Enemy::update_status()
{
	float direction_to_player;        // the yaw of the Entity-player vector

	Vector diff;        // the vector from the Entity to the player
	diff.x = core_coord().x - player_->core_coord().x;
	diff.z = core_coord().z - player_->core_coord().z;
	diff.Normalize();

	// find the yaw in the world of the vector from the Entity to the player
	// in relation the negative z-axis
	direction_to_player = RAD2DEG(diff.Yaw(Vector(0, 0, -1)));
	srand((unsigned int) time(nullptr));

//	static time_t t1 = 0;
//	t1 = time(0);

	if(md2->modelState != MODEL_DYING && md2->modelState != MODEL_DEAD)
	{
		// if the player is close enough, the Entity should become scared
		distance_from_player_ = (player_->core_coord() - core_coord()).Length();
		if(distance_from_player_ < 100.0)
		{
			ahead_yaw() = (direction_to_player /*- 90 */) + ((rand() % 30) - 25);        // set the direction of the Entity
			int a = rand() % 2;
			switch(a)
			{
				case 0:
					{
//
//					if (time(0) - t1 > 2)
//					{
//						md2->modelState = MODEL_FIRE;
//						horizontal_speed() = 10;
//
//						Rocket *rocket = new Rocket(terrain());        // camera->lookAt.UnitVector()
//						rocket->geometric_center() = this->eyes() + Vector(25, 3, 25);
//						rocket->move_yaw() = move_yaw();
//						t1 = time(0);
//					}
				}
					break;

				default:
					//					md2->modelState = MODEL_CROUCH;
					break;
			}
		}
		else
		{
			ahead_yaw() = (float(rand() % 360));
			int a = rand() % 3;
			switch(a)
			{
				case 0:
					md2->modelState = MODEL_IDLE;
					want_to_go_forward(false);
					break;
				case 1:
					md2->modelState = MODEL_JUMP;
					break;
				case 2:
					md2->modelState = MODEL_RUN;
					want_to_go_forward(true);
					break;
			}
		}
	}

// do prep for MD2 Model states
	/*
	 Frame#  Action
	 ----------------
	 0-39    idle
	 40-46   running
	 47-60   getting shot but not falling (back bending)
	 61-66   getting shot in shoulder
	 67-73   jumping
	 74-95   idle
	 96-112  getting shot and falling down
	 113-122 idle
	 123-135 idle
	 136-154 crouch
	 155-161 crouch crawl
	 162-169 crouch adjust weapon (idle)
	 170-177 kneeling dying
	 178-185 falling back dying
	 186-190 falling forward dying
	 191-198 falling back slow dying
	 */

	switch(md2->modelState)
	{
		case MODEL_IDLE:
			frame_start = 0;
			frame_end = 39;
			break;

		case MODEL_RUN:
			frame_start = 40;
			frame_end = 46;
			break;

		case MODEL_JUMP:
			frame_start = 67;
			frame_end = 73;
			break;

		case MODEL_CROUCH:
			frame_start = 155;
			frame_end = 161;
			break;

		case MODEL_FIRE:
			frame_start = 61;
			frame_end = 66;
			break;

		case MODEL_DYING:
			frame_start = 191;        // 178
			frame_end = 198;        // 184
			if(md2->nextFrame == frame_start)
			{
				md2->modelState = MODEL_DEAD;
				status() = Object::object_status::DEAD;
			}
			break;

		case MODEL_DEAD:
			frame_start = 0;
			frame_end = 1;
			break;

		default:
			frame_start = 0;
			frame_end = 1;
			break;
	}
}
void Enemy::v_draw(float second)
{
	update_status();

	glTranslatef(core_coord().x, core_coord().y, core_coord().z);
//	glRotatef(-get_yaw(), 0.0, 1.0, 0.0);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	float a = 1.0 / 20.0;
	glScalef(a, a, a);

//	LOG("stateStart %d, stateEnd %d, deltaT * animate_speed %f", stateStart, stateEnd, deltaT * animate_speed);
	animate_speed_ = speed();
	md2->render_frames(frame_start, frame_end, second * animate_speed_);
}
void Enemy::v_collision(Object *obj)
{
	if(md2->modelState == MODEL_DYING || md2->modelState == MODEL_DEAD)
	{
		return;
	}

	if(obj->object_type_ == ENEMY)
	{
		md2->modelState = MODEL_IDLE;
	}
	else
		if(obj->object_type_ == ROCKET)
		{
			md2->modelState = MODEL_DYING;
			horizontal_speed() = 0;
		}
}

