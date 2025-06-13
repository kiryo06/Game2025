#include "Camera.h"
#include "DxLib.h"

Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::Init() const
{
	SetCameraNearFar(0.5f, 100.0f);
	SetCameraPositionAndAngle(VGet(-50, 0, -50), 0.0f, 0.0f, 0.0f);
}

void Camera::Update() const
{
}

void Camera::Draw() const
{
}
