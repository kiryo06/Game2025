#pragma once
#include "DxLib.h"

class Player;
class Boss
{
private:
	int m_model;				// �{�X�̃��f��
	int m_frameCountClose;		// �߂��ꍇ�̃t���[�����J�E���g����
	int m_frameCountFar;		// �����ꍇ�̃t���[�����J�E���g����
	int m_frameCountTarget;		// �^�[�Q�b�g�ł���ꍇ�̃t���[�����J�E���g����
	int m_frameCountTAction;	// �^�[�Q�b�g���Ă���ꍇ���ɍs�������̍��v�t���[�����v������
	int m_frameCountFAction;	// �����ꍇ���ɍs�������̍��v�t���[�����v������
	int m_frameCountCAction;	// �߂��ꍇ���ɍs�������̍��v�t���[�����v������
	float m_rad;				// �{�X�̔��a
	float m_playerRad;			// �v���C���[�̔��a
	VECTOR m_pos;				// �{�X�̈ʒu
	VECTOR m_playerPos;			// �v���C���[�̈ʒu���擾���郁���o�[
	bool m_close;				// �߂����ǂ����𔻒f����
	bool m_far;					// �������ǂ����𔻒f����
	bool m_target;				// �^�[�Q�b�g�ł��邩�ǂ����𔻒f����
	bool m_moveUp;				// �i�ވړ������邩�ǂ����𔻒f����
	bool m_moveDown;			// �߂�ړ������邩�ǂ����𔻒f����
	bool m_meleeAttack;			// �ߐڍU�������邩�ǂ����𔻒f����
	bool m_rangedAttack;		// ���u�U�������邩�ǂ����𔻒f����
public:
	Boss();
	~Boss();
	// ���f���̓ǂݍ���
	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Player* m_pPlayer);
	void Draw();
private:
	// �ߋ���
	void CloseDistance(float closeDist);
	// ������
	void FarDistance(float farDist);
	// �^�[�Q�b�g�ł���͈�
	void TargetDistance(float targetDist);
	// �U�������邩�ړ������邩�Ƃǂ܂邩�𔻒f����
	void DecideAction();
	// �{�X�̈ړ�
	void MoveBoss();
	// �ߐڍU��
	void MeleeAttack();
	// ���u�U��
	void RangedAttack();
};

