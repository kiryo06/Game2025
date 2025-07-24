#include "Boss.h"
#include "Player.h"
#include "AttackProcessor.h"
namespace
{
	constexpr	const	int		kDrawFormatPos			= 16;						// 初期位置を設定
	constexpr	const	int		kRandMin				=  1;						// ランダム数の最小値
	constexpr	const	int		kRandMax				=  4;						// ランダム数の最大値
	constexpr	const	int		kDebugDisplayNum		= 10;						// デバック表示する情報の数
	constexpr	const	int		kCloseFrame				= 60 * 2;					// 近距離のフレーム数
	constexpr	const	int		kFarFrame				= 60 * 3;					// 遠距離のフレーム数
	constexpr	const	int		kTargetFrame			= 60 * 4;					// ターゲットのフレーム数
	constexpr	const	int		kTActionFrame			= 60 * 2;					// 近距離の行動変更のフレーム数
	constexpr	const	int		kFActionFrame			= 60 * 2;					// 遠距離の行動変更フレーム数
	constexpr	const	int		kCActionFrame			= 60 * 2;					// ターゲットの行動変更フレーム数
	constexpr	const	int		kmeleeAttack			= 60 * 1;					// 近接攻撃時にほかの処理を止める時間
	constexpr	const	int		krangedAttack			= 60 * 1;					// 遠隔攻撃時にほかの処理を止めるための時間
	constexpr	const	int		kOnColor				= 0x33ffcc;					// ONになった時の色
	constexpr	const	int		kOffColor				= 0xd3d3d3;					// OFFになった時の色
	constexpr	const	int		kOkColor				= 0x33ff66;					// OKになった時の色
	constexpr	const	int		kNotColor				= 0xff5555;					// NOTになった時の色
	constexpr	const	float	kBossRad				= {  1000.0f };				// ボスの半径
	constexpr	const	float	kClose					= {  4000.0f };				// 近距離かどうかの判定距離
	constexpr	const	float	kFar					= {  7000.0f };				// 遠距離かどうかの判定距離
	constexpr	const	float	kTarget					= { 10000.0f };				// ターゲットできる距離
	constexpr	const	float	kMoveUpSpeed			= {	   10.0f };				// 近づく速度
	constexpr	const	float	kMoveDownSpeed			= {     5.0f };				// 離れる速度
	constexpr	const	float	kMaxSpeedIncrease		= {    15.0f };				// 最大速度を増やす量の最大値
	constexpr	const	VECTOR	kBossPos				= { 0.0f, 0.0f, -1000.0f };	// ボスの初期位置
	constexpr	const	VECTOR	kBossScale				= { 3.0f,3.0f, 3.0f };		// ボスのスケール
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
	// プレイヤーの位置を受け取る
	m_playerPos = player->GetPos();
	// プレイヤーの当たり判定の半径を受け取る
	m_playerRad = player->GetColRadius();
	// ボスとプレイヤーの距離を求める
	float dist = CalcDistance(m_pos, m_playerPos);
	// ボスが攻撃するために必要な距離の条件
	CloseDistance(dist);
	FarDistance(dist);
	TargetDistance(dist);

	// 距離に合わせて何をするかを判断する
	DecideAction();
	// ボスの移動
	Move(dist);

	// ボスの攻撃
	MeleeAttack();
	RangedAttack();

	// ボスの位置
	MV1SetPosition(m_model, m_pos);
	// ボスのスケールを変更
	MV1SetScale(m_model, kBossScale);
	// ボスの向いている向き
	RotationXYZ();
}

void Boss::Draw()
{
	// ボスのモデルを描画
	MV1DrawModel(m_model);

#ifdef _DEBUG
	// ボスの当たり判定
	DrawCapsule3D(m_pos, m_pos, kBossRad, 16, 0xffff00, 0xffff00, false);
	// 近距離のターゲット
	DrawCapsule3D(m_pos, m_pos, kClose,16,0xffff00,0xffff00,false);
	// 遠距離のターゲット
	DrawCapsule3D(m_pos, m_pos, kFar,16,0xffff00,0xffff00,false);
	// ターゲットできる範囲
	DrawCapsule3D(m_pos, m_pos, kTarget, 16, 0xffff00, 0xffff00, false);
#endif // _DEBUG
}

void Boss::DebugFormatDraw()
{
	printf("%d\n",m_frameCountAttack);
	float moveSpeed = kMoveUpSpeed + m_targetMoveSpeed;
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 6, 0xffffff, "近い:%d", kCloseFrame - m_frameCountClose);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 7, 0xffffff, "遠い:%d", kFarFrame - m_frameCountFar);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 8, 0xffffff, "ターゲット:%d\n", kTargetFrame - m_frameCountTarget);
	DrawFormatString(kDrawFormatPos * 16, kDrawFormatPos * 6, 0xffffff, "近距離の次の動きまで:%d/%d", m_frameCountCAction,kCActionFrame);
	DrawFormatString(kDrawFormatPos * 16, kDrawFormatPos * 7, 0xffffff, "遠距離の次の動きまで:%d/%d", m_frameCountFAction,kFActionFrame);
	DrawFormatString(kDrawFormatPos * 16, kDrawFormatPos * 8, 0xffffff, "ターゲット時の次の動きまで:%d/%d", m_frameCountTAction,kTActionFrame);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 10, 0xffffff, "Bossの接近速度:%.2f", moveSpeed);
	DrawFormatString(kDrawFormatPos * 8, kDrawFormatPos * 11, 0xffffff, "Bossの後退速度: %.2f", kMoveDownSpeed);
	// 表示する情報の色を初期化
	int colors[kDebugDisplayNum] = {};
	for (int i = 0; i < kDebugDisplayNum; ++i) colors[i] = kOffColor;

	// 状況に応じて色を変える
	if (m_close)															{	colors[1] = kOnColor;	}
	if (m_far)																{	colors[2] = kOnColor;	}
	if (m_target)															{	colors[3] = kOnColor;	}
	if (!m_close && !m_far && !m_target)									{	colors[4] = kOnColor;	}
	if (m_moveUp)															{	colors[5] = kOkColor;	}
	if (m_moveDown)															{	colors[6] = kOkColor;	}
	if (m_meleeAttack)														{	colors[7] = kOkColor;	}
	if (m_rangedAttack)														{	colors[8] = kOkColor;	}
	if (!m_moveUp && !m_moveDown && !m_meleeAttack && !m_rangedAttack)		{	colors[9] = kNotColor;	}

	// 表示する情報の種類
	const char* labels[kDebugDisplayNum] =
	{
		"BOSSの情報　\n",
		"近距離　　　\n",
		"遠距離　　　\n",
		"ターゲット中\n",
		"範囲外　　　\n",
		"接近中　　　\n",
		"後退中　　　\n",
		"近接攻撃中　\n",
		"遠隔攻撃中　\n",
		"行動不可　　\n"
	};

	// 表示する情報の量を
	for (int i = 0; i < kDebugDisplayNum; ++i)
	{
		DrawFormatString(kDrawFormatPos, kDrawFormatPos * (5 + i), colors[i], labels[i]);
	}
}

// 距離判定(近距離かどうか)
void Boss::CloseDistance(float closeDist)
{
	if ((closeDist) < (m_playerRad + kClose))
	{
		m_close = true;
		m_frameCountClose = 0;
	}
	else
	{
		// 範囲外ではあるがまだ近いフラグが立っている場合
		if (m_close)
		{
			if (m_frameCountClose == kCloseFrame)
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

// 距離判定(遠距離かどうか)
void Boss::FarDistance(float farDist)
{
	if ((farDist) < (m_playerRad + kFar))
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
			if (m_frameCountFar == kFarFrame)
			{
				// n秒経過したら遠いフラグを外す
				m_far = false;
				// ターゲットフラグを立てる
				// ここで建てないと遠いフラグが立っている状態でターゲットの範囲を超えたときにバグが発生する
				m_target = true;
				m_frameCountFar = 0;
				return;
			}
			m_frameCountFar++;
		}
	}
}

// 距離判定(ターゲット距離かどうか)
void Boss::TargetDistance(float targetDist)
{
	if ((targetDist) < (m_playerRad + kTarget))
	{
		if (!m_close&&!m_far)
		{
			// 遠いフラグが立っていない場合はターゲットフラグを立てる
			m_target = true;
			m_frameCountTarget = 0;
		}
		else
		{
			// 遠いフラグが立っている場合はターゲットフラグを外す
			m_target = false;
			m_frameCountTarget = 0;
		}
	}
	else
	{
		// 範囲外ではあるがまだターゲットフラグを立てておく時間
		if (m_target)
		{
			if (m_frameCountTarget == kTargetFrame)
			{
				// n秒経過したらターゲットフラグを外す
				m_target = false;
				m_frameCountTarget = 0;
				return;
			}
			m_frameCountTarget++;
		}
	}
}

// 行動制御
void Boss::DecideAction()
{
	// どの範囲でもない場合は早期return
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
	
	// 近い範囲にいる場合
	else if (m_close)
	{
		// バグの原因になるので初期化
		m_frameCountFAction = kFActionFrame;
		m_frameCountTAction = kTActionFrame;
		m_targetMoveSpeed = 0.0f;
		// 攻撃中は早期returnで処理を止める
		if (m_attack)
		{
			return;
		}
		else
		{
			// 何秒かに一回処理を変える
			if (m_frameCountCAction == kCActionFrame)
			{
				// 何回も初期化すると大変なので
				m_frameCountCAction = 0;
				// n秒経過したらターゲットフラグを外す
				// ランダムで値を取得するためのもの
				int randValue = GetRandom(kRandMin, kRandMax);
				// 1/4の確率で近づいてくる
				if (randValue <= kRandMax / 4)
				{
					m_moveUp = true;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
				// 1/4の確率で遠ざかる
				else if (randValue <= kRandMax / 4 * 2)
				{
					m_moveUp = false;
					m_moveDown = true;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
				// 1/4の確率で近距離攻撃する
				else if (randValue <= kRandMax / 4 * 3)
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = true;
					m_rangedAttack = false;
					return;
				}
				// 何もしない
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
	
	// 遠い範囲にいる場合
	else if (m_far)
	{
		// バグの原因になるので初期化
		m_frameCountCAction = kCActionFrame;
		m_frameCountTAction = kTActionFrame;
		m_targetMoveSpeed = 0.0f;
		// 攻撃中は早期returnで処理を止める
		if (m_attack)
		{
			return;
		}
		else
		{
			// 何秒かに一回処理を変える
			if (m_frameCountFAction == kFActionFrame)
			{
				// 何回も初期化すると大変なので
				m_frameCountFAction = 0;
				// n秒経過したらターゲットフラグを外す
				// ランダムで値を取得するためのもの
				int randValue = GetRandom(kRandMin, kRandMax);
				// 1/4の確率で近づいてくる
				if (randValue <= kRandMax / 4)
				{
					m_moveUp = true;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = false;
					return;
				}
				// 1/4の確率で遠隔攻撃
				else if (randValue <= kRandMax / 4 * 2)
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = true;
					return;
				}
				// 1/4の確率で遠隔攻撃(仮)
				else if (randValue <= kRandMax / 4 * 3)
				{
					m_moveUp = false;
					m_moveDown = false;
					m_meleeAttack = false;
					m_rangedAttack = true;
					return;
				}
				// 何もしない
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
	
	// ターゲットできる範囲にいる場合
	else if (m_target)
	{
		// バグの原因になるので初期化
		m_frameCountFAction = kCActionFrame;
		m_frameCountCAction = kFActionFrame;
		// 何秒かに一回処理を変える
		if (m_frameCountTAction == kTActionFrame)
		{
			// 何回も初期化すると大変なので
			m_frameCountTAction = 0;
			// n秒経過したらターゲットフラグを外す
			// ランダムで値を取得するためのもの
			int randValue = GetRandom(kRandMin, kRandMax);
			// 1/4の確率で近づいてくる(普通)
			if (randValue <= kRandMax / 4)
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease / 5;
				return;
			}
			// 1/4の確率で近づいてくる(ちょっと早い)
			else if (randValue <= kRandMax / 4 * 2)
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease / 3;
				return;
			}
			// 1/4の確率で近づいてくる(早い)
			else if (randValue <= kRandMax / 4 * 3)
			{
				m_moveUp = true;
				m_moveDown = false;
				m_meleeAttack = false;
				m_rangedAttack = false;
				m_targetMoveSpeed = kMaxSpeedIncrease / 2;
				return;
			}
			// 1/4の確率で近づいてくる(ものすごく早い)
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

// 移動
void Boss::Move(float MoveDist)
{
	if (m_moveUp && m_moveDown)return;

	if (m_moveUp)
	{
		if ((MoveDist) < (m_playerRad + kBossRad))
		{
			// プレイヤーとの距離が近すぎる場合は動かない
			return;
		}
		else
		{
			// ボスの移動
			VECTOR direction = VSub(m_playerPos, m_pos);
			direction = VNorm(direction); // 正規化
			m_pos = VAdd(m_pos, VScale(direction, kMoveUpSpeed + m_targetMoveSpeed));
		}
	}
	if (m_moveDown)
	{
		// ボスの移動
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // 正規化
		m_pos = VAdd(m_pos, VScale(direction, -kMoveDownSpeed));
	}
}

// 近接攻撃
void Boss::MeleeAttack()
{
	// 近接攻撃の処理
	if (m_meleeAttack)
	{
		// 攻撃中のフラグを立てる
		m_attack = true;
		// 現在のフレーム(攻撃時間)を計測
		m_frameCountAttack++;
		// 現在の攻撃時間が設定時間と一緒になった時攻撃をやめるためのもの
		if (m_frameCountAttack == kmeleeAttack)
		{
			m_meleeAttack = false;
			m_attack = false;
			m_frameCountAttack = 0;
			return;
		}
		if (m_attack)
		{
			// 攻撃の処理
			//VECTOR end = MV1GetPosition(m_model);
			m_attackProcessor->ProcessBossAttack(this, m_targetPlayer, Melee);
		}
	}
}

// 遠隔攻撃
void Boss::RangedAttack()
{
	// 遠隔攻撃の処理
	if (m_rangedAttack)
	{
		// 攻撃中のフラグを立てる
		m_attack = true;
		// 現在のフレーム(攻撃時間)を計測
		m_frameCountAttack++;
		// 現在の攻撃時間が設定時間と一緒になった時攻撃をやめるためのもの
		if (m_frameCountAttack == krangedAttack)
		{
			m_rangedAttack = false;
			m_attack = false;
			m_frameCountAttack = 0;
			return;
		}
		if (m_attack && m_attackProcessor)
		{
			// 攻撃の処理
			m_attackProcessor->ProcessBossAttack(this, m_targetPlayer, Ranged);
		}
	}
}

void Boss::RotationXYZ()
{
	// ボスの向いている向きを変える
	VECTOR das = VSub(m_playerPos, m_pos);
	// 目標のY回転角(ラジアン)
	float targetRotY = 0;
	// 最後に入力された値を変更しないめに入力がないときは処理を行わない
	if (VSize(das) != 0)
	{
		// 正規化
		das = VNorm(das);
		// アークタンジェント
		targetRotY = atan2(das.z, das.x);

		// モデルの初期向きの補正(モデルによって調整が必要)
		targetRotY -= DX_PI_F / 2 * 3;	// 90度ずれていた分の補正
		targetRotY *= -1.0f;
	}

	// Lerpの補間係数（0.0～1.0、小さいほどゆっくり回転）
	float t = 0.1f;

	// 角度補正(補正するには「角度の差」を調整)
	float angleDiff = targetRotY - m_currentRotY;

	// 角度を -π ～ π の範囲に補正
	while (angleDiff > DX_PI_F)		{ angleDiff -= DX_PI_F * 2; }
	while (angleDiff < -DX_PI_F)	{ angleDiff += DX_PI_F * 2; }

	// 角度制限を超えていたら制限値にクリップ
	if (angleDiff > DX_PI_F / 3.0f)       angleDiff = DX_PI_F / 3.0f;
	else if (angleDiff < -DX_PI_F / 3.0f) angleDiff = -DX_PI_F / 3.0f;

	// スムーズに回転させる
	m_currentRotY += angleDiff * t;

	// 回転を設定
	MV1SetRotationXYZ(m_model, VGet(0, m_currentRotY, 0));
}

//|**日付**| 作業内容														| 目的								|		// 状況
//|**11日**| プレイヤーキャラクターのモデル表示 & 基本移動（前後左右		| プレイヤー操作の基本実装			|		// モデルが未実装
//|**12日**| プレイヤーのアニメーション / カメラとの連携					| 表示のリアリティを高める			|		// アニメーションが未実装
//|**13日**| ステージのモデル読み込み / 当たり判定のベース構築				| ステージを探索できる環境づくり	|		// 
//|**14日**| プレイヤーとステージの衝突判定実装								| すり抜けないようにする			|		// 
//|**15日**| ボスとの当たり判定（接触時ダメージ）							| 基本的な敵とのやり取り			|		// 
//|**16日**| プレイヤーの攻撃（近接 or 遠距離） & ヒット判定				| 攻撃ができるようにする			|		// 
//|**17日**| ボスの攻撃パターン（単純でOK） & ヒット処理					| 敵も攻撃してくるように			|		// 
//|**18日**| HPシステム（プレイヤー・ボス） & 勝敗条件の実装				| 戦いの目的が明確に				|		// 
//|**19日**| HPバーなど簡単なUI表示											| 状態がわかるようにする			|		// 
//|**20日**| ゲームの状態管理（タイトル → ゲーム → 終了）					| ゲームの流れを作る				|		// 
//|**21日**| テスト・バグ修正（1回目）										| プレイ可能な状態に調整			|		// 
//|**22日**| 簡易BGM・SE（リソースがあれば）								| 臨場感アップ						|		// なし
//|**23日**| エフェクト追加（ヒットや爆発など）								| 演出を整える						|		// なし
//|**24日**| 最終調整 & 通しプレイテスト									| デモとして完成させる				|		// なし
