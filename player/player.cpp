/*
 *
 */

#include "player.h"
#include "rocket.h"

Player::Player(Terrain * terrain)
		: Object(terrain)
{
	object_type_ = PLAYER;

//	geometric_center() = Vector(0, 0, 0);
	speed() = 2;
	horizontal_speed() = 2;
	collision_radius() = 0.9;        // person height is 1.8m

	rocket_to_emit_ = 0;
	emited_rocket_ = 0;

//	player_go_forward_ = false;
//	player_go_back_ = false;
//	player_go_left_ = false;
//	player_go_right_ = false;
//	player_jump_ = false;
//	player_turn_left_ = false;
//	player_turn_right_ = false;
//	player_go_upper_ = false;
//	player_go_lower_ = false;

	Object::object_list_.push_back(this);
// audioSys = nullptr; rocketSound = nullptr;
}
Player::~Player()
{
}
void Player::emit_rocket()
{
	if(status() == Object::DEAD)
	{
		return;
	}

// use camera->lookAt vector and multiply
// this lookAt vector by the ammo's speed
// to get the ammo velocity vector.
// create the new ammo and attach it to
// the world. fire the ammo

	Rocket *rocket = new Rocket(terrain());        // camera->lookAt.UnitVector()
	rocket->core_coord() = this->eyes_coord() - Vector(0, this->collision_radius() * 2 * 0.1, 0);
	rocket->ahead_yaw() = this->muzzle_yaw();

//	Object::object_list_.push_back(rocket);

	LOG("emit_rocket");
//	double vector_x = cos(DEG2RAD(get_direction()));
//	double vector_y = sin(DEG2RAD(get_pitch()));
//	double vector_z = sin(DEG2RAD(get_direction()));
//	double cosYaw = cos(DEG2RAD(direction)) * 10;
//	double sinYaw = sin(DEG2RAD(direction)) * 10;
//	double sinPitch = sin(DEG2RAD(pitch)) * 10;

//	rocket->SetAudioSystem(audioSys);
//	rocket->LoadAudio(audioSys, "explode.wav", false);
}
void Player::v_collision(Object *obj)
{
//	if(obj->object_type_ == ENEMY)
//	{
//		speed() = 0;
//	}
}
void Player::v_draw(float second)
{
	static float second_passed = 0;        // time in s between emit 2 rocket
	second_passed += second;

	if(second_passed > 0.2 && emited_rocket_ < rocket_to_emit_)        // && rocket_interval_time <= 0)
	{
		emit_rocket();
		emited_rocket_ = rocket_to_emit_;
		second_passed = 0;        // s
	}
}
void Player::update_input(float second)
{
//	want_to_go_forward(player_go_forward_);
//	want_to_go_back(player_go_back_);
//	want_to_go_left(player_go_left_);
//	want_to_go_right(player_go_right_);
//	want_to_jump(player_jump_);
//	want_to_turn_left(player_turn_left_);
//	want_to_turn_right(player_turn_right_);

//	go_upper() = player_go_upper_;
//	go_lower() = player_go_lower_;

//	mouse_move_x_ = abs(mouse_move_x_) > 1 ? mouse_move_x_ : 0;
//	yaw() += mouse_move_x_ * 0.05;
//	mouse_move_x_ = 0;

//	ahead_yaw() += turn_direction_ * 5;
}

