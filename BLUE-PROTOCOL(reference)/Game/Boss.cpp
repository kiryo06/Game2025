#include "Boss.h"
#include "Player.h"
#include "AttackProcessor.h"
namespace
{
	constexpr	const	int		kDrawFormatPos			= 16;						// �����ʒu��ݒ�
	constexpr	const	int		kRandMin				=  1;						// �����_�����̍ŏ��l
	constexpr	const	int		kRandMax				=  4;						// �����_�����̍ő�l
	constexpr	const	int		kDebugDisplayNum		= 10;						// �f�o�b�N�\��������̐�
	constexpr	const	int		kCloseFrame				= 60 * 2;					// �ߋ����̃t���[����
	constexpr	const	int		kFarFrame				= 60 * 3;					// �������̃t���[����
	constexpr	const	int		kTargetFrame			= 60 * 4;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		kTActionFrame			= 60 * 2;					// �ߋ����̍s���ύX�̃t���[����
	constexpr	const	int		kFActionFrame			= 60 * 2;					// �������̍s���ύX�t���[����
	constexpr	const	int		kCActionFrame			= 60 * 2;					// �^�[�Q�b�g�̍s���ύX�t���[����
	constexpr	const	int		kmeleeAttack			= 60 * 1;					// �ߐڍU�����ɂق��̏������~�߂鎞��
	constexpr	const	int		krangedAttack			= 60 * 1;					// ���u�U�����ɂق��̏������~�߂邽�߂̎���
	constexpr	const	int		kOnColor				= 0x33ffcc;					// ON�ɂȂ������̐F
	constexpr	const	int		kOffColor				= 0xd3d3d3;					// OFF�ɂȂ������̐F
	constexpr	const	int		kOkColor				= 0x33ff66;					// OK�ɂȂ������̐F
	constexpr	const	int		kNotColor				= 0xff5555;					// NOT�ɂȂ������̐F
	constexpr	const	float	kBossRad				= {  1000.0f };				// �{�X�̔��a
	constexpr	const	float	kClose					= {  4000.0f };				// �ߋ������ǂ����̔��苗��
	constexpr	const	float	kFar					= {  7000.0f };				// ���������ǂ����̔��苗��
	constexpr	const	float	kTarget					= { 10000.0f };				// �^�[�Q�b�g�ł��鋗��
	constexpr	const	float	kMoveUpSpeed			= {	   10.0f };				// �߂Â����x
	constexpr	const	float	kMoveDownSpeed			= {     5.0f };				// ����鑬�x
	constexpr	const	float	kMaxSpeedIncrease		= {    15.0f };				// �ő呬�x�𑝂₷�ʂ̍ő�l
	constexpr	const	VECTOR	kBossPos				= { 0.0f, 0.0f, -1000.0f };	// �{�X�̏����ʒu
	constexpr	const	VECTOR	kBossScale				= { 3.0f,3.0f, 3.0f };		// �{�X�̃X�P�[��
}

int GetRandom(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

float CalcDistance(const VECTOR& a, const VECTOR& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

Boss::Boss():
	m_model(-1),
	m_frameCountClose(0),
	m_frameCountFar(0),
	m_frameCountTarget(0),
	m_frameCountTAction(0),
	m_frameCountFAction(0),
	m_frameCountCAction(0),
	m_frameCountAttack(0),
	m_rad(0.0f),
	m_playerRad(0.0f),
	m_hp(0.0f),
	m_currentRotY(0.0f),
	m_targetMoveSpeed(0.0f),
	m_pos(0.0f, 0.0f, 0.0f),
	m_playerPos(0.0f, 0.0f, 0.0f),
	m_close(false),
	m_far(false),
	m_target(false),
	m_moveUp(false),
	m_moveDown(false),
	m_meleeAttack(false),
	m_rangedAttack(false),
	m_attack(false)
{
}

Boss::~Boss()
{
}

void Boss::Init()
{
	m_pos = kBossPos;
	m_rad = kBossRad;

}

void Boss::Update(Player* player)
{
	// �v���C���[�̈ʒu���󂯎��
	m_playerPos = player->GetPos();
	// �v���C���[�̓����蔻��̔��a���󂯎��
	m_playerRad = player->GetColRadius();
	// �{�X�ƃv���C���[�̋��������߂�
	float dist = CalcDistance(m_pos, m_playerPos);
	// �{�X���U�����邽�߂ɕK�v�ȋ����̏���
	CloseDistance(dist);
	FarDistance(dist);
	TargetDistance(dist);

	// �����ɍ��킹�ĉ������邩�𔻒f����
	DecideAction();
	// �{�X�̈ړ�
	Move(dist);

	// �{�X�̍U��
	MeleeAttack();
	RangedAttack();

	// �{�X�̈ʒu
	MV1SetPosition(m_model, m_pos);
	// �{�X�̃X�P�[����ύX
	MV1SetScale(m_model, kBossScale);
	// �{�X�̌����Ă������
	RotationXYZ();
}

void Boss::Draw()
{
	// �{�X�̃��f����`��
	MV1DrawModel(m_model);

#ifdef _DEBUG
	// �{�X�̓����蔻��
	DrawCapsule3D(m_pos, m_pos, kBossRad, 16, 0xffff00, 0xffff00, false);
	// �ߋ����̃^�[�Q�b�g
	DrawCapsule3D(m_pos, m_pos, kClose,16,0xffff00,0xffff00,false);
	// �������̃^�[�Q�b�g
	DrawCapsule3D(m_pos, m_pos, kFar,16,0xffff00,0xffff00,false);
	// �^�[�Q�b�g�ł���͈�
	DrawCapsule3D(m_pos, m_pos, kTarget, 16, 0xffff00, 0xffff00, false);
#endif // _DEBUG
}

void Boss::DebugFormatDraw()
{
	printf("%d\n",m_frameCountAttack);
	float moveSpeed = kMoveUpSpeed + m_targetMoveSpeed;
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 6, 0xffffff, "�߂�:%d", kCloseFrame - m_frameCountClose);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 7, 0xffffff, "����:%d", kFarFrame - m_frameCountFar);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 8, 0xffffff, "�^�[�Q�b�g:%d\n", kTargetFrame - m_frameCountTarget);
	DrawFormatString(kDrawFormatPos * 16, kDrawFormatPos * 6, 0xffffff, "�ߋ����̎��̓����܂�:%d/%d", m_frameCountCAction,kCActionFrame);
	DrawFormatString(kDrawFormatPos * 16, kDrawFormatPos * 7, 0xffffff, "�������̎��̓����܂�:%d/%d", m_frameCountFAction,kFActionFrame);
	DrawFormatString(kDrawFormatPos * 16, kDrawFormatPos * 8, 0xffffff, "�^�[�Q�b�g���̎��̓����܂�:%d/%d", m_frameCountTAction,kTActionFrame);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 10, 0xffffff, "Boss�̐ڋߑ��x:%.2f", moveSpeed);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 11, 0xffffff, "Boss�̌�ޑ��x: %.2f", kMoveDownSpeed);
	// �\��������̐F��������
	int colors[kDebugDisplayNum] = {};
	for (int i = 0; i < kDebugDisplayNum; ++i) colors[i] = kOffColor;

	// �󋵂ɉ����ĐF��ς���
	if (m_close)															{	colors[1] = kOnColor;	}
	if (m_far)																{	colors[2] = kOnColor;	}
	if (m_target)															{	colors[3] = kOnColor;	}
	if (!m_close && !m_far && !m_target)									{	colors[4] = kOnColor;	}
	if (m_moveUp)															{	colors[5] = kOkColor;	}
	if (m_moveDown)															{	colors[6] = kOkColor;	}
	if (m_meleeAttack)														{	colors[7] = kOkColor;	}
	if (m_rangedAttack)														{	colors[8] = kOkColor;	}
	if (!m_moveUp && !m_moveDown && !m_meleeAttack && !m_rangedAttack)		{	colors[9] = kNotColor;	}

	// �\��������̎��
	const char* labels[kDebugDisplayNum] =
	{
		"BOSS�̏��@\n",
		"�ߋ����@�@�@\n",
		"�������@�@�@\n",
		"�^�[�Q�b�g��\n",
		"�͈͊O�@�@�@\n",
		"�ڋߒ��@�@�@\n",
		"��ޒ��@�@�@\n",
		"�ߐڍU�����@\n",
		"���u�U�����@\n",
		"�s���s�@�@\n"
	};

	// �\��������̗ʂ�
	for (int i = 0; i < kDebugDisplayNum; ++i)
	{
		DrawFormatString(kDrawFormatPos, kDrawFormatPos * (5 + i), colors[i], labels[i]);
	}
}

// ��������(�ߋ������ǂ���)
void Boss::CloseDistance(float closeDist)
{
	if ((closeDist) < (m_playerRad + kClose))
	{
		m_close = true;
		m_frameCountClose = 0;
	}
	else
	{
		// �͈͊O�ł͂��邪�܂��߂��t���O�������Ă���ꍇ
		if (m_close)
		{
			if (m_frameCountClose == kCloseFrame)
			{
				// n�b�o�߂�����߂��t���O���O��
				m_close = false;
				// �����t���O�𗧂Ă�
				// �����Ō��ĂȂ��Ƌ߂��t���O�������Ă����Ԃŉ������͈̔͂𒴂����Ƃ��Ƀo�O����������
				m_far = true;
				m_frameCountClose = 0;
				return;
			}
			m_frameCountClose++;
		}
	}
}

// ��������(���������ǂ���)
void Boss::FarDistance(float farDist)
{
	if ((farDist) < (m_playerRad + kFar))
	{
		if (!m_close)
		{
			// �߂��t���O�������Ă��Ȃ��ꍇ�͉����t���O�𗧂Ă�
			m_far = true;
			m_frameCountFar = 0;
		}
		else
		{
			// �߂��t���O�������Ă���ꍇ�͉����t���O���O��
			m_far = false;
			m_frameCountFar = 0;
		}
	}
	else
	{
		// �͈͊O�ł͂��邪�܂������t���O�𗧂ĂĂ�������
		if (m_far)
		{
			if (m_frameCountFar == kFarFrame)
			{
				// n�b�o�߂����牓���t���O���O��
				m_far = false;
				// �^�[�Q�b�g�t���O�𗧂Ă�
				// �����Ō��ĂȂ��Ɖ����t���O�������Ă����ԂŃ^�[�Q�b�g�͈̔͂𒴂����Ƃ��Ƀo�O����������
				m_target = true;
				m_frameCountFar = 0;
				return;
			}
			m_frameCountFar++;
		}
	}
}

// ��������(�^�[�Q�b�g�������ǂ���)
void Boss::TargetDistance(float targetDist)
{
	if ((targetDist) < (m_playerRad + kTarget))
	{
		if (!m_close&&!m_far)
		{
			// �����t���O�������Ă��Ȃ��ꍇ�̓^�[�Q�b�g�t���O�𗧂Ă�
			m_target = true;
			m_frameCountTarget = 0;
		}
		else
		{
			// �����t���O�������Ă���ꍇ�̓^�[�Q�b�g�t���O���O��
			m_target = false;
			m_frameCountTarget = 0;
		}
	}
	else
	{
		// �͈͊O�ł͂��邪�܂��^�[�Q�b�g�t���O�𗧂ĂĂ�������
		if (m_target)
		{
			if (m_frameCountTarget == kTargetFrame)
			{
				// n�b�o�߂�����^�[�Q�b�g�t���O���O��
				m_target = false;
				m_frameCountTarget = 0;
				return;
			}
			m_frameCountTarget++;
		}
	}
}

// �s������
void Boss::DecideAction()
{
	// �ǂ͈̔͂ł��Ȃ��ꍇ�͑���return
	if (!m_close && !m_far && !m_target)
	{
		m_moveUp = false;
		m_moveDown = false;
		m_meleeAttack = false;
		m_rangedAttack = false;
		m_frameCountCAction = kCActionFrame;
		m_frameCountFAction = kFActionFrame;
		m_frameCountTAction = kTActionFrame;
		m_targetMoveSpeed = 0.0f;
		return;
	}
	
	// �߂��͈͂ɂ���ꍇ
	else if (m_close)
	{
		// �o�O�̌����ɂȂ�̂ŏ�����
		m_frameCountFAction = kFActionFrame;
		m_frameCountTAction = kTActionFrame;
		m_targetMoveSpeed = 0.0f;
		// �U�����͑���return�ŏ������~�߂�
		if (m_attack)
		{
			return;
		}
		else
		{
			// ���b���Ɉ�񏈗���ς���
			if (m_frameCountCAction == kCActionFrame)
			{
				// ���������������Ƒ�ςȂ̂�
				m_frameCountCAction = 0;
				// n�b�o�߂�����^�[�Q�b�g�t���O���O��
				// �����_���Œl���擾���邽�߂̂���
				int randValue = GetRandom(kRandMin, kRandMax);
				// 1/4�̊m���ŋ߂Â��Ă���
				if (randValue <= kRandMax / 4)
				{
					m_moveUp = true;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
				// 1/4�̊m���ŉ�������
				else if (randValue <= kRandMax / 4 * 2)
				{
					m_moveUp = false;
					m_moveDown = true;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
				// 1/4�̊m���ŋߋ����U������
				else if (randValue <= kRandMax / 4 * 3)
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = true;
					m_rangedAttack = false;
					return;
				}
				// �������Ȃ�
				else
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
			}
			m_frameCountCAction++;
			return;
		}
	}
	
	// �����͈͂ɂ���ꍇ
	else if (m_far)
	{
		// �o�O�̌����ɂȂ�̂ŏ�����
		m_frameCountCAction = kCActionFrame;
		m_frameCountTAction = kTActionFrame;
		m_targetMoveSpeed = 0.0f;
		// �U�����͑���return�ŏ������~�߂�
		if (m_attack)
		{
			return;
		}
		else
		{
			// ���b���Ɉ�񏈗���ς���
			if (m_frameCountFAction == kFActionFrame)
			{
				// ���������������Ƒ�ςȂ̂�
				m_frameCountFAction = 0;
				// n�b�o�߂�����^�[�Q�b�g�t���O���O��
				// �����_���Œl���擾���邽�߂̂���
				int randValue = GetRandom(kRandMin, kRandMax);
				// 1/4�̊m���ŋ߂Â��Ă���
				if (randValue <= kRandMax / 4)
				{
					m_moveUp = true;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
				// 1/4�̊m���ŉ��u�U��
				else if (randValue <= kRandMax / 4 * 2)
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = true;
					return;
				}
				// 1/4�̊m���ŉ��u�U��(��)
				else if (randValue <= kRandMax / 4 * 3)
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = true;
					return;
				}
				// �������Ȃ�
				else
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
			}
			m_frameCountFAction++;
			return;
		}
	}
	
	// �^�[�Q�b�g�ł���͈͂ɂ���ꍇ
	else if (m_target)
	{
		// �o�O�̌����ɂȂ�̂ŏ�����
		m_frameCountFAction = kCActionFrame;
		m_frameCountCAction = kFActionFrame;
		// ���b���Ɉ�񏈗���ς���
		if (m_frameCountTAction == kTActionFrame)
		{
			// ���������������Ƒ�ςȂ̂�
			m_frameCountTAction = 0;
			// n�b�o�߂�����^�[�Q�b�g�t���O���O��
			// �����_���Œl���擾���邽�߂̂���
			int randValue = GetRandom(kRandMin, kRandMax);
			// 1/4�̊m���ŋ߂Â��Ă���(����)
			if (randValue <= kRandMax / 4)
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease / 5;
				return;
			}
			// 1/4�̊m���ŋ߂Â��Ă���(������Ƒ���)
			else if (randValue <= kRandMax / 4 * 2)
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease / 3;
				return;
			}
			// 1/4�̊m���ŋ߂Â��Ă���(����)
			else if (randValue <= kRandMax / 4 * 3)
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease / 2;
				return;
			}
			// 1/4�̊m���ŋ߂Â��Ă���(���̂���������)
			else
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease;
				return;
			}
			return;
		}
		m_frameCountTAction++;
		return;
	}
}

void Boss::SetAttackProcessor(AttackProcessor* processor)
{
	m_attackProcessor = processor;
}

void Boss::SetTargetPlayer(Player* player)
{
	m_targetPlayer = player;
}

// �ړ�
void Boss::Move(float MoveDist)
{
	if (m_moveUp && m_moveDown)return;

	if (m_moveUp)
	{
		if ((MoveDist) < (m_playerRad + kBossRad))
		{
			// �v���C���[�Ƃ̋������߂�����ꍇ�͓����Ȃ�
			return;
		}
		else
		{
			// �{�X�̈ړ�
			VECTOR direction = VSub(m_playerPos, m_pos);
			direction = VNorm(direction); // ���K��
			m_pos = VAdd(m_pos, VScale(direction, kMoveUpSpeed + m_targetMoveSpeed));
		}
	}
	if (m_moveDown)
	{
		// �{�X�̈ړ�
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // ���K��
		m_pos = VAdd(m_pos, VScale(direction, -kMoveDownSpeed));
	}
}

// �ߐڍU��
void Boss::MeleeAttack()
{
	// �ߐڍU���̏���
	if (m_meleeAttack)
	{
		// �U�����̃t���O�𗧂Ă�
		m_attack = true;
		// ���݂̃t���[��(�U������)���v��
		m_frameCountAttack++;
		// ���݂̍U�����Ԃ��ݒ莞�Ԃƈꏏ�ɂȂ������U������߂邽�߂̂���
		if (m_frameCountAttack == kmeleeAttack)
		{
			m_meleeAttack = false;
			m_attack = false;
			m_frameCountAttack = 0;
			return;
		}
		if (m_attack)
		{
			// �U���̏���
			//VECTOR end = MV1GetPosition(m_model);
			m_attackProcessor->ProcessBossAttack(this, m_targetPlayer, Melee);
		}
	}
}

// ���u�U��
void Boss::RangedAttack()
{
	// ���u�U���̏���
	if (m_rangedAttack)
	{
		// �U�����̃t���O�𗧂Ă�
		m_attack = true;
		// ���݂̃t���[��(�U������)���v��
		m_frameCountAttack++;
		// ���݂̍U�����Ԃ��ݒ莞�Ԃƈꏏ�ɂȂ������U������߂邽�߂̂���
		if (m_frameCountAttack == krangedAttack)
		{
			m_rangedAttack = false;
			m_attack = false;
			m_frameCountAttack = 0;
			return;
		}
		if (m_attack && m_attackProcessor)
		{
			// �U���̏���
			m_attackProcessor->ProcessBossAttack(this, m_targetPlayer, Ranged);
		}
	}
}

void Boss::RotationXYZ()
{
	// �{�X�̌����Ă��������ς���
	VECTOR das = VSub(m_playerPos, m_pos);
	// �ڕW��Y��]�p(���W�A��)
	float targetRotY = 0;
	// �Ō�ɓ��͂��ꂽ�l��ύX���Ȃ��߂ɓ��͂��Ȃ��Ƃ��͏������s��Ȃ�
	if (VSize(das) != 0)
	{
		// ���K��
		das = VNorm(das);
		// �A�[�N�^���W�F���g
		targetRotY = atan2(das.z, das.x);

		// ���f���̏��������̕␳(���f���ɂ���Ē������K�v)
		targetRotY -= DX_PI_F / 2 * 3;	// 90�x����Ă������̕␳
		targetRotY *= -1.0f;
	}

	// Lerp�̕�ԌW���i0.0�`1.0�A�������قǂ�������]�j
	float t = 0.1f;

	// �p�x�␳(�␳����ɂ́u�p�x�̍��v�𒲐�)
	float angleDiff = targetRotY - m_currentRotY;

	// �p�x�� -�� �` �� �͈̔͂ɕ␳
	while (angleDiff > DX_PI_F)		{ angleDiff -= DX_PI_F * 2; }
	while (angleDiff < -DX_PI_F)	{ angleDiff += DX_PI_F * 2; }

	// �p�x�����𒴂��Ă����琧���l�ɃN���b�v
	if (angleDiff > DX_PI_F / 3.0f)       angleDiff = DX_PI_F / 3.0f;
	else if (angleDiff < -DX_PI_F / 3.0f) angleDiff = -DX_PI_F / 3.0f;

	// �X���[�Y�ɉ�]������
	m_currentRotY += angleDiff * t;

	// ��]��ݒ�
	MV1SetRotationXYZ(m_model, VGet(0, m_currentRotY, 0));
}

//|**���t**| ��Ɠ��e														| �ړI								|		// ��
//|**11��**| �v���C���[�L�����N�^�[�̃��f���\�� & ��{�ړ��i�O�㍶�E		| �v���C���[����̊�{����			|		// ���f����������
//|**12��**| �v���C���[�̃A�j���[�V���� / �J�����Ƃ̘A�g					| �\���̃��A���e�B�����߂�			|		// �A�j���[�V������������
//|**13��**| �X�e�[�W�̃��f���ǂݍ��� / �����蔻��̃x�[�X�\�z				| �X�e�[�W��T���ł�����Â���	|		// 
//|**14��**| �v���C���[�ƃX�e�[�W�̏Փ˔������								| ���蔲���Ȃ��悤�ɂ���			|		// 
//|**15��**| �{�X�Ƃ̓����蔻��i�ڐG���_���[�W�j							| ��{�I�ȓG�Ƃ̂����			|		// 
//|**16��**| �v���C���[�̍U���i�ߐ� or �������j & �q�b�g����				| �U�����ł���悤�ɂ���			|		// 
//|**17��**| �{�X�̍U���p�^�[���i�P����OK�j & �q�b�g����					| �G���U�����Ă���悤��			|		// 
//|**18��**| HP�V�X�e���i�v���C���[�E�{�X�j & ���s�����̎���				| �킢�̖ړI�����m��				|		// 
//|**19��**| HP�o�[�ȂǊȒP��UI�\��											| ��Ԃ��킩��悤�ɂ���			|		// 
//|**20��**| �Q�[���̏�ԊǗ��i�^�C�g�� �� �Q�[�� �� �I���j					| �Q�[���̗�������				|		// 
//|**21��**| �e�X�g�E�o�O�C���i1��ځj										| �v���C�\�ȏ�Ԃɒ���			|		// 
//|**22��**| �Ȉ�BGM�ESE�i���\�[�X������΁j								| �Տꊴ�A�b�v						|		// �Ȃ�
//|**23��**| �G�t�F�N�g�ǉ��i�q�b�g�┚���Ȃǁj								| ���o�𐮂���						|		// �Ȃ�
//|**24��**| �ŏI���� & �ʂ��v���C�e�X�g									| �f���Ƃ��Ċ���������				|		// �Ȃ�
