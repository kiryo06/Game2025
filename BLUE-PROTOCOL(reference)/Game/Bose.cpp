#include "Bose.h"
#include "Player.h"
namespace
{
	constexpr const VECTOR BosePos = { 0.0f, 0.0f, -1000.0f };
}

Bose::Bose():
	m_model(-1),
	m_pos(0.0f, 0.0f, 0.0f)
{
}

Bose::~Bose()
{
}

void Bose::Init()
{
	m_pos = BosePos;
}

void Bose::Update(Player* m_pPlayer)
{
	VECTOR das;
	das = m_pPlayer->GetPos();
	das = VSub( das,m_pos);
	float m_rotY = 0;
	// 最後に入力された値を変更しないめに入力がないときは処理を行わない
	if (VSize(das) != 0)
	{
		// 正規化
		das = VNorm(das);
		// アークタンジェント
		m_rotY = atan2(das.z, das.x);
		m_rotY -= DX_PI_F / 2 * 3;	// 90度ずれていた分の補正
		m_rotY *= -1.0f;
	}
	// ボスの位置
	MV1SetPosition(m_model, m_pos);
	// ボスの向いている向き
	MV1SetRotationXYZ(m_model, VGet(0, m_rotY,0));
}

void Bose::Draw()
{
	// ボスのモデルを描画
	MV1DrawModel(m_model);

	// 当たり判定のデバック表示
#ifdef _DEBUG
	DrawCapsule3D(m_pos, m_pos,100,16,0xffff00,0xffff00,false);
#endif // _DEBUG
}
