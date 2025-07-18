#include "Player.h"
#include "Pad.h"
#include "Input.h"
#include "Camera.h"
#include "AttackProcessor.h"

namespace
{
	// 物理移動関連
	constexpr	const	float	kJumpPower				=	16.0f;			// プレイヤーのジャンプ力
	constexpr	const	float	kGravity				=	-0.5f;			// プレイヤーの重力
	constexpr	const	float	kMoveAccel				=	1.0f;			// プレイヤーの移動加速度
	constexpr	const	float	kMoveDecRate			=	0.80f;			// プレイヤーの移動減速率

	// コントローラについての設定
	constexpr	const	float	kDeadZone				=	0.1f;			// デットゾーンを決める

	// キャラクターのステータス
	constexpr	const	float	kDefaultHp				=	100.0f;			// プレイヤーの初期HP
	// 当たり判定関連
	constexpr	const	float	kCollisionRadius		=	100.0f;			// プレイヤーの当たり判定の半径
	constexpr	const	float	kCollisionHeightOffset	=	80.0f;			// 当たり判定の中心Y座標
	// 地面の高さ(仮)
	constexpr	const	float	kGroundHeight			=	0.0f;
}

Player::Player() :
	m_model(-1),
	m_rotY(0.0f),
	m_getCameraAtan2(0.0f),
	m_hp(0.0f),
	m_attack(0.0f),
	m_pos(0.0f, 0.0f, 0.0f),
	m_vec(0.0f, 0.0f, 0.0f),
	m_state(JumpState::Idle)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_hp = kDefaultHp;
}

void Player::Update(Input& input, Camera *camera)
{
	// カメラの向きを取得
	m_getCameraAtan2 = camera->GetAtan2();
	HandleInput(input);
	switch (m_state)
	{
	case JumpState::Idle:
		// 入力が入ったらジャンプ処理に移行
		if (input.IsTrigger("Aボタン"))
		{
			Jump();
		}
		break;
	case JumpState::Junmping:
		// 頂点に到達したら落下状態に移行
		if (m_vec.y <= 0.0f)
		{
			m_state = JumpState::Falling;
		}
		m_vec.y = kJumpPower;
		break;
	case JumpState::Falling:
		// 地面に着地したら待機状態に移行
		if (m_pos.y <= kGroundHeight)
		{
			m_pos.y = kGroundHeight;
			m_vec.y = 0.0f;
			m_state = JumpState::Idle;
		}
		break;
	}
	// 前のフレームからの経過時間を表す値
	float deltaTime = 0.0f;

	// 物理演算の更新
	Gravity(deltaTime);
	Movement(deltaTime);
	UpdateTransform();

#ifdef _DEBUG
	// プレイヤーのを初期位置に戻す
	if (input.IsTrigger("左スティック押しこみ"))
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

	DrawFormatString(10, 0, 0xff0000, "HP: %.1f", m_hp);
	DrawFormatString(10, 20, 0x00ffff, "State: %d",static_cast<int>(m_state));
	DrawSphere3D(GetColPos(), GetColRadius(), 16,0xff0000, 0xff0000, false);
	
	
//	DrawFormatString(100, 10, 0x00ffff, "%f", m_getCameraAtan2);
//	DrawFormatString(10, 200, 0xff0000, "Vec X:%.3f | Vec Y:%.3f | Vec Z:%.3f", m_vec.x, m_vec.y, m_vec.z);
	// 当たり判定のデバック表示
//	DrawSphere3D(GetColPos(), GetColRadius(), 16, 0xff0000, 0xff0000, false);
//	DrawSphere3D(VGet(0, 80, 0), 16, 16, 0x00ff00, 0x00ff00, false);
//	DrawLine3D(GetColPos(), VGet(0, 80, 0), 0x00ff00);
#endif // _DEBUG
}

VECTOR Player::GetColPos() const
{
	VECTOR result = m_pos;
	result.y += kCollisionHeightOffset;
	return result;
}

float Player::GetColRadius() const
{
	return kCollisionRadius;
}

void Player::HandleInput(Input& input)
{
	// 移動入力から方向ベクトルを計算するため
	VECTOR dir = VGet(0, 0, 0);

	// 前後移動処理		「fabs」は絶対値
	if (fabs(Pad::GetLeftStick().y) > kDeadZone)
	{
		dir.z = Pad::GetLeftStick().y;
	}

	// 左右移動処理		「fabs」は絶対値
	if (fabs(Pad::GetLeftStick().x) > kDeadZone)
	{
		dir.x = -Pad::GetLeftStick().x;
	}

	// dirに値が入っているなら正規化する
	if (VSize(dir) != 0.0f)
	{
		dir = VNorm(dir);
	}

	// カメラの向いている向きfloatを反転させる
	float cameraAngle = m_getCameraAtan2 *= -1;

	// カメラの向いている向きを90度補正
	cameraAngle =cameraAngle + DX_PI_F / 2.0f;

	VECTOR vec;
	vec.x = cosf(cameraAngle) * dir.x + sinf(cameraAngle) * dir.z;
	vec.y = dir.y;
	vec.z = -sinf(cameraAngle) * dir.x + cosf(cameraAngle) * dir.z;

	// 速度を加算
	m_vec = VAdd(m_vec, VScale(vec,kMoveAccel));
	
	// プレイヤーの向きを更新
	if (VSize(vec) > 0.0f)
	{
		m_rotY = atan2(vec.z, vec.x) - (DX_PI_F / 2.0f * 3.0f);
		m_rotY *= -1.0f;
	}
}

void Player::Jump()
{
	m_vec.y = kJumpPower;
	m_state = JumpState::Junmping;
}

void Player::Gravity(float deltaTime)
{
	if (m_state == JumpState::Junmping || m_state == JumpState::Falling)
	{
		m_vec.y += kGravity * deltaTime;
	}
}

void Player::Movement(float deltaTime)
{
	// 水平方向の速度減衰
	m_vec.x *= kMoveDecRate;
	m_vec.z *= kMoveDecRate;

	// 座標を更新
	m_pos = VAdd(m_pos, VScale(m_vec, deltaTime));
}

void Player::UpdateTransform()
{
	// モデルに座標と回転を適用
	MV1SetPosition(m_model, m_pos);
	MV1SetRotationXYZ(m_model, VGet(0, m_rotY, 0));
}