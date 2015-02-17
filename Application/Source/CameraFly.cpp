#include "CameraFly.h"
#include "Application.h"
#include "Mtx44.h"

CameraFly::CameraFly()
{
}

CameraFly::~CameraFly()
{
}

void CameraFly::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void CameraFly::Update(double dt, const std::vector<Vector3> v, float width, float height, double* xPos, double* yPos)
{
	static const float CAMERA_SPEED = 100.f;
	static const float MOUSE_SPEED = 20.f;

	double mouseX = width;
	double mouseY = height;

	if(Application::IsKeyPressed(VK_LEFT) || (*xPos > mouseX))
	{
		
		float yaw = (float)(MOUSE_SPEED * dt * (mouseX - *xPos));
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = view + position;
		up = rotation * up;
	}
	if(Application::IsKeyPressed(VK_RIGHT) || (*xPos < mouseX))
	{
		float yaw = (float)(-MOUSE_SPEED * dt * (*xPos - mouseX));
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = view + position;
		up = rotation * up;
	}
	if(Application::IsKeyPressed(VK_UP) || (*yPos > mouseY))
	{
		float pitch = (float)(MOUSE_SPEED * dt * (mouseY - *yPos));
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
		up = right.Cross(view).Normalized();
	}
	if(Application::IsKeyPressed(VK_DOWN) || (*yPos < mouseY))
	{
		float pitch = (float)(-MOUSE_SPEED * dt * (*yPos - mouseY));
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
		up = right.Cross(view).Normalized();
	}
	/*if(Application::IsKeyPressed('N'))
	{
		Vector3 direction = target - position;
		if(direction.Length() > 5)
		{
			Vector3 view = (target - position).Normalized();
			position += view * (float)(10.f * dt);
		}
	}
	if(Application::IsKeyPressed('M'))
	{
		Vector3 view = (target - position).Normalized();
		position -= view * (float)(10.f * dt);
	}*/
	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	
	Vector3 view = (target-position);
	view.Normalize();
	Vector3 incr(0, 0, 0);
	if (Application::IsKeyPressed('W'))
	{
		incr += view * CAMERA_SPEED * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		incr -= view * CAMERA_SPEED * dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		Vector3 right = view.Cross(up);
		right.Normalize();
		incr -= right * CAMERA_SPEED * dt;
	}
	if (Application::IsKeyPressed('D'))
	{
		Vector3 right = view.Cross(Vector3(up));
		right.Normalize();
		incr += right * CAMERA_SPEED * dt;
	}

	/*if (checkCollision(v, incr))
	{
		bool overlap[3];
		overlap[0] = checkCollision(v, Vector3(incr.x, 0, 0));
		overlap[1] = checkCollision(v, Vector3(0, incr.y, 0));
		overlap[2] = checkCollision(v, Vector3(0, 0, incr.z));
		if (overlap[0]) incr.x = 0;
		if (overlap[1]) incr.y = 0;
		if (overlap[2]) incr.z = 0;
	}*/
	position += incr;
	target += incr;
}

void CameraFly::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

bool CameraFly::checkCollision(const std::vector<Vector3> v, Vector3 incr, std::string obj)
{
	Vector3 pos = position + incr;
	Vector3 posMax(pos);
	Vector3 posMin(pos);
	if (!obj.compare("character"))
	{
		posMax += Vector3(5, 5, 5);
		posMin -= Vector3(5, 15, 5);
	}
	else if (!obj.compare("pokeball"))
	{
		posMax += Vector3(2, 2, 2);
		posMin -= Vector3(2, 2, 2);
	}

	for (int count = 0; count < v.size(); count+=2)
	{
		if (posMax.x >= v[count+1].x && posMin.x <= v[count+0].x)
		if (posMax.y >= v[count+1].y && posMin.y <= v[count+0].y)
		if (posMax.z >= v[count+1].z && posMin.z <= v[count+0].z)
			return true;
	}
	return false;
}