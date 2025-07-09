#pragma once
#include "DxLib.h"

class Player;
class Boss
{
private:
	int m_model;				// ボスのモデル
	int m_frameCountClose;		// 近い場合のフレームをカウントする
	int m_frameCountFar;		// 遠い場合のフレームをカウントする
	int m_frameCountTarget;		// ターゲットできる場合のフレームをカウントする
	int m_frameCountTAction;	// ターゲットしている場合次に行う処理の合計フレームを計測する
	int m_frameCountFAction;	// 遠い場合次に行う処理の合計フレームを計測する
	int m_frameCountCAction;	// 近い場合次に行う処理の合計フレームを計測する
	float m_rad;				// ボスの半径
	float m_playerRad;			// プレイヤーの半径
	VECTOR m_pos;				// ボスの位置
	VECTOR m_playerPos;			// プレイヤーの位置を取得するメンバー
	bool m_close;				// 近いかどうかを判断する
	bool m_far;					// 遠いかどうかを判断する
	bool m_target;				// ターゲットできるかどうかを判断する
	bool m_moveUp;				// 進む移動をするかどうかを判断する
	bool m_moveDown;			// 戻る移動をするかどうかを判断する
	bool m_meleeAttack;			// 近接攻撃をするかどうかを判断する
	bool m_rangedAttack;		// 遠隔攻撃をするかどうかを判断する
public:
	Boss();
	~Boss();
	// モデルの読み込み
	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Player* m_pPlayer);
	void Draw();
private:
	// 近距離
	void CloseDistance(float closeDist);
	// 遠距離
	void FarDistance(float farDist);
	// ターゲットできる範囲
	void TargetDistance(float targetDist);
	// 攻撃をするか移動をするかとどまるかを判断する
	void DecideAction();
	// ボスの移動
	void MoveBoss();
	// 近接攻撃
	void MeleeAttack();
	// 遠隔攻撃
	void RangedAttack();
};

