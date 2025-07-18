#include "AttackProcessor.h"
#include "Player.h"
#include "Boss.h"

namespace
{
	constexpr	const	float	BossMeleeDamage = 10.0f;
}

void AttackProcessor::ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttackType type)
{
	switch (type)
	{
	case Attack:
		break;
	case Skill_1:
		break;
	case Skill_2:
		break;
	case Skill_3:
		break;
	case Skill_4:
		break;
	case Skill_5:
		break;
	case Skill_6:
		break;
	}
}

void AttackProcessor::ProcessBossAttack(Boss* boss, Player* player, BossAttackType type)
{
	switch (type)
	{
	case BossAttackType::Melee:
		if (IsHit(player))
		{

			// ãﬂê⁄çUåÇÇÃì‡óe
		}
		break;
	case BossAttackType::Ranged:
		if (IsHit(player))
		{
			// âìäuçUåÇÇÃì‡óe
		}
		break;
	}
}

bool AttackProcessor::IsHit(Player* player)
{
	return true;
}

bool AttackProcessor::IsHit(Boss* boss)
{
	return true;
}
