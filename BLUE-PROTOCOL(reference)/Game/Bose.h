#pragma once
#include "DxLib.h"

class Player;
class Bose
{
private:
	int m_model;				// �{�X�̃��f��
	int m_frameCount;				// �t���[�����J�E���g����
	float m_rad;				// �{�X�̔��a
	VECTOR m_pos;				// �{�X�̈ʒu
	bool m_close;				// �߂����ǂ����𔻒f����
	bool m_far;					// �������ǂ����𔻒f����

	float m_playerRad;			// �v���C���[�̔��a
	VECTOR m_playerPos;			// �v���C���[�̈ʒu���擾���郁���o�[
public:
	Bose();
	~Bose();
	// ���f���̓ǂݍ���
	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Player* m_pPlayer);
	void Draw();
private:
	// �ߋ���
	void CloseDistance();
	// ������
	void FarDistance();
};

