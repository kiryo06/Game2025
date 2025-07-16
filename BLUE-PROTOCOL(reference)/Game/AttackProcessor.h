#pragma once

class Player;
class Boss;

enum PlayerAttacckType
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
public:
	// �v���C���[����Boss�ւ̍U��
	void ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttacckType type);
	// Boss����v���C���[�G�̍U��
	void ProcessBossAttack(Boss* boss, Player* player, BossAttackType type);
};

