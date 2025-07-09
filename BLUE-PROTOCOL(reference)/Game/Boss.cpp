#include "Boss.h"
#include "Player.h"
namespace
{
	constexpr	const	int		CloseFrame		= 60 * 2;					// �ߋ����̃t���[����
	constexpr	const	int		FarFrame		= 60 * 3;					// �������̃t���[����
	constexpr	const	int		TargetFrame		= 60 * 4;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		TActionFrame	= 60 * 2;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		FActionFrame	= 60 * 2;					// �^�[�Q�b�g�̃t���[����
	constexpr	const	int		CActionFrame	= 60 * 2;					// �^�[�Q�b�g�̃t���[����
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
	MoveBoss();

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

	printf("�߂�:%d����:%d�^�[�Q�b�g:%d\n", m_frameCountClose, m_frameCountFar,m_frameCountTarget);
	printf("�ړ�:%d\n", m_frameCountTAction);
	if (m_close)
	{
		DrawFormatString(20, 150, 0xffffff, "�ߋ���\n");
	}
	if (m_far)
	{
		DrawFormatString(20, 166, 0xffffff, "������\n");
	}
	if (m_target)
	{
		DrawFormatString(20, 182, 0x00ff00, "�^�[�Q�b�g��\n");
	}
	if(!m_close && !m_far && !m_target)
	{
		DrawFormatString(20, 198, 0xff0000, "�͈͊O\n");
	}

	if (m_moveUp|| m_moveDown)
	{
		DrawFormatString(20, 204, 0x00ff00, "�ړ���\n");
	}

	if (!m_moveUp && !m_moveDown)
	{
		DrawFormatString(20, 204, 0x00ff00, "�ړ��s��\n");
	}
#endif // _DEBUG
}

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

void Boss::DecideAction()
{
	if (m_close)		// �߂��͈͂ɂ���ꍇ
	{
		// ���b���Ɉ�񏈗���ς���
		if (m_frameCountCAction == CActionFrame)
		{
			// n�b�o�߂�����^�[�Q�b�g�t���O���O��
			// �����_���Œl���擾���邽�߂̂���
			int randValue = GetRandom(1, 6);
			if (randValue <= 3)	// 1/2�̊m���ŋ߂Â��Ă���
			{
				m_moveUp = true;
			}
			else				// �������Ȃ�
			{
				m_moveUp = false;
			}
			m_frameCountCAction = 0;
			return;
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
			int randValue = GetRandom(1, 6);
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
			int randValue = GetRandom(1, 6);
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
	}
}

void Boss::MoveBoss()
{
	if (m_moveUp)
	{
		// �{�X�̈ړ�
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // ���K��
		m_pos = VAdd(m_pos, VScale(direction, MoveUpSpeed));
	}
	if (m_moveDown)
	{
		// �{�X�̈ړ�
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // ���K��
		m_pos = VAdd(m_pos, VScale(direction, -MoveDownSpeed));
	}
}

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
