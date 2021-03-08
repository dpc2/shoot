/*
 *
 */

#include "camera.h"
#include "h.h"

Camera::Camera(Object * object)
{
	obj = object;
}
Camera::~Camera()
{
}
//void Camera::UpdateLookAt()
//{
//	Vector look = Vector(finalLookAt_.x - look_at_.x,
//			finalLookAt_.y - look_at_.y,
//			finalLookAt_.z - look_at_.z);
//
//	lookAtVel_ = look * 0.5;
//}
//void Camera::UpdateMoveTo()
//{
//	Vector pos = Vector(finalPosition_.x - position_.x,
//			finalPosition_.y - position_.y,
//			finalPosition_.z - position_.z);
//
//	speed_ = pos * 0.5;
//}
//
//void Camera::RotatePitch(scalar_t radians)
//{
//	float sine = sinf(radians);
//	float cosine = cosf(radians);
//
//	up_.y = cosine * up_.Length();
//	up_.z = sine * up_.Length();
//
//	/*     x   y      z       p
//	 |  1  0       0       0 |
//	 M = |  0  cos(A) -sin(A)  0 |
//	 |  0  sin(A)  cos(A)  0 |
//	 |  0  0       0       1 |
//	 */
//}
//void Camera::RotateYaw(scalar_t radians)
//{
//	float sine = sinf(radians);
//	float cosine = cosf(radians);
//
//	/*	   x      y    z      p
//	 |  cos(A)  0  -sin(A)  0 |
//	 M = |  0       1   0       0 |
//	 |  sin(A)  0   cos(A)  0 |
//	 |  0       0   0       1 |
//	 */
//}
//void Camera::RotateRoll(scalar_t radians)
//{
//	float sine = sinf(radians);
//	float cosine = cosf(radians);
//
//	/*
//	 |  cos(A)  -sin(A)   0   0 |
//	 M = |  sin(A)   cos(A)   0   0 |
//	 |  0        0        1   0 |
//	 |  0        0        0   1 |
//	 */
//}
//void Camera::LookAtNow(Vector &direction)
//{
//	look_at_ = direction;		// ???
//}
//void Camera::MoveToNow(scalar_t x, scalar_t y, scalar_t z)
//{
//	position_.x = x;
//	position_.y = y;
//	position_.z = z;
//}
//void Camera::MoveToNow(Vector &target_position)
//{
//	position_ = target_position;
//}
void Camera::update()
{
	position_ = obj->eyes_coord();
	look_at_ = obj->look_at_coord();
	up_ = obj->up();

	gluLookAt(position_.x, position_.y, position_.z,
			look_at_.x, look_at_.y, look_at_.z,
			up_.x, up_.y, up_.z);
}
//// look at an object over time
//void Camera::LookAt(Vector &object_position)
//{
////	Vector v = Vector(object->position - look_at_);
//	initLookAt_ = look_at_;
//	finalLookAt_ = object_position;
//	lookAtAccel_ = -look_at_ * 0.25f;
//	UpdateLookAt();
//}
//// move to an object over time
//void Camera::MoveTo(Vector &object_position)
//{
////	Vector v = Vector(object->position - position);
//	initPosition_ = position_;
//	finalPosition_ = object_position;
////	acceleration_ = -position_ * 0.25f;
//	UpdateMoveTo();
//}

