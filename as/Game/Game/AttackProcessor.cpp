#include "AttackProcessor.h"
#include "Player.h"
#include "Boss.h"
#include "Geometry.h"

namespace
{
	constexpr	const	float	BossMeleeDamage = 10.0f;
}

//void AttackProcessor::ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttackType type)
//{
//	switch (type)
//	{
//	case Attack:
//		break;
//	case Skill_1:
//		break;
//	case Skill_2:
//		break;
//	case Skill_3:
//		break;
//	case Skill_4:
//		break;
//	case Skill_5:
//		break;
//	case Skill_6:
//		break;
//	}
//}

void AttackProcessor::ProcessBossAttack(Boss* boss, Player* player, BossAttackType type)
{
	switch (type)
	{
	case BossAttackType::Melee:
		if (IsHit(player))
		{

			// 近接攻撃の内容
		}
		break;
	case BossAttackType::Ranged:
		if (IsHit(player))
		{
			// 遠隔攻撃の内容
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

// 球と球の当たり判定 (仮の関数)
bool CheckCollision(const ColliderSphere3D * sphere1, const ColliderSphere3D * sphere2)
{
    if (!sphere1 || !sphere2) return false;
    float distSq = VSize(VSub(sphere1->center, sphere2->center));
    float radiusSum = sphere1->radius + sphere2->radius;
    return distSq <= (radiusSum * radiusSum);
    }

void AttackProcessor::ProcessPlayerAttack(Player * player, Boss * boss)
{
    // 1. プレイヤーが攻撃中でなければ何もしない
        if (!player->IsAttacking())
        {
            return;
        }
        // 2. この攻撃で既にヒット済みなら何もしない
        if (m_hitEnemiesThisAttack.count(boss) > 0)
        {
            return;
        }
        // 3. 当たり判定をチェック
        if (CheckCollision(player->GetAttackCollider(), boss->GetHurtbox()))
        {
            // 4. ヒットしたらダメージを与え、ヒット済みリストに追加
            boss->TakeDamage(10.0f); // ダメージ量を10とする
            m_hitEnemiesThisAttack.insert(boss);
        }
}
void AttackProcessor::BeginNewAttack()
{
    m_hitEnemiesThisAttack.clear();
}