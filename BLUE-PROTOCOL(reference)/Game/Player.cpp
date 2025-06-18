#include "Player.h"
#include "Pad.h"
#include "Input.h"

namespace
{
	constexpr float kJumpPower = 16.0f;		// �v���C���[�̃W�����v��
	constexpr float kGravity = -0.5f;		// �v���C���[�̏d��

	constexpr float kMoveAccel = 1.0f;		// �v���C���[�̈ړ������x
	constexpr float kMoveDecRate = 0.80f;	// �v���C���[�̈ړ�������

	constexpr int kDefaultHp = 120;			// �v���C���[�̏���HP

	constexpr float kColRadius = 100.0f;		// �v���C���[�̓����蔻��

}

Player::Player() :
	m_model(-1),
	m_pos(0.0f, 20.2f,0.0f),
	m_vec(0.0f,0.0f,0.0f),
	m_modelRot{ 0.0f, 0.0f, 0.0f },
	m_hp(kDefaultHp)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update(Input& input)
{
	//	m_vec = VScale(m_vec, kMoveDecRate);	// �ړ��x�N�g��������
	m_vec.x *= kMoveDecRate;
	m_vec.z *= kMoveDecRate;

	if (isJumping())
	{
		m_vec.y += kGravity;
	}
	else
	{
		m_vec.y = 0.0f;
		m_pos.y = 0.0f;
	}

	// �v���C���[�̈ړ�
	if ((Pad::GetLeftStick)().x < -1.0f)
	{
		m_vec.x += Pad::GetLeftStick().x * 0.001 * -1.0f;
	}
	if ((Pad::GetLeftStick)().x > 1.0f)
	{
		m_vec.x -= Pad::GetLeftStick().x * 0.001 * 1.0f;
	}
	if ((Pad::GetLeftStick)().y < -1.0f)
	{
		m_vec.z += Pad::GetLeftStick().y * 0.001;
	}
	if ((Pad::GetLeftStick)().y > 1.0f)
	{
		m_vec.z += Pad::GetLeftStick().y * 0.001;
	}

	// �v���C���[�̂������ʒu�ɖ߂�
//	if (Pad::isPress(PAD_INPUT_9))
	if (input.IsTrigger("Debug"))
	{
		m_pos = VGet(0.0f, 0.0f, 0.0f);
	}
	if (!isJumping())
	{
//		if (Pad::isTrigger(PAD_INPUT_1))
		if (input.IsTrigger("jump"))
		{
			m_vec.y = kJumpPower;
		}
	}

	m_pos = VAdd(m_pos, m_vec);

//	MV1SetPosition(m_model, m_pos);
//	MV1SetRotationXYZ(m_model, m_modelRot);
}

void Player::Draw()
{
	// �v���C���[�̃��f����`��
//	MV1DrawModel(m_model);

#ifdef _DEBUG
	// �����蔻��̃f�o�b�N�\��
	DrawSphere3D(GetColPos(), GetColRadius(), 16, 0xff0000, 0xff0000, false);
	DrawSphere3D(VGet(0, 80, 0), 16, 16, 0x00ff00, 0x00ff00, false);
	DrawLine3D(GetColPos(), VGet(0, 80, 0), 0x00ff00);
#endif // _DEBUG
}

VECTOR Player::GetColPos() const
{
	VECTOR result = m_pos;
	result.y += 80.0f;
	return result;
}

float Player::GetColRadius() const
{
	return kColRadius;
}

bool Player::isJumping() const
{
	return (m_pos.y > 0.0f);
}
