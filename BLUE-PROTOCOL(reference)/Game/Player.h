#pragma once
#include "DxLib.h"

class Player
{
private:
	VECTOR m_pos;
	VECTOR m_vec;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
};

