#include "Player.h"
#include "Pad.h"
#include "Input.h"
#include "Camera.h"

namespace
{
	constexpr float kJumpPower = 16.0f;		// プレイヤーのジャンプ力
	constexpr float kGravity = -0.5f;		// プレイヤーの重力

	constexpr float kMoveAccel = 1.0f;		// プレイヤーの移動加速度
	constexpr float kMoveDecRate = 0.80f;	// プレイヤーの移動減速率

	constexpr int kDefaultHp = 120;			// プレイヤーの初期HP

	constexpr float kColRadius = 100.0f;		// プレイヤーの当たり判定

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
	// ジャンプ処理
	if (!isJumping())
	{
		if (input.IsTrigger("jump"))
		{
			m_vec.y = kJumpPower;
		}
	}
	// プレイヤーの移動
	Move();

#ifdef _DEBUG
	// プレイヤーのを初期位置に戻す
	if (input.IsTrigger("Debug"))
	{
		m_pos = VGet(0.0f, 0.0f, 0.0f);
	}
#endif // _DEBUG

}

void Player::Draw()
{
	// プレイヤーのモデルを描画
	MV1DrawModel(m_model);


#ifdef _DEBUG
	
	DrawFormatString(100, 10, 0x00ffff, "%f", m_getCameraAtan2);
	DrawFormatString(10, 200, 0xff0000, "Vec X:%.3f | Vec Y:%.3f | Vec Z:%.3f", m_vec.x, m_vec.y, m_vec.z);

	// 当たり判定のデバック表示
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
	// 現在向いている向き
	VECTOR dir = VGet(0, 0, 0);

	// 前または後ろならば、
	if (Pad::GetLeftStick().y < -1.0f || Pad::GetLeftStick().y > 1.0f)
	{
		dir.z = Pad::GetLeftStick().y;
	}

	// 左または右ならば、
	if (Pad::GetLeftStick().x < -1.0f || Pad::GetLeftStick().x > 1.0f)
	{
		dir.x = -Pad::GetLeftStick().x;
	}

	// dirに値が入っているなら正規化する
	if (VSize(dir) != 0.0f)
	{
		dir = VNorm(dir);
	}

	// カメラの向いている向きfloatを反転させる
	m_getCameraAtan2 *= -1;

	// カメラの向いている向きを90度補正
	m_getCameraAtan2 += DX_PI_F / 2;

	VECTOR vec;
	vec.x = cosf(m_getCameraAtan2) * dir.x + sinf(m_getCameraAtan2) * dir.z;
	vec.y = dir.y;
	vec.z = -sinf(m_getCameraAtan2) * dir.x + cosf(m_getCameraAtan2) * dir.z;

	vec = VScale(vec, 5.0f);
	m_vec = VAdd(m_vec, vec);


	// プレイヤーの位置に値を
	m_pos = VAdd(m_pos, m_vec);

	// 最後に入力された値を変更しないめに入力がないときは処理を行わない
	if (VSize(vec) != 0)
	{
		// 正規化
		vec = VNorm(vec);
		// アークタンジェント
		m_rotY = atan2(vec.z, vec.x);
		m_rotY -= DX_PI_F /2*3;	// 90度ずれていた分の補正
		m_rotY *= -1.0f;
	}

	// プレイヤーの位置
	MV1SetPosition(m_model, m_pos);
	// プレイヤーの向いている向き
	MV1SetRotationXYZ(m_model, VGet(0, m_rotY, 0));
}

bool Player::isJumping() const
{
	return (m_pos.y > 0.0f);
}
