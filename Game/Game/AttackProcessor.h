#pragma once
#include <set>	// std::set���g������

class Player;
class Boss;
enum PlayerAttackType
{
	Attack,
	Skill_1,
	Skill_2,
	Skill_3,
	Skill_4,
	Skill_5,
	Skill_6
};

enum BossAttackType
{
	Melee,			// �ߐڍU��
	Ranged			// ���u�U��
};

class AttackProcessor
{
private:
	float m_bossDamage;
	std::set<Boss*> m_hitEnemiesThisAttack;		// �U���̓��������G�̃��X�g���쐬
public:
	// �v���C���[����Boss�ւ̍U��
//	void ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttackType type);
	// Boss����v���C���[�G�̍U��
	void ProcessBossAttack(Boss* boss, Player* player, BossAttackType type);
	
	// �v���C���[����Boss�ւ̍U������
	void ProcessPlayerAttack(Player* player, Boss* boss);

	// �V�����U�����n�܂�O�ɌĂ�
	void BeginNewAttack();
private:
	bool IsHit(Player* player);	// ��:	�ȈՓI�ȓ����蔻��
	bool IsHit(Boss* boss);		// ��:�@�ȈՓI�ȓ����蔻��
};