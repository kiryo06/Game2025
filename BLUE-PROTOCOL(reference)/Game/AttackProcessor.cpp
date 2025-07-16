#include "AttackProcessor.h"
#include "Player.h"
#include "Boss.h"

void AttackProcessor::ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttacckType type)
{
	
}

void AttackProcessor::ProcessBossAttack(Boss* boss, Player* player, BossAttackType type)
{
	switch (type)
	{
	case BossAttackType::Melee:

	case BossAttackType::Ranged:

		break;
	}
}
