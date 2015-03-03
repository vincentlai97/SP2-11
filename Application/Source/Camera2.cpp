#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"

Camera2::Camera2()
{
}

Camera2::~Camera2()
{
}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	state = NJUMPING;
	state = SitDown;
	state = StandUp;
	jumpHeight = 0;
}

void Camera2::Update(double dt, CollisionBox cameraCollisionBox, const std::vector<CollisionBox*> v, float width, float height, double* xPos, double* yPos)
{
	static const float CAMERA_SPEED = 70.f;
	static const float MOUSE_SPEED = 10.f;

	double mouseX = width;
	double mouseY = height;

	bool ToiletUsed;

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
	view.y = 0;
	view.Normalize();
	Vector3 incr(0, 0, 0);
	if (state == NJUMPING)
	{
		incr.y -= CAMERA_SPEED * dt;
		jumpHeight -= CAMERA_SPEED * dt;
	}
	else if (state == JUMPING)
	{
		if (jumpHeight > 20) state = NJUMPING;
		else 
		{
			incr.y += CAMERA_SPEED * dt;
			jumpHeight += CAMERA_SPEED * dt;
		}
	}

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

	if (cameraCollisionBox.checkCollision(v, incr))
	{
		bool overlap[3];
		overlap[0] = cameraCollisionBox.checkCollision(v, Vector3(incr.x, 0, 0));
		overlap[1] = cameraCollisionBox.checkCollision(v, Vector3(0, incr.y, 0));
		overlap[2] = cameraCollisionBox.checkCollision(v, Vector3(0, 0, incr.z));
		if (overlap[0]) incr.x = 0;
		if (overlap[1]) incr.y = 0;
		if (overlap[2]) incr.z = 0;
	}
	position += incr;
	target += incr;

	if (Application::IsKeyPressed(VK_SPACE) && state == NJUMPING && incr.y == 0 && jumpHeight <= 2)
	{
		state = JUMPING;
		jumpHeight = 0;
	}
}

void Camera2::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}