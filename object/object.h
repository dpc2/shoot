/*
 *
 */

#ifndef __OBJECT_H
#define __OBJECT_H

#include "terrain.h"
#include "vector.h"
#include "h.h"

class Object
{
public:
	enum object_type
	{
		ENEMY,
		PLAYER,
		ROCKET,
		UNDEFINED,
	};
	enum object_status
	{
		DEFAULT,
		STAND,
		SQUAT,
		CRAWL,

		IS_JUMPING,
		IS_NOT_JUMPING,

		DEAD,
	};
	object_type object_type_ = UNDEFINED;
	static std::vector <Object*> object_list_;

private:
	Terrain * terrain_;
	Vector core_coord_;
	float collision_radius_;				// size of bounding sphere (radius)
	float ahead_yaw_;
	float muzzle_yaw_ = 0;
//	float muzzle_pitch_;

	float speed_;
	float horizontal_speed_;
	float horizontal_traveled_distance_;			// distance rocket has travelled
	float vertical_speed_;
	const float vertical_acceleration_;        // acceleration 加速度

	void update(float second);
	void update_X_Z_coord(float second);
	void update_Y_coord(float second);

	bool want_to_go_forward_;
	bool want_to_go_back_;
	bool want_to_go_left_;
	bool want_to_go_right_;
	bool want_to_jump_;
	bool want_to_turn_left_;
	bool want_to_turn_right_;

	bool go_forward_;
	bool go_back_;
	bool go_left_;
	bool go_right_;
	object_status jump_status_;
	bool turn_left_;
	bool turn_right_;

	object_status status_;
	//	float visible_range_;

public:
	Object(Terrain * terrain,
			Vector core_coord = Vector(0, 0, 0),
			float collision_radius = 1,
			float yaw = -90,
			float speed = 2);
	virtual ~Object() = 0;

	void collision();        // 碰撞
	virtual void v_collision(Object *object) = 0;        // 碰撞
	virtual void v_draw(float second) = 0;
	void draw(float s_passed);

	Terrain *terrain();
	Vector & core_coord();
	Vector feet_coord();
	Vector eyes_coord();
	Vector look_at_coord();
	Vector up();
	float & ahead_yaw();
	float & muzzle_yaw();

	float & speed();
	float & horizontal_speed();
	float & horizontal_traveled_distance();
	float & vertical_speed();
	const float & vertical_acceleration();
	float & collision_radius();

	void want_to_go_forward(bool b);
	void want_to_go_back(bool b);
	void want_to_go_left(bool b);
	void want_to_go_right(bool b);
	void want_to_jump(bool b);
	void want_to_turn_left(bool b);
	void want_to_turn_right(bool b);

	bool is_on_ground();
	object_status & status();
	void follow_to(Object * obj_to_follow, float distance_to_keep_while_follow);
};

#endif
