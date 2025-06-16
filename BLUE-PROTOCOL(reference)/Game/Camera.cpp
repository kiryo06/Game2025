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
	SetCameraNearFar(400.0f, 2000.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 400, -1200), VGet(0, 200, 0));
	SetupCamera_Perspective(48.0f * DX_PI_F / 180.0f);
}

void Camera::Update() const
{

}

void Camera::Draw() const
{

}
