#pragma once
#include "DxLib.h"

class Player;
class Bose
{
private:
	int m_model;				// ボスのモデル
	VECTOR m_pos;				// ボスの位置
public:
	Bose();
	~Bose();
	// モデルの読み込み
	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Player* m_pPlayer);
	void Draw();
private:
};

