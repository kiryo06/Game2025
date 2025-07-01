#include "Player.h"
#include "Pad.h"
#include "Input.h"
#include "Camera.h"

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
	m_pos(0.0f, 20.2f, 0.0f),
	m_vec(0.0f, 0.0f, 0.0f),
	m_rotY(0.0f),
	m_hp(kDefaultHp),
	m_getCameraAtan2(0.0f)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update(Input& input, Camera *camera)
{
	m_getCameraAtan2 = camera->GetAtan2();
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
	// �W�����v����
	if (!isJumping())
	{
		if (input.IsTrigger("jump"))
		{
			m_vec.y = kJumpPower;
		}
	}
	// �v���C���[�̈ړ�
	Move();

#ifdef _DEBUG
	// �v���C���[�̂������ʒu�ɖ߂�
	if (input.IsTrigger("Debug"))
	{
		m_pos = VGet(0.0f, 0.0f, 0.0f);
	}
#endif // _DEBUG

}

void Player::Draw()
{
	// �v���C���[�̃��f����`��
	MV1DrawModel(m_model);


#ifdef _DEBUG
	
	DrawFormatString(100, 10, 0x00ffff, "%f", m_getCameraAtan2);
	DrawFormatString(10, 200, 0xff0000, "Vec X:%.3f | Vec Y:%.3f | Vec Z:%.3f", m_vec.x, m_vec.y, m_vec.z);

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

void Player::Move()
{
	// ���݌����Ă������
	VECTOR dir = VGet(0, 0, 0);

	// �O�܂��͌��Ȃ�΁A
	if (Pad::GetLeftStick().y < -1.0f || Pad::GetLeftStick().y > 1.0f)
	{
		dir.z = Pad::GetLeftStick().y;
	}

	// ���܂��͉E�Ȃ�΁A
	if (Pad::GetLeftStick().x < -1.0f || Pad::GetLeftStick().x > 1.0f)
	{
		dir.x = -Pad::GetLeftStick().x;
	}

	// dir�ɒl�������Ă���Ȃ琳�K������
	if (VSize(dir) != 0.0f)
	{
		dir = VNorm(dir);
	}

	// �J�����̌����Ă������float�𔽓]������
	m_getCameraAtan2 *= -1;

	// �J�����̌����Ă��������90�x�␳
	m_getCameraAtan2 += DX_PI_F / 2;

	VECTOR vec;
	vec.x = cosf(m_getCameraAtan2) * dir.x + sinf(m_getCameraAtan2) * dir.z;
	vec.y = dir.y;
	vec.z = -sinf(m_getCameraAtan2) * dir.x + cosf(m_getCameraAtan2) * dir.z;

	vec = VScale(vec, 5.0f);
	m_vec = VAdd(m_vec, vec);


	// �v���C���[�̈ʒu�ɒl��
	m_pos = VAdd(m_pos, m_vec);

	// �Ō�ɓ��͂��ꂽ�l��ύX���Ȃ��߂ɓ��͂��Ȃ��Ƃ��͏������s��Ȃ�
	if (VSize(vec) != 0)
	{
		// ���K��
		vec = VNorm(vec);
		// �A�[�N�^���W�F���g
		m_rotY = atan2(vec.z, vec.x);
		m_rotY -= DX_PI_F /2*3;	// 90�x����Ă������̕␳
		m_rotY *= -1.0f;
	}

	// �v���C���[�̈ʒu
	MV1SetPosition(m_model, m_pos);
	// �v���C���[�̌����Ă������
	MV1SetRotationXYZ(m_model, VGet(0, m_rotY, 0));
}

bool Player::isJumping() const
{
	return (m_pos.y > 0.0f);
}
