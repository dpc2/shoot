/*
 * cactus_terrain.h
 *
 *  Created on: 2019年4月20日
 *      Author: x
 */

#ifndef OBJECT_TERRAIN_H_
#define OBJECT_TERRAIN_H_

#include "h.h"

template < typename T >
T Clamp(T x, T min, T max)
{
	if(x > max)
	{
		x = max;
	}
	if(x < min)
	{
		x = min;
	}

	return x;
}
template < typename T >
T SQUARE(T x)
{
	return x * x;
}
template < typename T >
T RAND_COORD(T x)
{
	return (float) rand() / RAND_MAX * x;
}

#ifndef PI
#define PI          3.14
#endif

#define GL_DRAW_ELEMENTS 1

#define MAP_SIZE	30
#define MAP_X		MAP_SIZE        // size of map along x-axis
#define MAP_Z		MAP_SIZE        // size of map along z-axis
#define MAP_SCALE  1.0     // the scale of the terrain map

class Terrain
{
private:
	GLuint texture_id_;        // sand texture
	float terrain_[MAP_X * MAP_Z][3];         // heightfield terrain data (0-255); 256x256
	float color_ar_[MAP_X * MAP_Z][3];        // color array
	float texcoord_ar_[MAP_X * MAP_Z][2];        // tex coord array
	GLuint index_ar_[MAP_X * MAP_Z * 2];        // vertex array

	void draw_terrain_lines();
	void draw_terrain();
	void init_terrain();
	bool coord_is_in_map(float x, float z);

public:

	Terrain();
	virtual ~Terrain();

	void draw(void);
	int width();
	int height();
	float terrain_Y_coord(float x, float z);
};

#endif /* OBJECT_TERRAIN_H_ */
