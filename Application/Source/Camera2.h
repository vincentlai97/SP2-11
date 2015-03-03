#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Camera.h"
#include "Vector3.h"
#include <vector>
#include "CollisionBox.h"

class Camera2 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	enum STATE
	{
		JUMPING,
		NJUMPING,
		SitDown,
		StandUp,
	};

	int state;
	float jumpHeight;

	Camera2();
	~Camera2();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, CollisionBox cameraCollisionBox, std::vector<CollisionBox*> v, float w, float h, double* xPos, double* yPos);
	virtual void Reset();
};

#endif