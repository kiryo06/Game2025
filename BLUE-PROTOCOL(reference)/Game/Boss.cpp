#include "Boss.h"
#include "Player.h"
namespace
{
	constexpr	const	int		DrawFormatPos	= 16;						// �����ʒu��ݒ�
	constexpr	const	int		RandMin			=  1;						// �����_�����̍ŏ��l
	constexpr	const	int		RandMax			= 12;						// �����_�����̍ő�l
	constexpr	const	int		CloseFrame		= 60 * 2;					// �ߋ����̃t���[����
	constexpr	const	int		FarFrame		= 60 * 3;					// �������̃t���[����
	constexpr	const	int		TargetFrame		= 60 * 4;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		TActionFrame	= 60 * 2;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		FActionFrame	= 60 * 2;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		CActionFrame	= 60 * 2;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		OnColor			= 0x33ffcc;					// ON�ɂȂ������̐F
	constexpr	const	int		OffColor		= 0xd3d3d3;					// OFF�ɂȂ������̐F
	constexpr	const	int		OkColor			= 0x33ff66;					// OK�ɂȂ������̐F
	constexpr	const	int		NotColor		= 0xff5555;					// NOT�ɂȂ������̐F
	constexpr	const	float	BossRad			= {  1000.0f };				// �{�X�̔��a
	constexpr	const	float	Close			= {  4000.0f };				// �ߋ������ǂ����̔��苗��
	constexpr	const	float	Far				= {  7000.0f };				// ���������ǂ����̔��苗��
	constexpr	const	float	Target			= { 10000.0f };				// �^�[�Q�b�g�ł��鋗��
	constexpr	const	float	MoveUpSpeed		= {	   10.0f };				// �߂Â����x
	constexpr	const	float	MoveDownSpeed	= {     5.0f };				// ����鑬�x
	constexpr	const	VECTOR	BossPos			= { 0.0f, 0.0f, -1000.0f };	// �{�X�̏����ʒu
}

int GetRandom(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

Boss::Boss():
	m_model(-1),
	m_frameCountClose(0),
	m_frameCountFar(0),
	m_frameCountTarget(0),
	m_frameCountTAction(0),
	m_frameCountFAction(0),
	m_frameCountCAction(0),
	m_rad(0.0f),
	m_playerRad(0.0f),
	m_pos(0.0f, 0.0f, 0.0f),
	m_playerPos(0.0f, 0.0f, 0.0f),
	m_close(false),
	m_far(false),
	m_target(false),
	m_moveUp(false),
	m_moveDown(false),
	m_meleeAttack(false),
	m_rangedAttack(false)
{
}

Boss::~Boss()
{
}

void Boss::Init()
{
	m_pos = BossPos;
	m_rad = BossRad;

}

void Boss::Update(Player* m_pPlayer)
{
	// �v���C���[�̈ʒu���󂯎��
	m_playerPos = m_pPlayer->GetPos();
	// �v���C���[�̓����蔻��̔��a���󂯎��
	m_playerRad = m_pPlayer->GetColRadius();
	// �{�X�̈ʒu����v���C���[�̈ʒu�������l������
	float distX = m_pos.x - m_playerPos.x;
	float distY = m_pos.y - m_playerPos.y;
	float distZ = m_pos.z - m_playerPos.z;
	// �{�X�ƃv���C���[�̋��������߂�
	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);
	// �{�X���U�����邽�߂ɕK�v�ȋ����̏���
	CloseDistance(dist);
	FarDistance(dist);
	TargetDistance(dist);

	// �����ɍ��킹�ĉ������邩�𔻒f����
	DecideAction();
	// �{�X�̈ړ�
	MoveBoss(dist);

	// �{�X�̍U��
	MeleeAttack();
	RangedAttack();

	// �{�X�̌����Ă��������ς���
	VECTOR das;
	das = m_pPlayer->GetPos();
	das = VSub(das, m_pos);
	float m_rotY = 0;
	// �Ō�ɓ��͂��ꂽ�l��ύX���Ȃ��߂ɓ��͂��Ȃ��Ƃ��͏������s��Ȃ�
	if (VSize(das) != 0)
	{
		// ���K��
		das = VNorm(das);
		// �A�[�N�^���W�F���g
		m_rotY = atan2(das.z, das.x);
		m_rotY -= DX_PI_F / 2 * 3;	// 90�x����Ă������̕␳
		m_rotY *= -1.0f;
	}

	// �{�X�̈ʒu
	MV1SetPosition(m_model, m_pos);
	// �{�X�̌����Ă������
	MV1SetRotationXYZ(m_model, VGet(0, m_rotY,0));
}

void Boss::Draw()
{
	// �{�X�̃��f����`��
	MV1DrawModel(m_model);

#ifdef _DEBUG
	// �{�X�̓����蔻��
	DrawCapsule3D(m_pos, m_pos, BossRad, 16, 0xffff00, 0xffff00, false);
	// �ߋ����̃^�[�Q�b�g
	DrawCapsule3D(m_pos, m_pos, Close,16,0xffff00,0xffff00,false);
	// �������̃^�[�Q�b�g
	DrawCapsule3D(m_pos, m_pos, Far,16,0xffff00,0xffff00,false);
	// �^�[�Q�b�g�ł���͈�
	DrawCapsule3D(m_pos, m_pos, Target, 16, 0xffff00, 0xffff00, false);
#endif // _DEBUG
}

void Boss::DebugFormatDraw()
{
	printf("�߂�:%d����:%d�^�[�Q�b�g:%d\n", m_frameCountClose, m_frameCountFar, m_frameCountTarget);
	printf("�ړ�:%d\n", m_frameCountTAction);

	int colors[8] = { OffColor, OffColor, OffColor, OffColor, OffColor, OffColor, OffColor, OffColor };
	if (m_close)							{ colors[1] = OnColor; }
	if (m_far)								{ colors[2] = OnColor; }
	if (m_target)							{ colors[3] = OnColor; }
	if (!m_close && !m_far && !m_target)	{ colors[4] = OnColor; }
	if (m_moveUp)							{ colors[5] = OkColor; }
	if (m_moveDown)							{ colors[6] = OkColor; }
	if (!m_moveUp && !m_moveDown)			{ colors[7] = NotColor; }

	DrawFormatString(DrawFormatPos, DrawFormatPos *  5, colors[0], "BOSS�̏��	\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos *  6, colors[1], "�ߋ����@�@�@\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos *  7, colors[2], "�������@�@�@\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos *  8, colors[3], "�^�[�Q�b�g��\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos *  9, colors[4], "�͈͊O�@�@�@\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos * 10, colors[5], "�ڋߒ��@�@�@\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos * 11, colors[6], "��ޒ��@�@�@\n");
	DrawFormatString(DrawFormatPos, DrawFormatPos * 12, colors[7], "�ړ��s�@�@\n");
}

// ��������(�ߋ������ǂ���)
void Boss::CloseDistance(float closeDist)
{
	if ((closeDist) < (m_playerRad + Close))
	{
		m_close = true;
		m_frameCountClose = 0;
	}
	else
	{
		// �͈͊O�ł͂��邪�܂��߂��t���O�������Ă���ꍇ
		if (m_close)
		{
			if (m_frameCountClose == CloseFrame)
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
	if ((farDist) < (m_playerRad + Far))
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
			if (m_frameCountFar == FarFrame)
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
	if ((targetDist) < (m_playerRad + Target))
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
			if (m_frameCountTarget == TargetFrame)
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
	if (m_close)		// �߂��͈͂ɂ���ꍇ
	{
		// ���b���Ɉ�񏈗���ς���
		if (m_frameCountCAction == CActionFrame)
		{
			m_frameCountCAction = 0;
			// n�b�o�߂�����^�[�Q�b�g�t���O���O��
			// �����_���Œl���擾���邽�߂̂���
			int randValue = GetRandom(RandMin, RandMax);
			if (randValue <= RandMax / 4)					// 1/4�̊m���ŋ߂Â��Ă���
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				return;
			}
			else if (randValue <= RandMax / 4 * 2)			// 1/4�̊m���ŉ�������
			{
				m_moveUp = false;
				m_moveDown = true;
				m_meleeAttack = false;
				return;
			}
			else if (randValue <= RandMax / 4 * 3)			// 1/4�̊m���ŋߋ����U������
			{
				m_moveUp = false;
				m_moveDown = false;
				m_meleeAttack = true;
				return;
			}
			else											// �������Ȃ�
			{
				m_moveUp = false;
				m_moveDown = false;
				m_meleeAttack = false;
				return;
			}
		}
		m_frameCountCAction++;
	}
	else if (m_far)			// �����͈͂ɂ���ꍇ
	{
		// ���b���Ɉ�񏈗���ς���
		if (m_frameCountFAction == FActionFrame)
		{
			// n�b�o�߂�����^�[�Q�b�g�t���O���O��
			// �����_���Œl���擾���邽�߂̂���
			int randValue = GetRandom(RandMin, RandMax);
			if (randValue <= 3)	// 1/2�̊m���ŋ߂Â��Ă���
			{
				m_moveUp = true;
			}
			else				// �������Ȃ�
			{
				m_moveUp = false;
			}
			m_frameCountFAction = 0;
			return;
		}
		m_frameCountFAction++;
	}
	else if (m_target)			// �^�[�Q�b�g�ł���͈͂ɂ���ꍇ
	{
		// ���b���Ɉ�񏈗���ς���
		if (m_frameCountTAction == TActionFrame)
		{
			// n�b�o�߂�����^�[�Q�b�g�t���O���O��
			// �����_���Œl���擾���邽�߂̂���
			int randValue = GetRandom(RandMin, RandMax);
			if (randValue <= 3)	// 1/2�̊m���ŋ߂Â��Ă���
			{
				m_moveUp = true;
			}
			else				// �������Ȃ�
			{
				m_moveUp = false;
			}
			m_frameCountTAction = 0;
			return;
		}
		m_frameCountTAction++;
	}
	else
	{
		m_moveUp = false;
		m_moveDown = false;
		m_meleeAttack = false;
		m_rangedAttack = false;
		m_frameCountTAction = 0;
	}
}

// �ړ�
void Boss::MoveBoss(float MoveDist)
{
	if (m_moveUp)
	{
		if ((MoveDist) < (m_playerRad + BossRad))
		{
			// �v���C���[�Ƃ̋������߂�����ꍇ�͓����Ȃ�
		}
		else
		{
			// �{�X�̈ړ�
			VECTOR direction = VSub(m_playerPos, m_pos);
			direction = VNorm(direction); // ���K��
			m_pos = VAdd(m_pos, VScale(direction, MoveUpSpeed));
		}
	}
	if (m_moveDown)
	{
		// �{�X�̈ړ�
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // ���K��
		m_pos = VAdd(m_pos, VScale(direction, -MoveDownSpeed));
	}
}

// �ߐڍU��
void Boss::MeleeAttack()
{
	// �ߐڍU���̏���
	if (m_meleeAttack)
	{
		//// �ߐڍU���̏������s��
		//m_frameCountClose++;
		//if (m_frameCountClose >= CloseFrame)
		//{
		//	// �U���̏������s��
		//	m_frameCountClose = 0; // �t���[���J�E���g�����Z�b�g
		//	// �U���̏���������
		//	// �Ⴆ�΁A�v���C���[�Ƀ_���[�W��^����Ȃ�
		//}
	}
}

// ���u�U��
void Boss::RangedAttack()
{
	// ���u�U���̏���
	if (m_rangedAttack)
	{
		//// ���u�U���̏������s��
		//m_frameCountFar++;
		//if (m_frameCountFar >= FarFrame)
		//{
		//	// �U���̏������s��
		//	m_frameCountFar = 0; // �t���[���J�E���g�����Z�b�g
		//	// �U���̏���������
		//	// �Ⴆ�΁A�v���C���[�Ƀ_���[�W��^����Ȃ�
		//}
	}
}
