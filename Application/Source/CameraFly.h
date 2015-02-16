#ifndef CAMERA_FLY_H
#define CAMERA_FLY_H

#include "Camera.h"
#include "Vector3.h"
#include <vector>

class CameraFly : public Camera
{
	int state;
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	CameraFly();
	~CameraFly();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, std::vector<Vector3> v, float w, float h, double* xPos, double* yPos);
	virtual void Reset();
	bool checkCollision(const std::vector<Vector3> v, Vector3 incr, std::string obj = "character");
};

#endif