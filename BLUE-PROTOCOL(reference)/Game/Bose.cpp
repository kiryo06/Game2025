#include "Bose.h"
#include "Player.h"
namespace
{
	constexpr const VECTOR BosePos = { 0.0f, 0.0f, -1000.0f };
	constexpr const float BoseRad  = { 1000.0f};
}

Bose::Bose():
	m_model(-1),
	m_rad(200.0f),
	m_pos(0.0f, 0.0f, 0.0f),
	m_playerRad(0.0f),
	m_playerPos(0.0f,0.0f,0.0f)
{
}

Bose::~Bose()
{
}

void Bose::Init()
{
	m_pos = BosePos;
	m_rad = BoseRad;

}

void Bose::Update(Player* m_pPlayer)
{
	m_playerPos = m_pPlayer->GetPos();
	m_playerRad = m_pPlayer->GetColRadius();

	float distX = m_pos.x - m_playerPos.x;
	float distY = m_pos.y - m_playerPos.y;
	float distZ = m_pos.z - m_playerPos.z;

	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);
	if ((dist) < (m_playerRad + m_rad))
	{

	}
	else
	{
		printfDx("--\n");
	}
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

void Bose::Draw()
{
	// �{�X�̃��f����`��
	MV1DrawModel(m_model);

	// �����蔻��̃f�o�b�N�\��
#ifdef _DEBUG
	DrawCapsule3D(m_pos, m_pos, m_rad,8,0xffff00,0xffff00,false);
	DrawCapsule3D(m_playerPos, m_playerPos, m_playerRad, 8, 0xffffff, 0xffffff, false);
#endif // _DEBUG
}

void Bose::CloseDistance()
{
}

void Bose::FarDistance()
{
}
