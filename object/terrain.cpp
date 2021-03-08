/*
 * imagine.c
 *
 *  Created on: 2018年11月1日
 *      Author: x
 */

#include "terrain.h"

#include "texture.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float FRAND()		// returns a number ranging from -1.0 to 1.0
{
	return ((float) rand() - (float) rand()) / RAND_MAX;
}
Terrain::Terrain()
{
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_CCW);

//	glClearColor(0.5, 0.5, 1.0, 0.0);

//	float blue[4] = {0.5, 0.5, 1.0, 0.0};
//	float white[4] = {0.9, 0.9, 0.9, 1};
//	glEnable(GL_FOG);
//	glFogfv(GL_FOG_COLOR, white);
//	glFogf(GL_FOG_MODE, GL_EXP2);
//	glFogf(GL_FOG_START, 500);
//	glFogf(GL_FOG_END, 800);
//	glFogf(GL_FOG_DENSITY, 0.01f);

//	Texture t;
	texture_id_ = Load_texture((char*) "models/ground.bmp");
	init_terrain();
}
Terrain::~Terrain()
{

}
void Terrain::init_terrain()
{
	int k;
	float h = 0.2;
// loop through all of the heightfield points, randomly generating height values
	for(int z = 0; z < MAP_Z; z++)
	{
		for(int x = 0; x < MAP_X; x++)
		{
			k = z * MAP_X + x;
			terrain_[k][0] = float(x) * MAP_SCALE;
			terrain_[k][1] = h + FRAND() * h;
			terrain_[k][2] = -float(z) * MAP_SCALE;

			// set the values in the color array
			color_ar_[k][0] = color_ar_[k][1] = color_ar_[k][2]
					= terrain_[x + z * MAP_X][1] / 20.0f + 0.5;

			// set the values in the texture coordinate array. since the texture
			// is tiled over each "square", we can use texture wrapping
			texcoord_ar_[k][0] = (float) x / (MAP_X);
			texcoord_ar_[k][1] = (float) z / (MAP_Z);
		}
	}

	for(int z = MAP_Z / 2 - 4; z >= 0 && z < MAP_Z / 2 + 4; z++)
	{
		for(int x = MAP_X / 2 - 2; x >= 0 && x < MAP_X / 2 + 2; x++)
		{
			k = z * MAP_X + x;
//			terrain_[k][0] = float(x) * MAP_SCALE;
			terrain_[k][1] += h * 10;
//			terrain_[k][2] = -float(z) * MAP_SCALE;
		}
	}

#if GL_DRAW_ELEMENTS
// loop over all vertices in the terrain map
	int i = 0;
	for(int z = 0; z < MAP_Z - 1; z++)
	{
		for(int x = 0; x < MAP_X; x++)
		{
			k = z * MAP_X + x;
			// add next two elements to the triangle strip
			index_ar_[i++] = k + MAP_X;
			index_ar_[i++] = k;

//			printf("%d %d \n", k + MAP_X, k);
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, terrain_);

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, color_ar_);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoord_ar_);

#endif
}

void Terrain::draw_terrain()
{
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

#if GL_DRAW_ELEMENTS
	for(int z = 0; z < MAP_Z - 1; z++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, MAP_X * 2, GL_UNSIGNED_INT, &index_ar_[MAP_X * 2 * z]);
	}
#else

	glColor3f(0, 0, 1);
	int i = 0;

	for(int z = 0; z < MAP_Z - 1; z++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for(int x = 0; x < MAP_X; x++)
		{
			i = z * MAP_X + x;
			i += MAP_X;
			glColor3f(color_ar_[i][0], color_ar_[i][1], color_ar_[i][2]);
			glTexCoord2f(texcoord_ar_[i][0], texcoord_ar_[i][1]);
			glVertex3f(terrain_[i][0], terrain_[i][1], terrain_[i][2]);

			i -= MAP_X;
			glTexCoord2f(texcoord_ar_[i][0], texcoord_ar_[i][1]);
			glVertex3f(terrain_[i][0], terrain_[i][1], terrain_[i][2]);
		}

		glEnd();
	}
#endif
}

void Terrain::draw_terrain_lines()
{
// select the sand texture
	glDisable(GL_TEXTURE_2D);

#if GL_DRAW_ELEMENTS
	for(int z = 0; z < MAP_Z - 1; z++)
	{
		glDrawElements(GL_LINE_STRIP, MAP_X * 2, GL_UNSIGNED_INT, &index_ar_[MAP_X * 2 * z]);
		break;
	}
#else
	glColor3f(0, 0, 1);
	int i = 0;

	for(int z = 0; z < MAP_Z - 1; z++)
	{
		glBegin(GL_LINE_STRIP);

		for(int x = 0; x < MAP_X; x++)
		{
			i = z * MAP_X + x;
			i += MAP_X;
			glVertex3f(terrain_[i][0], terrain_[i][1], terrain_[i][2]);

			i -= MAP_X;
			glVertex3f(terrain_[i][0], terrain_[i][1], terrain_[i][2]);
		}

		glEnd();
	}

#endif
}
int Terrain::width()
{
	return (MAP_X - 1) * MAP_SCALE;
}
int Terrain::height()
{
	return (MAP_Z - 1) * MAP_SCALE;
}
void Terrain::draw(void)
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	draw_terrain_lines();
	draw_terrain();
//	draw_cacus();
}
bool Terrain::coord_is_in_map(float x, float z)
{
//	if(geometric_center_coord_.x < 0)
//		geometric_center_coord_.x = 0;
//	if(geometric_center_coord_.x > (terrain_->width() - 1) * terrain_->terrain_mul())
//		geometric_center_coord_.x = (terrain_->width() - 1) * terrain_->terrain_mul();
//	if(geometric_center_coord_.z < -(terrain_->height() - 1) * terrain_->terrain_mul())
//		geometric_center_coord_.z = -(terrain_->height() - 1) * terrain_->terrain_mul();
//	if(geometric_center_coord_.z > 0)
//		geometric_center_coord_.z = 0;

	bool b = true;
	b &= (x >= 0);
	b &= (x <= width());
	b &= (z <= 0);
	b &= (z >= -height());

	return b;
}
float Terrain::terrain_Y_coord(float x, float z)
{
	if(coord_is_in_map(x, z) == false)
	{
		return -1 * LARGE_FLOAT_NUMBER;        // -1*a is more eye-catching than -a
	}
//	x = Clamp<float>(x, 0, (MAP_X - 1) * MAP_SCALE);
//	z = Clamp<float>(z, -(MAP_Z - 1) * MAP_SCALE, 0);

// divide by the grid-spacing if it is not 1
	float projCameraX = x / MAP_SCALE;
	float projCameraZ = -z / MAP_SCALE;

// compute the height field coordinates (hflCol0, hflRow0) and
// (hflCol1, hflRow1) that identify the height field cell directly below the camera.
	int hflCol0 = int(projCameraX);
	int hflRow0 = int(projCameraZ);
	int hflCol1 = hflCol0 + 1;
	int hflRow1 = hflRow0 + 1;

// get the four corner heights of the cell from the height field
	float h00 = terrain_[hflCol0 + hflRow0 * MAP_X][1];
	float h01 = terrain_[hflCol1 + hflRow0 * MAP_X][1];
	float h11 = terrain_[hflCol1 + hflRow1 * MAP_X][1];
	float h10 = terrain_[hflCol0 + hflRow1 * MAP_X][1];

// calculate the position of the camera relative to the cell.
// note, that 0 <= tx, ty <= 1.
	float tx = projCameraX - float(hflCol0);
	float ty = projCameraZ - float(hflRow0);

// the next step is to perform a bilinear interpolation to compute the height
// of the terrain directly below the object.
	float txty = tx * ty;

	return h00 * (1.0f - ty - tx + txty)
			+ h01 * (tx - txty)
			+ h11 * txty
			+ h10 * (ty - txty);
}

