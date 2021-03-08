/*
 * object.cpp
 *  Created on: 2018年12月29日
 *      Author: x
 */

#include "object.h"

#include "h.h"

std::vector <Object*> Object::object_list_;

Object::Object(
		Terrain * terrain,
		Vector core_coord,
		float collision_radius,
		float yaw,
		float speed)
		: vertical_acceleration_(-10)
{
	terrain_ = terrain;
	core_coord_ = core_coord;
	collision_radius_ = collision_radius;

	if(core_coord_ == Vector(0, 0, 0))
	{
		float x = rand() % (int) terrain_->width();
		float z = -rand() % (int) terrain_->height();
		if(x < 0)
		{
			x = 0;
		}
		if(x > terrain_->width())
		{
			x = terrain_->width();
		}
		if(z < -terrain_->height())
		{
			z = -terrain_->height();
		}
		if(z > 0)
		{
			z = 0;
		}

		float y = terrain_->terrain_Y_coord(x, z) + collision_radius_;
		core_coord_ = Vector(x, y, z);
	}

	ahead_yaw_ = yaw;
//	up_ = Vector(0, 1, 0);

	speed_ = speed;
	horizontal_speed_ = speed_;
	horizontal_traveled_distance_ = 0;
	vertical_speed_ = 0;

	go_forward_ = false;
	go_back_ = false;
	go_left_ = false;
	go_right_ = false;
	jump_status_ = IS_NOT_JUMPING;
	turn_left_ = false;
	turn_right_ = false;

	want_to_go_forward_ = false;
	want_to_go_back_ = false;
	want_to_go_left_ = false;
	want_to_go_right_ = false;
	want_to_jump_ = false;
	want_to_turn_left_ = false;
	want_to_turn_right_ = false;

//	go_upper_ = false;
//	go_lower_ = false;
//	force_add_to_y_ = 0;
	status_ = DEFAULT;

//	Object::object_list_.push_back(this);		// TODO: this could cause error
}
Object::~Object()
{
}
void Object::update(float second)
{
	if(status_ == DEAD)
	{
		return;
	}
	if(vertical_speed_ < -1 * collision_radius_ * 2 * 100)
	{
		status_ = DEAD;
		return;
	}

	if(object_type_ == PLAYER)
	{
		if(is_on_ground() == true)
		{
			go_forward_ = want_to_go_forward_;
			go_back_ = want_to_go_back_;
			go_left_ = want_to_go_left_;
			go_right_ = want_to_go_right_;
//		jump_status_ = ALIVE_JUMP_OVER;
		}
	}
	else
		if(object_type_ == ROCKET)
		{
			go_forward_ = want_to_go_forward_;
		}
		else
			if(object_type_ == ENEMY)
			{
				go_forward_ = want_to_go_forward_;
			}

	turn_left_ = want_to_turn_left_;
	turn_right_ = want_to_turn_right_;
	if(turn_left_ == true)
	{
		ahead_yaw_ -= 5;
	}
	if(turn_right_ == true)
	{
		ahead_yaw_ += 5;
	}

	if(want_to_jump_ == true && jump_status_ == IS_NOT_JUMPING)        // jump caused by player
	{
		vertical_speed_ = 5;
		jump_status_ = IS_JUMPING;
	}

	update_X_Z_coord(second);
	update_Y_coord(second);

	float eyes_height_to_feet = 0;
	if(status_ == STAND || status_ == DEFAULT)
	{
		//
	}
	else
	{
		// TODO: ALIVE_SQUAT,
		eyes_height_to_feet = collision_radius_ * 0.9;
		LOG("status_: %d", status_);
		exit(1);
	}
//	LOG("position_: %.1f %.1f %.1f", position_.x, position_.y, position_.z);
}
void Object::update_X_Z_coord(float second)
{
	float s = 0;		// horizontal_delta_distance

	if(go_forward_ || go_back_ || go_left_ || go_right_)
	{
		s = horizontal_speed_ * second;
	}
	else
	{
		return;
	}

	horizontal_traveled_distance_ += s;

	float x = 0;
	float z = 0;
	float rad = PI * ahead_yaw_ / 180.0;

	if(go_forward_)
	{
		x += cos(rad) * s;
		z += sin(rad) * s;
	}
	if(go_back_)
	{
		x -= cos(rad) * s;
		z -= sin(rad) * s;
	}
	if(go_left_)
	{
		x += sin(rad) * s;
		z -= cos(rad) * s;
	}
	if(go_right_)
	{
		x -= sin(rad) * s;
		z += cos(rad) * s;
	}

	// if both go_forward_... and go_right_... are true
	if(sqrt(x * x + z * z) - s > SMALL_FLOAT_NUMBER)
	{
		x /= sqrt(2);
		z /= sqrt(2);
	}

	float next_feet_x = core_coord_.x + x;
	float next_feet_z = core_coord_.z + z;

//	if(terrain_->coord_is_in_map(core_coord_.x, core_coord_.z) == true
//			&& terrain_->coord_is_in_map(next_feet_x, next_feet_z) == true)

	float next_feet_y = terrain()->terrain_Y_coord(next_feet_x, next_feet_z);
	float this_feet_y = feet_coord().y;

	if(this_feet_y < next_feet_y)
	{
		if(next_feet_y - this_feet_y > collision_radius_ * 2 * 0.3)
		{
			LOG("this_feet_y < next_feet_y too much, can not move");
			return;
		}

		float pitch = (next_feet_y - this_feet_y) / (sqrt(x * x + z * z) + SMALL_FLOAT_NUMBER);
		if(pitch > 1)
		{
			LOG("pitch: %.1f / %.1f = %.1f", next_feet_y - this_feet_y, sqrt(x * x + z * z), pitch);
			return;
		}
	}

	core_coord_.x += x;
	core_coord_.z += z;
}
void Object::update_Y_coord(float second)
{
	if(jump_status_ == IS_NOT_JUMPING && false == is_on_ground())        // jump caused by map
	{
		jump_status_ = IS_JUMPING;
	}

	if(jump_status_ == IS_JUMPING)
	{
		// compute geometric_center_position_ with acceleration
		float pre_vertical_speed = vertical_speed_;
		vertical_speed_ += vertical_acceleration_ * second;
		float vertical_delta_distance = (pre_vertical_speed + vertical_speed_) / 2 * second;
		core_coord_.y += vertical_delta_distance;
	}

	if(is_on_ground() == true)
	{
		vertical_speed_ = 0;
		jump_status_ = IS_NOT_JUMPING;
	}
}
void Object::collision()
{
	Object *p;
	std::vector <Object*>::iterator obj;
	for(obj = object_list_.begin(); obj != object_list_.end(); obj++)
	{
		p = *obj;
		// delete obj from object_list_ ........................

		if(p == this)
		{
			continue;
		}

		if((p->core_coord_ - core_coord_).Length()
				< p->collision_radius_ + collision_radius_)
		{
			v_collision(p);
		}
	}
}
void Object::draw(float second)
{
	if(status_ == DEAD)
	{
//		delete this;
//		return;
	}

	update(second);
	collision();

	glPushMatrix();
	v_draw(second);
	glPopMatrix();
}
Terrain * Object::terrain()
{
	return terrain_;
}
Vector & Object::core_coord()
{
	return core_coord_;
}
Vector Object::feet_coord()
{
	if(status_ == STAND || status_ == DEFAULT)
	{
		return core_coord_ - Vector(0, collision_radius_, 0);
	}
	else
		if(status_ == DEAD)
		{

		}
		else
		{
			// todo: crawl
			LOG();
			exit(1);
		}
}
Vector Object::eyes_coord()
{
	if(status_ == STAND || status_ == DEFAULT)
	{
		return core_coord_ + Vector(0, collision_radius_ * 0.9, 0);
	}
	else
		if(status_ == DEAD)
		{
			return Vector(terrain_->width() / 2,
					terrain_->width() / 2 + terrain_->height() / 2 + 10,
					-terrain_->height() / 2);
		}
		else
		{        // todo: if(status_ == CRAWL)
			LOG();
			exit(1);
		}
}
Vector Object::look_at_coord()
{
	if(status_ == STAND || status_ == DEFAULT)
	{
		Vector eyes = eyes_coord();
		float rad = PI * ahead_yaw_ / 180.0;

		Vector look_at;
		look_at.x = eyes.x + cos(rad) * 100;
		look_at.z = eyes.z + sin(rad) * 100;
		look_at.y = eyes.y;

		return look_at;
	}
	else
		if(status_ == DEAD)
		{
			return Vector(terrain()->width() / 2, 0, -terrain()->height() / 2);
		}
		else
		{        // todo: if(status_ == CRAWL)
			LOG();
			exit(1);
		}
}
Vector Object::up()
{
	if(status_ == STAND || status_ == DEFAULT)
	{
		return Vector(0, 1, 0);
	}
	else
		if(status_ == DEAD)
		{
			return Vector(0, 0, -1);
		}
		else
		{        // todo: if(status_ == CRAWL)
			LOG();
			exit(1);
		}
}
float & Object::ahead_yaw()
{
	return ahead_yaw_;
}
float & Object::muzzle_yaw()
{
	return muzzle_yaw_;
}
float & Object::speed()
{
	return speed_;
}
float & Object::horizontal_speed()
{
	return horizontal_speed_;
}
float & Object::horizontal_traveled_distance()
{
	return horizontal_traveled_distance_;
}
float & Object::vertical_speed()
{
	return vertical_speed_;
}
const float & Object::vertical_acceleration()
{
	return vertical_acceleration_;
}
float & Object::collision_radius()
{
	return collision_radius_;
}
void Object::want_to_go_forward(bool b)
{
	want_to_go_forward_ = b;
}
void Object::want_to_go_back(bool b)
{
	want_to_go_back_ = b;
}
void Object::want_to_go_left(bool b)
{
	want_to_go_left_ = b;
}
void Object::want_to_go_right(bool b)
{
	want_to_go_right_ = b;
}
void Object::want_to_jump(bool b)
{
	want_to_jump_ = b;
}
void Object::want_to_turn_left(bool b)
{
	want_to_turn_left_ = b;
}
void Object::want_to_turn_right(bool b)
{
	want_to_turn_right_ = b;
}
bool Object::is_on_ground()
{
	Vector feet = feet_coord();

	float map_Y = terrain_->terrain_Y_coord(feet.x, feet.z);

	if(feet.y < map_Y + SMALL_FLOAT_NUMBER)
	{
		if(status_ == STAND || status_ == DEFAULT)
		{
			core_coord_.y = map_Y + collision_radius_;
		}
		else
			if(status_ == DEAD)
			{
//				LOG();
//				exit(1);
				return false;
			}
			else
			{        // todo: if(status_ == CRAWL)
				LOG();
				exit(1);
			}

		return true;
	}
	else        // is jumping
	{
//		LOG("Y: %f", terrain_->terrain_Y_coord(feet_coord_.x, feet_coord_.z));
		return false;
	}
}
Object::object_status & Object::status()
{
	return status_;
}
void Object::follow_to(Object * obj_to_follow, float distance_to_keep_while_follow)
{
}

