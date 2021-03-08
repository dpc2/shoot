/*
 *
 */

#include "rocket.h"

Rocket::Rocket(Terrain *terrain)
		: Object(terrain)
{
	object_type_ = Object::ROCKET;
	horizontal_speed() = 30;        // set speed_z
	collision_radius() = 0.01;

	//	get_acceleration() = Vector(0, 0, 0);        // 加速度

	md2_ = new ModelMD2();
	md2_->Load((char*) "models/rocketair.md2", (char*) "models/rocket.pcx");
	md2_->interpol = 1.0f;
	md2_->SetState(MODEL_RUN);

	bomb_ = nullptr;
	is_bombing_ = false;
//	load_bomb_texture();

	Object::object_list_.push_back(this);
}

Rocket::~Rocket()
{
	if(bomb_ != nullptr)
	{
		bomb_->KillSystem();
		delete[] bomb_;
		bomb_ = nullptr;
	}

	if(bomb_texture_ != nullptr)
	{
		delete bomb_texture_;
		bomb_texture_ = nullptr;
	}
}
//void Rocket::load_bomb_texture()
//{
//	bomb_texture_ = new Texture((char*) "models/bomb.bmp");
//
//	glGenTextures(1, &bomb_texture_->texID);
//	glBindTexture(GL_TEXTURE_2D, bomb_texture_->texID);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
////	glTexImage2D(GL_TEXTURE_2D, 0, 4, bomb_texture->width, bomb_texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bomb_texture->data);
//	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bomb_texture_->width, bomb_texture_->height, GL_RGBA, GL_UNSIGNED_BYTE,
//			bomb_texture_->data);
//}
void Rocket::v_collision(Object *obj)
{
	if(obj->object_type_ == ENEMY)
	{
		horizontal_speed() = 0;
		status() = DEAD;
		is_bombing_ = true;
//		bomb_ = new Bomb(500, geometric_center(), 8.0, bomb_texture_->texID);
//			PlaySound();
		return;
	}

	if(is_bombing_ == false && is_on_ground() == true)
	{
		horizontal_speed() = 0;
		is_bombing_ = true;
//		bomb_ = new Bomb(500, geometric_center(), 8.0, bomb_texture_->texID);
//				PlaySound();
	}
}
void Rocket::v_draw(float second)
{
////	position() += speed() * s_passed;
////	position_.y = terrain_->GetHeight(position_.x, position_.z) + size_;
////	get_velocity() += get_acceleration() * s_passed;

//	float cosYaw = (float)cos(DEG2RAD(direction));
//	float sinPitch = (float)sin(DEG2RAD(pitch));
//	float sinYaw = (float)sin(DEG2RAD(direction));

	{
//		double s = velocity.z * deltaTime;
//		get_position().x += vector_x * s;
//		get_position().y += vector_y * s;
//		get_position().z += vector_z * s;
	}
	{
//		LOG("deltaTime %f", deltaTime);
//		Vector velocity_old = velocity;
//		Vector velocity_average = (velocity + velocity_old) / 2;

//	s = s * Vector(cosYaw, sinYaw, sinPitch);
//		Vector s = get_velocity() * deltaTime;
//		set_velocity(get_velocity() + get_acceleration() * deltaTime);
//		set_position(get_position() + s);
	}

	if(status() == DEAD)
	{
		return;
	}
	want_to_go_forward(true);
//		go_back_ = false;
//		go_left_ = false;
//		go_right_ = false;
//		go_upper_ = false;
//		go_lower_ = false;

//	LOG("is_bombing_: %d", is_bombing_);
//	if(is_bombing_ == true)
//	{
//		if(bomb_->IsDead() /*&& !audioSys->GetPerformance()->IsPlaying(entitySound->GetSegment(), nullptr)*/)
//		{
//			bomb_->KillSystem();
//			delete bomb_;
//			bomb_ = nullptr;
//			is_bombing_ = false;
//			status() = Object::object_status::DEAD;
//			return;
//		}
//
//		bomb_->Update(second);
//		bool b = glIsEnabled(GL_FOG);
//		glDisable(GL_FOG);
//		bomb_->Render();
//		if(b)
//		{
//			glEnable(GL_FOG);
//		}
//		else
//		{
//			glDisable(GL_FOG);
//		}
//
//		return;
//	}

	if(horizontal_traveled_distance() >= 500.0f
			|| is_on_ground() == true)
	{
		LOG();
//		is_bombing_ = true;
		horizontal_speed() = 0;
		vertical_speed() = 0;
//		bomb_ = new Bomb(10, geometric_center(), 0.1, bomb_texture_->texID);
		status() = Object::object_status::DEAD;
//		return;
	}

// if the Rocket has not yet exploded, draw the Rocket model
	bool b = glIsEnabled(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);

	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(core_coord().x, core_coord().y, core_coord().z);
	glRotatef(-ahead_yaw(), 0.0, 1.0, 0.0);

	float a = 1.0 / 240;
	glScalef(a, a, a);
	md2_->render_single_frame(0);

	if(b)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
}
