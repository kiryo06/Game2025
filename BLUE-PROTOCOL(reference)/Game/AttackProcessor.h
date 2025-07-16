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
	Melee,			// ‹ßÚUŒ‚
	Ranged			// ‰“ŠuUŒ‚
};

class AttackProcessor
{
public:
	// ƒvƒŒƒCƒ„[‚©‚çBoss‚Ö‚ÌUŒ‚
	void ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttacckType type);
	// Boss‚©‚çƒvƒŒƒCƒ„[ŠG‚ÌUŒ‚
	void ProcessBossAttack(Boss* boss, Player* player, BossAttackType type);
};

