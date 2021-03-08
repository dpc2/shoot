/*
 *
 */

#ifndef __CAMERA_H
#define __CAMERA_H

#include "object.h"
#include "vector.h"

class Camera
{
private:
	Object * obj;
	Vector position_;			// position of camera
	Vector look_at_;
	Vector up_;

public:
	Camera(Object * object);
	~Camera();

	void update();
};

#endif

