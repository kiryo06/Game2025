#pragma once
#include <set>	// std::setを使うため

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
	Melee,			// 近接攻撃
	Ranged			// 遠隔攻撃
};

class AttackProcessor
{
private:
	float m_bossDamage;
	std::set<Boss*> m_hitEnemiesThisAttack;		// 攻撃の当たった敵のリストを作成
public:
	// プレイヤーからBossへの攻撃
//	void ProcessPlayerAttack(Player* player, Boss* boss, PlayerAttackType type);
	// Bossからプレイヤー絵の攻撃
	void ProcessBossAttack(Boss* boss, Player* player, BossAttackType type);
	
	// プレイヤーからBossへの攻撃処理
	void ProcessPlayerAttack(Player* player, Boss* boss);

	// 新しい攻撃が始まる前に呼ぶ
	void BeginNewAttack();
private:
	bool IsHit(Player* player);	// 仮:	簡易的な当たり判定
	bool IsHit(Boss* boss);		// 仮:　簡易的な当たり判定
};