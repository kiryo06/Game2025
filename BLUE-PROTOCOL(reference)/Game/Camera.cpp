#include "Camera.h"

namespace
{
	constexpr float kMoveSpeed = 0.1f;
}
Camera::Camera():
	m_pos(VGet(0.0f, 400.0f, -1200.0f)),
	m_targetPos(VGet(0.0f, 200.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f))
{

}

Camera::~Camera()
{
}

void Camera::Init() const
{
	// カメラのNear,Far
	SetCameraNearFar(400.0f, 2000.0f);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	SetupCamera_Perspective(48.0f * DX_PI_F / 180.0f);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);
	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_NUMPAD0))
	{
		m_move = VAdd(m_move,VGet(kMoveSpeed, kMoveSpeed, kMoveSpeed));
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD4))
	{
		m_pos.z = m_move.z;
	}
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
}

void Camera::Draw() const
{

}
