#include "Boss.h"
#include "Player.h"
namespace
{
	constexpr	const	int		CloseFrame		= 60 * 2;					// 近距離のフレーム数
	constexpr	const	int		FarFrame		= 60 * 3;					// 遠距離のフレーム数
	constexpr	const	int		TargetFrame		= 60 * 4;					// ターゲットのフレーム数
	constexpr	const	int		TActionFrame	= 60 * 2;					// ターゲットのフレーム数
	constexpr	const	int		FActionFrame	= 60 * 2;					// ターゲットのフレーム数
	constexpr	const	int		CActionFrame	= 60 * 2;					// ターゲットのフレーム数
	constexpr	const	float	BossRad			= {  1000.0f };				// ボスの半径
	constexpr	const	float	Close			= {  4000.0f };				// 近距離かどうかの判定距離
	constexpr	const	float	Far				= {  7000.0f };				// 遠距離かどうかの判定距離
	constexpr	const	float	Target			= { 10000.0f };				// ターゲットできる距離
	constexpr	const	float	MoveUpSpeed		= {	   10.0f };				// 近づく速度
	constexpr	const	float	MoveDownSpeed	= {     5.0f };				// 離れる速度
	constexpr	const	VECTOR	BossPos			= { 0.0f, 0.0f, -1000.0f };	// ボスの初期位置
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
	// プレイヤーの位置を受け取る
	m_playerPos = m_pPlayer->GetPos();
	// プレイヤーの当たり判定の半径を受け取る
	m_playerRad = m_pPlayer->GetColRadius();
	// ボスの位置からプレイヤーの位置引いた値を入れる
	float distX = m_pos.x - m_playerPos.x;
	float distY = m_pos.y - m_playerPos.y;
	float distZ = m_pos.z - m_playerPos.z;
	// ボスとプレイヤーの距離を求める
	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);
	// ボスが攻撃するために必要な距離の条件
	CloseDistance(dist);
	FarDistance(dist);
	TargetDistance(dist);

	// 距離に合わせて何をするかを判断する
	DecideAction();
	// ボスの移動
	MoveBoss();

	// ボスの攻撃
	MeleeAttack();
	RangedAttack();

	// ボスの向いている向きを変える
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

#ifdef _DEBUG
	// ボスの当たり判定
	DrawCapsule3D(m_pos, m_pos, BossRad, 16, 0xffff00, 0xffff00, false);
	// 近距離のターゲット
	DrawCapsule3D(m_pos, m_pos, Close,16,0xffff00,0xffff00,false);
	// 遠距離のターゲット
	DrawCapsule3D(m_pos, m_pos, Far,16,0xffff00,0xffff00,false);
	// ターゲットできる範囲
	DrawCapsule3D(m_pos, m_pos, Target, 16, 0xffff00, 0xffff00, false);

	printf("近い:%d遠い:%dターゲット:%d\n", m_frameCountClose, m_frameCountFar,m_frameCountTarget);
	printf("移動:%d\n", m_frameCountTAction);
	if (m_close)
	{
		DrawFormatString(20, 150, 0xffffff, "近距離\n");
	}
	if (m_far)
	{
		DrawFormatString(20, 166, 0xffffff, "遠距離\n");
	}
	if (m_target)
	{
		DrawFormatString(20, 182, 0x00ff00, "ターゲット中\n");
	}
	if(!m_close && !m_far && !m_target)
	{
		DrawFormatString(20, 198, 0xff0000, "範囲外\n");
	}

	if (m_moveUp|| m_moveDown)
	{
		DrawFormatString(20, 204, 0x00ff00, "移動中\n");
	}

	if (!m_moveUp && !m_moveDown)
	{
		DrawFormatString(20, 204, 0x00ff00, "移動不可\n");
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

void Boss::FarDistance(float farDist)
{
	if ((farDist) < (m_playerRad + Far))
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

void Boss::TargetDistance(float targetDist)
{
	if ((targetDist) < (m_playerRad + Target))
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
			if (m_frameCountTarget == TargetFrame)
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

void Boss::DecideAction()
{
	if (m_close)		// 近い範囲にいる場合
	{
		// 何秒かに一回処理を変える
		if (m_frameCountCAction == CActionFrame)
		{
			// n秒経過したらターゲットフラグを外す
			// ランダムで値を取得するためのもの
			int randValue = GetRandom(1, 6);
			if (randValue <= 3)	// 1/2の確率で近づいてくる
			{
				m_moveUp = true;
			}
			else				// 何もしない
			{
				m_moveUp = false;
			}
			m_frameCountCAction = 0;
			return;
		}
		m_frameCountCAction++;
	}
	else if (m_far)			// 遠い範囲にいる場合
	{
		// 何秒かに一回処理を変える
		if (m_frameCountFAction == FActionFrame)
		{
			// n秒経過したらターゲットフラグを外す
			// ランダムで値を取得するためのもの
			int randValue = GetRandom(1, 6);
			if (randValue <= 3)	// 1/2の確率で近づいてくる
			{
				m_moveUp = true;
			}
			else				// 何もしない
			{
				m_moveUp = false;
			}
			m_frameCountFAction = 0;
			return;
		}
		m_frameCountFAction++;
	}
	else if (m_target)			// ターゲットできる範囲にいる場合
	{
		// 何秒かに一回処理を変える
		if (m_frameCountTAction == TActionFrame)
		{
			// n秒経過したらターゲットフラグを外す
			// ランダムで値を取得するためのもの
			int randValue = GetRandom(1, 6);
			if (randValue <= 3)	// 1/2の確率で近づいてくる
			{
				m_moveUp = true;
			}
			else				// 何もしない
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
		// ボスの移動
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // 正規化
		m_pos = VAdd(m_pos, VScale(direction, MoveUpSpeed));
	}
	if (m_moveDown)
	{
		// ボスの移動
		VECTOR direction = VSub(m_playerPos, m_pos);
		direction = VNorm(direction); // 正規化
		m_pos = VAdd(m_pos, VScale(direction, -MoveDownSpeed));
	}
}

void Boss::MeleeAttack()
{
	// 近接攻撃の処理
	if (m_meleeAttack)
	{
		//// 近接攻撃の処理を行う
		//m_frameCountClose++;
		//if (m_frameCountClose >= CloseFrame)
		//{
		//	// 攻撃の処理を行う
		//	m_frameCountClose = 0; // フレームカウントをリセット
		//	// 攻撃の処理を書く
		//	// 例えば、プレイヤーにダメージを与えるなど
		//}
	}
}

void Boss::RangedAttack()
{
	// 遠隔攻撃の処理
	if (m_rangedAttack)
	{
		//// 遠隔攻撃の処理を行う
		//m_frameCountFar++;
		//if (m_frameCountFar >= FarFrame)
		//{
		//	// 攻撃の処理を行う
		//	m_frameCountFar = 0; // フレームカウントをリセット
		//	// 攻撃の処理を書く
		//	// 例えば、プレイヤーにダメージを与えるなど
		//}
	}
}
