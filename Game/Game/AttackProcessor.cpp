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

			// �ߐڍU���̓��e
		}
		break;
	case BossAttackType::Ranged:
		if (IsHit(player))
		{
			// ���u�U���̓��e
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

// ���Ƌ��̓����蔻�� (���̊֐�)
bool CheckCollision(const ColliderSphere3D * sphere1, const ColliderSphere3D * sphere2)
{
    if (!sphere1 || !sphere2) return false;
    float distSq = VSize(VSub(sphere1->center, sphere2->center));
    float radiusSum = sphere1->radius + sphere2->radius;
    return distSq <= (radiusSum * radiusSum);
    }

void AttackProcessor::ProcessPlayerAttack(Player * player, Boss * boss)
{
    // 1. �v���C���[���U�����łȂ���Ή������Ȃ�
        if (!player->IsAttacking())
        {
            return;
        }
        // 2. ���̍U���Ŋ��Ƀq�b�g�ς݂Ȃ牽�����Ȃ�
        if (m_hitEnemiesThisAttack.count(boss) > 0)
        {
            return;
        }
        // 3. �����蔻����`�F�b�N
        if (CheckCollision(player->GetAttackCollider(), boss->GetHurtbox()))
        {
            // 4. �q�b�g������_���[�W��^���A�q�b�g�ς݃��X�g�ɒǉ�
            boss->TakeDamage(10.0f); // �_���[�W�ʂ�10�Ƃ���
            m_hitEnemiesThisAttack.insert(boss);
        }
}
void AttackProcessor::BeginNewAttack()
{
    m_hitEnemiesThisAttack.clear();
}