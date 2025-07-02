#include "Camera.h"
#include <cmath>
#include "Player.h"
#include "Pad.h"

namespace
{
	constexpr float kReset = 0.0f;
	constexpr float kMoveSpeed = 0.001f;
}
Camera::Camera():
	m_pos(VGet(0.0f, 400.0f, 1200.0f)),
	m_targetPos(VGet(0.0f, 200.0f, 0.0f)),
	m_move(VGet(0.05f, 0.05f, 0.0f)),
	m_cameraRot(VGet(0.0f, 0.0f, 0.0f)),
	m_cameraPosAtan2(0.0f),
	m_cemeraGetPos(VGet(0.0f,0.0f,0.0f)),
	m_cameraGetTarget(VGet(0.0f,0.0f,0.0f))
{
}

Camera::~Camera()
{
}

void Camera::Init()const
{
	// �J������Near,Far
	SetCameraNearFar(0.0f, 2000.0f);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_targetPos);
	SetupCamera_Perspective(48.0f * DX_PI_F / 180.0f);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);
	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);
}

void Camera::Update(Player* m_pPlayer)
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
	if (CheckHitKey(KEY_INPUT_NUMPAD8) || Pad::GetRightStick().y > 1.0f)
	{
		if (m_cameraRot.x >= -0.7f)
		{
			m_cameraRot.x -= m_move.x;
		}
	}

	// �J�����̉�]����]
	if (CheckHitKey(KEY_INPUT_NUMPAD2) || Pad::GetRightStick().y < -1.0f)
	{
		if (m_cameraRot.x <= 1.2f)
		{
			m_cameraRot.x += m_move.x;
		}
	}

	// �J�����̉�]����]
	if (CheckHitKey(KEY_INPUT_NUMPAD4) || Pad::GetRightStick().x > 1.0f)
	{
		m_cameraRot.y += m_move.y;
	}

	// �J�����̉�]�E��]
	if (CheckHitKey(KEY_INPUT_NUMPAD6) || Pad::GetRightStick().x < -1.0f)
	{
		m_cameraRot.y -= m_move.y;
	}


	// �J�����̉�]�ʂ�MATRIX�ŕϊ�
	MATRIX cameraRotMtxX = MGetRotX(m_cameraRot.x);
	MATRIX cameraRotMtxY = MGetRotY(m_cameraRot.y);

	// �J�����̈ʒu���X�V
	VECTOR toCameraX = VTransform(m_pos, cameraRotMtxX);
	VECTOR toCameraXY = VTransform(toCameraX, cameraRotMtxY);

	// �v���C���[�Ǐ]
	VECTOR toCameraPlayerPos = VAdd(toCameraXY, VAdd(m_pPlayer->GetPos(),VGet(0,600,0)));
	VECTOR toCameraPlayerTarget = VAdd(m_targetPos, m_pPlayer->GetPos());


	// �J�����ݒ�A�����_�̍X�V
	SetCameraPositionAndTarget_UpVecY(toCameraPlayerPos, toCameraPlayerTarget);
	DrawFormatString(10, 132, 0xff0000, "%f", m_cameraRot.x);
	DrawFormatString(10, 116, 0xff0000, "Move X:%.3f | Move Y:%.3f | Move Z:%.3f", toCameraX.x, toCameraX.y, toCameraX.z);


	// �J�����̈ʒu��Norm�����l������ϐ�
	VECTOR cameraPosNorm = VNorm(VSub(GetCameraPosition(),GetCameraTarget()));
	// �J�����̃A�[�N�^���W�F���g��ۑ�
	m_cameraPosAtan2 = atan2(cameraPosNorm.z, cameraPosNorm.x);

	// �J�����̈ʒu�ƒ����_�����炤
	m_cemeraGetPos = GetCameraPosition();
	m_cameraGetTarget = GetCameraTarget();

	// �w�莲�Ŏw��p�x��]����s����擾
	//MGetRotAxis(m_cemeraGetPos, m_cameraPosAtan2);

	m_cemeraGetPos = VNorm(VGet(m_cemeraGetPos.x,0.0f,m_cemeraGetPos.z));
}

void Camera::Draw() const
{

	
	DrawFormatString(10, 100, 0xff0000, "Move X:%.3f | Move Y:%.3f | Move Z:%.3f", m_move.x, m_move.y, m_move.z);
	// �J�����̈ʒu����\��
	DrawLine3D(VGet(m_cemeraGetPos.x * 1000000, 0.0f, m_cemeraGetPos.z * 1000000), VGet(m_cameraGetTarget.x, 0.0f, m_cameraGetTarget.z), 0xffffff);
	DrawFormatString(321, 0, 0xfffff, "%f", m_cameraPosAtan2);
}