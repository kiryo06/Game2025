#include "Boss.h"
#include "Player.h"
namespace
{
	constexpr const int CloseFrame = 60 * 2;	// �ߋ����̃t���[����
	constexpr const int FarFrame = 60 * 2;		// �������̃t���[����
	constexpr const float BossRad  = { 1000.0f};
	constexpr const float Close = {8000.0f};
	constexpr const float Far = {10000.0f};
	constexpr const VECTOR BossPos = { 0.0f, 0.0f, -1000.0f };
}

Boss::Boss():
	m_model(-1),
	m_frameCountClose(0),
	m_frameCountFar(0),
	m_rad(0.0f),
	m_pos(0.0f, 0.0f, 0.0f),
	m_close(false),
	m_far(false),
	m_playerRad(0.0f),
	m_playerPos(0.0f,0.0f,0.0f)
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
	m_playerPos = m_pPlayer->GetPos();
	m_playerRad = m_pPlayer->GetColRadius();
	// �{�X���U�����邽�߂ɕK�v�ȋ����̏���
	CloseDistance();
	FarDistance();

	// �{�X�̍U��


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

	// �����蔻��̃f�o�b�N�\��
#ifdef _DEBUG
	// �ߋ����̃^�[�Q�b�g
	DrawCapsule3D(m_pos, m_pos, Close,16,0xffff00,0xffff00,false);
	// �������̃^�[�Q�b�g
	DrawCapsule3D(m_pos, m_pos, Far,16,0xffff00,0xffff00,false);
	printf("�߂�:%d����:%d\n", m_frameCountClose, m_frameCountFar);
	if (m_close && !m_far)
	{
		DrawFormatString(20, 100, 0xffffff, "�ߋ���\n");
	}
	if (m_far && !m_close)
	{
		DrawFormatString(20, 100, 0xffffff, "������\n");
	}
	if (m_close && m_far)
	{
		DrawFormatString(20, 100, 0xff00ff, "�������Ă���\n");
	}
	if (!m_close && !m_far)
	{
		DrawFormatString(20, 100, 0xff00ff, "�ǂ���ł��Ȃ�\n");
	}

#endif // _DEBUG
}

void Boss::CloseDistance()
{
	float distX = m_pos.x - m_playerPos.x;
	float distY = m_pos.y - m_playerPos.y;
	float distZ = m_pos.z - m_playerPos.z;

	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);
	if ((dist) < (m_playerRad + Close))
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

void Boss::FarDistance()
{
	float distX = m_pos.x - m_playerPos.x;
	float distY = m_pos.y - m_playerPos.y;
	float distZ = m_pos.z - m_playerPos.z;

	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);
	if ((dist) < (m_playerRad + Far))
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
				m_frameCountFar = 0;
				return;
			}
			m_frameCountFar++;
		}
	}
}
