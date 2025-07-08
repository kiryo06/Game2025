#pragma once
#include "DxLib.h"

class Player;
class Boss
{
private:
	int m_model;				// ボスのモデル
	int m_frameCountClose;		// 近い場合のフレームをカウントする
	int m_frameCountFar;		// 遠い場合のフレームをカウントする
	float m_rad;				// ボスの半径
	VECTOR m_pos;				// ボスの位置
	bool m_close;				// 近いかどうかを判断する
	bool m_far;					// 遠いかどうかを判断する

	float m_playerRad;			// プレイヤーの半径
	VECTOR m_playerPos;			// プレイヤーの位置を取得するメンバー
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
	void CloseDistance();
	// 遠距離
	void FarDistance();
};

