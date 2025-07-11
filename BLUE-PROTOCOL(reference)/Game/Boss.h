#pragma once
#include "DxLib.h"

class Player;
class Boss
{
private:
	// モデル
	int m_model;				// ボスのモデル
	
	// フレームカウント
	int m_frameCountClose;		// 近い場合のフレームをカウントする
	int m_frameCountFar;		// 遠い場合のフレームをカウントする
	int m_frameCountTarget;		// ターゲットできる場合のフレームをカウントする
	int m_frameCountTAction;	// ターゲットしている場合次に行う処理の合計フレームを計測する
	int m_frameCountFAction;	// 遠い場合次に行う処理の合計フレームを計測する
	int m_frameCountCAction;	// 近い場合次に行う処理の合計フレームを計測する
	int m_frameCountAttack;		// 攻撃しているときの現在のフレーム時間を格納するためのもの
	
	// 半径
	float m_rad;				// ボスの半径
	float m_playerRad;			// プレイヤーの半径

	// 速度
	float m_targetMoveSpeed;	// ターゲット中の移動速度を変える
	
	// 位置
	VECTOR m_pos;				// ボスの位置
	VECTOR m_playerPos;			// プレイヤーの位置を取得するメンバー
	
	// 状態フラグ
	bool m_close;				// 近いかどうかを判断する
	bool m_far;					// 遠いかどうかを判断する
	bool m_target;				// ターゲットできるかどうかを判断する
	bool m_moveUp;				// 進む移動をするかどうかを判断する
	bool m_moveDown;			// 戻る移動をするかどうかを判断する
	bool m_meleeAttack;			// 近接攻撃をするかどうかを判断する
	bool m_rangedAttack;		// 遠隔攻撃をするかどうかを判断する
	bool m_attack;				// 攻撃中かどうかを判断する
public:
	Boss();
	~Boss();
	// モデルの設定
	void SetModel(int model) { m_model = model; }

	// 初期化
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="m_pPlayer"></param>
	void Update(Player* player);

	// 描画
	void Draw();

	// デバッグ文字描画
	void DebugFormatDraw();
private:
	// 距離の判定
	void CloseDistance(float closeDist);		// 近距離
	void FarDistance(float farDist);			// 遠距離
	void TargetDistance(float targetDist);		// ターゲットできる範囲

	// 行動決定
	void DecideAction();						// 攻撃をするか移動をするかとどまるかを判断する

	// 移動・攻撃
	void MoveBoss(float MoveDist);							// ボスの移動
	void MeleeAttack();							// 近接攻撃
	void RangedAttack();						// 遠隔攻撃
};

