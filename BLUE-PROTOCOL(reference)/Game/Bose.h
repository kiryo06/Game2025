#pragma once
#include "DxLib.h"

class Player;
class Bose
{
private:
	int m_model;				// �{�X�̃��f��
	VECTOR m_pos;				// �{�X�̈ʒu
public:
	Bose();
	~Bose();
	// ���f���̓ǂݍ���
	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Player* m_pPlayer);
	void Draw();
private:
};

