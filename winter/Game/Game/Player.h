#pragma once
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
private:
	// モデル
	int m_model;

	// 向きを保存するためのもの
	float m_rotY;
	float m_getCameraAtan2;

	float m_attackFrameCount;

	float m_hp;
	float m_attack;

	// 位置
	VECTOR m_pos;
	// ベクトル
	VECTOR m_vec;

	bool m_isAttacking;

	std::unique_ptr<ColliderSphere3D>
};

