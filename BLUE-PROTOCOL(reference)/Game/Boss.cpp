#include "Boss.h"
#include "Player.h"
namespace
{
	constexpr const int CloseFrame = 60 * 2;	// 近距離のフレーム数
	constexpr const int FarFrame = 60 * 2;		// 遠距離のフレーム数
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
	// ボスが攻撃するために必要な距離の条件
	CloseDistance();
	FarDistance();

	// ボスの攻撃


	VECTOR das;
	das = m_pPlayer->GetPos();
	das = VSub(das, m_pos);
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

void Boss::Draw()
{
	// ボスのモデルを描画
	MV1DrawModel(m_model);

	// 当たり判定のデバック表示
#ifdef _DEBUG
	// 近距離のターゲット
	DrawCapsule3D(m_pos, m_pos, Close,16,0xffff00,0xffff00,false);
	// 遠距離のターゲット
	DrawCapsule3D(m_pos, m_pos, Far,16,0xffff00,0xffff00,false);
	printf("近い:%d遠い:%d\n", m_frameCountClose, m_frameCountFar);
	if (m_close && !m_far)
	{
		DrawFormatString(20, 100, 0xffffff, "近距離\n");
	}
	if (m_far && !m_close)
	{
		DrawFormatString(20, 100, 0xffffff, "遠距離\n");
	}
	if (m_close && m_far)
	{
		DrawFormatString(20, 100, 0xff00ff, "両方ついている\n");
	}
	if (!m_close && !m_far)
	{
		DrawFormatString(20, 100, 0xff00ff, "どちらでもない\n");
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
		// 範囲外ではあるがまだ近いフラグが立っている場合
		if (m_close)
		{
			if (m_frameCountClose == CloseFrame)
			{
				// n秒経過したら近いフラグを外す
				m_close = false;
				// 遠いフラグを立てる
				// ここで建てないと近いフラグが立っている状態で遠距離の範囲を超えたときにバグが発生する
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
			// 近いフラグが立っていない場合は遠いフラグを立てる
			m_far = true;
			m_frameCountFar = 0;
		}
		else
		{
			// 近いフラグが立っている場合は遠いフラグを外す
			m_far = false;
			m_frameCountFar = 0;
		}
	}
	else
	{
		// 範囲外ではあるがまだ遠いフラグを立てておく時間
		if (m_far)
		{
			if (m_frameCountFar == FarFrame)
			{
				// n秒経過したら遠いフラグを外す
				m_far = false;
				m_frameCountFar = 0;
				return;
			}
			m_frameCountFar++;
		}
	}
}
