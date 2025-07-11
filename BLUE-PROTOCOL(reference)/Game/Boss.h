#pragma once
#include "DxLib.h"

class Player;
class Boss
{
private:
	// ���f��
	int m_model;				// �{�X�̃��f��
	
	// �t���[���J�E���g
	int m_frameCountClose;		// �߂��ꍇ�̃t���[�����J�E���g����
	int m_frameCountFar;		// �����ꍇ�̃t���[�����J�E���g����
	int m_frameCountTarget;		// �^�[�Q�b�g�ł���ꍇ�̃t���[�����J�E���g����
	int m_frameCountTAction;	// �^�[�Q�b�g���Ă���ꍇ���ɍs�������̍��v�t���[�����v������
	int m_frameCountFAction;	// �����ꍇ���ɍs�������̍��v�t���[�����v������
	int m_frameCountCAction;	// �߂��ꍇ���ɍs�������̍��v�t���[�����v������
	int m_frameCountAttack;		// �U�����Ă���Ƃ��̌��݂̃t���[�����Ԃ��i�[���邽�߂̂���
	
	// ���a
	float m_rad;				// �{�X�̔��a
	float m_playerRad;			// �v���C���[�̔��a

	// ���x
	float m_targetMoveSpeed;	// �^�[�Q�b�g���̈ړ����x��ς���
	
	// �ʒu
	VECTOR m_pos;				// �{�X�̈ʒu
	VECTOR m_playerPos;			// �v���C���[�̈ʒu���擾���郁���o�[
	
	// ��ԃt���O
	bool m_close;				// �߂����ǂ����𔻒f����
	bool m_far;					// �������ǂ����𔻒f����
	bool m_target;				// �^�[�Q�b�g�ł��邩�ǂ����𔻒f����
	bool m_moveUp;				// �i�ވړ������邩�ǂ����𔻒f����
	bool m_moveDown;			// �߂�ړ������邩�ǂ����𔻒f����
	bool m_meleeAttack;			// �ߐڍU�������邩�ǂ����𔻒f����
	bool m_rangedAttack;		// ���u�U�������邩�ǂ����𔻒f����
	bool m_attack;				// �U�������ǂ����𔻒f����
public:
	Boss();
	~Boss();
	// ���f���̐ݒ�
	void SetModel(int model) { m_model = model; }

	// ������
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="m_pPlayer"></param>
	void Update(Player* player);

	// �`��
	void Draw();

	// �f�o�b�O�����`��
	void DebugFormatDraw();
private:
	// �����̔���
	void CloseDistance(float closeDist);		// �ߋ���
	void FarDistance(float farDist);			// ������
	void TargetDistance(float targetDist);		// �^�[�Q�b�g�ł���͈�

	// �s������
	void DecideAction();						// �U�������邩�ړ������邩�Ƃǂ܂邩�𔻒f����

	// �ړ��E�U��
	void MoveBoss(float MoveDist);							// �{�X�̈ړ�
	void MeleeAttack();							// �ߐڍU��
	void RangedAttack();						// ���u�U��
};

