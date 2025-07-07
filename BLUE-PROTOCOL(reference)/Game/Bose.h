#pragma once
#include "DxLib.h"

class Player;
class Bose
{
private:
	int m_model;				// ボスのモデル
	float m_rad;				// ボスの半径
	VECTOR m_pos;				// ボスの位置
	float m_playerRad;			// プレイヤーの半径
	VECTOR m_playerPos;			// プレイヤーの位置を取得するメンバー
public:
	Bose();
	~Bose();
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

