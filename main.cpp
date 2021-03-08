/*
 */

#include "h.h"
#include "world.h"

int screen_w = 640;
int screen_h = 480;
World * world;

void keyboard_cb(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'W':
			case 'w':
			world->player_->want_to_go_forward(true);
			break;

		case 'S':
			case 's':
			world->player_->want_to_go_back(true);
			break;

		case 'A':
			case 'a':
			world->player_->want_to_go_left(true);
			break;

		case 'D':
			case 'd':
			world->player_->want_to_go_right(true);
			break;

		case ' ':
			world->player_->want_to_jump(true);
			break;

//		case 'U':
//			case 'u':
//			world->player_->player_go_upper(true);
//			break;
//
//		case 'L':
//			case 'l':
//			world->player_->player_go_lower(true);
//			break;

		case '\e':
			exit(0);
			break;

//		case '!':
//			case '1':
//			world->player_->mouseSensitivity_ -= 0.002f;
//			if(world->player_->mouseSensitivity_ < 0.002)
//				world->player_->mouseSensitivity_ = 0.002;
//			break;
//
//		case '@':
//			case '2':
//			world->player_->mouseSensitivity_ += 0.002f;
//			break;

		default:
			break;
	}
}
void keyboard_cb_up(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'W':
			case 'w':
			world->player_->want_to_go_forward(false);
			break;

		case 'S':
			case 's':
			world->player_->want_to_go_back(false);
			break;

		case 'A':
			case 'a':
			world->player_->want_to_go_left(false);
			break;

		case 'D':
			case 'd':
			world->player_->want_to_go_right(false);
			break;

		case ' ':
			world->player_->want_to_jump(false);        // todo: want_to_jump_ can not keep == true
			break;

//		case 'U':
//			case 'u':
//			world->player_->player_go_upper(false);
//			break;
//
//		case 'L':
//			case 'l':
//			world->player_->player_go_lower(false);
//			break;

		default:
			break;
	}
}
void mouse_cb(int button, int state, int x, int y)
{
	/* mouse x,y are given in window coordinates
	 */
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)
			{
				world->player_->rocket_to_emit_++;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			break;
	}
	return;
}
void mouse_cb_passive_motion(int x, int y)
{
	static int i = 0;
	static int pre_x = 0;
	if(i == 0)
	{
		pre_x = x;
		i++;
	}
	int mouse_move_x_ = x - screen_w / 2;
	world->player_->muzzle_yaw() = world->player_->ahead_yaw() + mouse_move_x_ * 0.05;

	pre_x = x;

	if(x < screen_w * 0.001)
	{
		world->player_->want_to_turn_left(true);
	}
	else
	{
		world->player_->want_to_turn_left(false);
	}
	if(x > screen_w * 0.999)
	{
		world->player_->want_to_turn_right(true);
	}
	else
	{
		world->player_->want_to_turn_right(false);
	}

	return;
}
void reshape(int w, int h)
{
	screen_w = w;
	screen_h = h;

//	glPixelZoom();

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(54.0, (float) w / (float) h, 0.5f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void idle()
{
// check for forward and backward motion

	static int t0 = 0;
	int t = glutGet(GLUT_ELAPSED_TIME);

	static int frames = 0;
	frames++;
	if(t - t0 >= 2000)
	{
		float seconds = (t - t0) / 1000.0;
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bfps: %.1f, s: %.1f, %ld", frames / seconds, t / 1000.0,
				Object::object_list_.size());
		fflush(stdout);
		t0 = t;
		frames = 0;
	}

	glutPostRedisplay();
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	glEnable(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);

//	float white[4] = {0.9, 0.9, 0.9, 1};
//	glEnable(GL_FOG);
//	glFogfv(GL_FOG_COLOR, white);
//	glFogf(GL_FOG_MODE, GL_EXP2);
//	glFogf(GL_FOG_START, 500);
//	glFogf(GL_FOG_END, 800);
//	glFogf(GL_FOG_DENSITY, 0.01f);

	world->display();

	glutSwapBuffers();
}
int main(int argc, char **argv)
{
	printf("Welcome to A Time to Kill! \n\n"
			"Keys: \n"
			"W - Forward \n"
			"S - Backward \n"
			"A - Left Strafe \n"
			"D - Right Strafe \n\n"
			"2 - Increase mouse sensitivity \n"
			"1 - Decrease mouse sensitivity \n\n"
			"Left mouse button fires rockets. \n"
			"Move mouse to look around \n\n"
			"You have 5 minutes to kill all of the enemies on the terrain using your rockets.\n\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(screen_w, screen_h);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(nullptr);
//	glutFullScreen();

	world = new World();

	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard_cb);
	glutKeyboardUpFunc(keyboard_cb_up);
	glutMouseFunc(mouse_cb);
	glutPassiveMotionFunc(mouse_cb_passive_motion);
//	glutSpecialFunc (keyboard_cb_special);
//	glutSpecialUpFunc (keyboard_cb_special_up);
	glutWarpPointer(screen_w / 2, screen_h / 2);
//	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();
	return 0;
}
