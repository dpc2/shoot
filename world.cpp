/*
 *
 */

#include "h.h"
#include "world.h"

#include "terrain.h"
#include "rocket.h"

World::World()
{
	terrain_ = new Terrain();
	player_ = new Player(terrain_);
	camera_ = new Camera(player_);

	generate_enemy();
	max_seconds_of_one_game_ = 60 * 5;			// 5 minutes
	timeElapsed_ = 0;
	game_over_ = false;

	gui_ = new CGUI;
	gui_->set_seconds_left(max_seconds_of_one_game_);
	gui_->SetEnemiesLeft(count_object_by_type(Object::object_type::ENEMY));

	//	audioSystem = new CAudioSystem;
	//	audioSystem->InitDirectXAudio(nullptr);
	//	worldSound = audioSystem->Create("ambient.wav", false);
	//	audioSystem->Play(worldSound, DMUS_SEG_REPEAT_INFINITE);
	//	player->SetAudioSystem(audioSystem);
}
World::~World()
{
	delete gui_;
	delete terrain_;
	delete camera_;
//	gui_ = nullptr;
//	terrain_ = nullptr;
//	audioSystem->Shutdown();
//	delete audioSystem;
//	delete worldSound;
//	audioSystem = nullptr;
//	worldSound = nullptr;
}
void World::generate_enemy()
{
#define MAX_ENEMY (1)
//	srand((unsigned int) time(nullptr));
	int enemy_ogro_num, enemy_soldier_num;
//	enemy_ogro_num = enemy_soldier_num = abs(rand() % (MAX_ENEMY - 4)) + 4;        // random # from 4 to MAX
	enemy_ogro_num = enemy_soldier_num = MAX_ENEMY;

//	for(int i = 0; i < enemy_soldier_num; i++)
//	{
//		Enemy *enemy_soldier = new Enemy(terrain_, (char*) "models/sodf8/tris.md2",
//				(char*) "models/sodf8/abarlith.pcx");
//		enemy_soldier->collision_radius() = 6;
//		enemy_soldier->SetPlayer(player_);
////		enemy_ogro->SetAudioSystem(audioSystem);
////		Object::object_list_.push_back(enemy_soldier);
//	}

	for(int i = 0; i < enemy_ogro_num; i++)
	{
		Enemy *enemy_ogro = new Enemy(terrain_, (char*) "models/ogro/tris.md2", (char*) "models/ogro/ogrobase.pcx");
		enemy_ogro->collision_radius() = 0.9;
		enemy_ogro->SetPlayer(player_);
//		enemy_soldier->SetAudioSystem(audioSystem);
//		Object::object_list_.push_back(enemy_ogro);
	}
}
int World::count_object_by_type(Object::object_type type)
{
	int count = 0;

	for(int i = 0; i < (int) Object::object_list_.size(); i++)
	{
		if(type == Object::object_list_[i]->object_type_
				&& Object::object_status::DEAD != Object::object_list_[i]->status())
		{
			count++;
		}
	}

	return count;
}
void World::Animate(float ms_passed)
{
	int enemy_left = count_object_by_type(Object::object_type::ENEMY);
	gui_->SetEnemiesLeft(enemy_left);
	gui_->set_seconds_left(max_seconds_of_one_game_ - timeElapsed_);
	timeElapsed_ += ms_passed;

	if(enemy_left <= 0 || timeElapsed_ > max_seconds_of_one_game_)
	{
		FadeScreen();

		if(enemy_left <= 0)
			gui_->DrawWinner();
		else
			gui_->DrawLoser();
		game_over_ = true;
		exit(0);
	}
//	LOG("enemy %d, timeElapsed %.0f", count_object_by_type(Object::object_type::ENEMY), timeElapsed / 1000);
}
void World::display()
{
	static int ms;
	static int last_ms = 0;
	ms = glutGet(GLUT_ELAPSED_TIME);
	float s = (float) (ms - last_ms) / 1000;
//	LOG("s: %f", s);

	player_->update_input(s);
	player_->draw(s);

//	Vector v = player_->feet_coord();
//	LOG("rocket: x %.1f  y %.2f-%.2f-%.2f  z %.1f "
//			"h_distance_: %.1f, "
//			"h_speed: %.1f, "
//			"v_speed: %.1f",
//			v.x,
//			player_->terrain()->terrain_Y_coord(v.x, v.z), v.y, player_->core_coord().y,
//			v.z,
//			player_->horizontal_traveled_distance(),
//			player_->horizontal_speed(),
//			player_->vertical_speed());

	//	auto p = Object::object_list_.begin();
//	camera_->set_camera_attribute(
//			(*p)->position(),
//			(*p)->look_at(),
//			(*p)->up());


	glLoadIdentity();
	camera_->update();

//	gluLookAt(player_->geometric_center().x, player_->geometric_center().y, player_->geometric_center().z,
//			player_->look_at().x, player_->look_at().y, player_->look_at().z,
//			player_->up().x, player_->up().y, player_->up().z);

	//	LOG("gluLookAt: %.1f %.1f %.1f,         %.1f %.1f %.1f,         %.1f %.1f %.1f",
	//			position_.x, position_.y, position_.z,
	//			look_at_.x, look_at_.y, look_at_.z,
	//			up_.x, up_.y, up_.z);

//	Animate(ms_passed_);

	terrain_->draw();
//	gui_->Draw();

	Rocket * r = NULL;
	Enemy * e = NULL;

//	vector <Object*>::iterator p;
//	LOG("Object::object_list_.size: %ld", Object::object_list_.size());
	for(auto p = Object::object_list_.begin(); p != Object::object_list_.end();)
	{
		if((*p)->object_type_ == Object::PLAYER)
		{
			p++;
			continue;
		}
		if((*p)->object_type_ == Object::ROCKET)
		{
			r = dynamic_cast <Rocket *>(*p);
			if(r->status() == Object::object_status::DEAD)
			{
				p = Object::object_list_.erase(p);
				continue;
			}

//			Vector v = r->feet_coord();
//			LOG("rocket: x %.1f  y %.2f-%.2f-%.2f  z %.1f "
//					"h_distance_: %.1f, "
//					"h_speed: %.1f, "
//					"v_speed: %.1f",
//					v.x,
//					r->terrain()->terrain_Y_coord(v.x, v.z), v.y, r->core_coord().y,
//					v.z,
//					r->horizontal_traveled_distance(),
//					r->horizontal_speed(),
//					r->vertical_speed());
		}
		if((*p)->object_type_ == Object::ENEMY)
		{
			e = dynamic_cast <Enemy *>(*p);
			if(e->status() == Object::object_status::DEAD)
			{
				p = Object::object_list_.erase(p);
				continue;
			}

//			Vector v = e->feet_coord();
//			LOG("enemy: x %.1f  y %.2f-%.2f-%.2f  z %.1f ",
//					v.x,
//					e->terrain()->terrain_Y_coord(v.x, v.z), v.y, e->core_coord().y,
//					v.z);
		}

		(*p)->draw(s);
		p++;
	}

	if(e && r)
	{
		LOG("Length: %.2f < %.2f = %d",
				(r->core_coord() - e->core_coord()).Length(),
				r->collision_radius() + e->collision_radius(),
				(r->core_coord() - e->core_coord()).Length() < r->collision_radius() + e->collision_radius());
	}

	last_ms = ms;
}

void World::FadeScreen()
{
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0, 0.0, 0.0, 0.7);
	glBegin(GL_QUADS);
	glVertex3f(-5, -5, -3.0);
	glVertex3f(5, -5, -3.0);
	glVertex3f(5, 5, -3.0);
	glVertex3f(-5, 5, -3.0);
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

