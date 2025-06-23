#include "Camera.h"

namespace
{
	constexpr float kReset = 0.0f;
	constexpr float kMoveSpeed = 0.001f;
}
Camera::Camera():
	m_pos(VGet(0.0f, 400.0f, 1200.0f)),
	m_targetPos(VGet(0.0f, 200.0f, 0.0f)),
	m_move(VGet(0.0f, 0.0f, 0.0f)),
	m_cameraRot(VGet(0.0f, 0.0f, 0.0f))
{
}

Camera::~Camera()
{
}

void Camera::Init() const
{
	// �J������Near,Far
	SetCameraNearFar(400.0f, 2000.0f);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	SetupCamera_Perspective(48.0f * DX_PI_F / 180.0f);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);
	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);
}

void Camera::Update()
{
	// �J�����̉�]���x���グ��
	if (CheckHitKey(KEY_INPUT_NUMPAD0))
	{
		if (m_move.x <= 0.1f)
		{
			m_move.x += kMoveSpeed;
			m_move.y += kMoveSpeed;
		}
	}
	// �J�����̉�]���x������
	if (CheckHitKey(KEY_INPUT_NUMPAD1))
	{
		m_move.x -= kMoveSpeed;
		m_move.y -= kMoveSpeed;
		if (m_move.x <= 0.0f)
		{
			m_move.x = kReset;
			m_move.y = kReset;
		}
	}
	// �J�����̉�]�p�x�����Z�b�g
	if (CheckHitKey(KEY_INPUT_NUMPAD5))
	{
		m_cameraRot.x = kReset;
		m_cameraRot.y = kReset;
	}
	// �J�����̉�]���]
	if (CheckHitKey(KEY_INPUT_NUMPAD8))
	{
		if (m_cameraRot.x >= -0.7f)
		{
			m_cameraRot.x -= m_move.x;
		}
	}
	// �J�����̉�]����]
	if (CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		if (m_cameraRot.x <= 1.2f)
		{
			m_cameraRot.x += m_move.x;
		}
	}
	// �J�����̉�]����]
	if (CheckHitKey(KEY_INPUT_NUMPAD4))
	{
		m_cameraRot.y += m_move.y;
	}
	// �J�����̉�]�E��]
	if (CheckHitKey(KEY_INPUT_NUMPAD6))
	{
		m_cameraRot.y -= m_move.y;
	}


	// �J�����̉�]�ʂ�MATRIX�ŕϊ�
	MATRIX cameraRotMtxX = MGetRotX(m_cameraRot.x);
	MATRIX cameraRotMtxY = MGetRotY(m_cameraRot.y);
//	MATRIX cameraRotMtxZ = MGetRotZ(m_cameraRot.z);

	// �J�����̈ʒu���X�V
	VECTOR toCameraX = VTransform(m_pos, cameraRotMtxX);
	VECTOR toCameraXY = VTransform(toCameraX, cameraRotMtxY);

	// �v���C���[�Ǐ]
//	VECTOR toCameraPlayer = VAdd(toCamera, m_pPlayer->GetPos());

	// �J�����ݒ�A�����_�̍X�V
	SetCameraPositionAndTarget_UpVecY(toCameraXY, m_targetPos);
	DrawFormatString(10, 132, 0xff0000, "%f", m_cameraRot.x);
	DrawFormatString(10, 116, 0xff0000, "Move X:%.3f | Move Y:%.3f | Move Z:%.3f", toCameraX.x, toCameraX.y, toCameraX.z);
}

void Camera::Draw() const
{
	DrawFormatString(10, 100, 0xff0000, "Move X:%.3f | Move Y:%.3f | Move Z:%.3f", m_move.x, m_move.y, m_move.z);
}
