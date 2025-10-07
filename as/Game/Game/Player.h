#pragma once
#include "DxLib.h"
#include <memory>
#include"ColliderSphere3D.h"

// プレイヤーのジャンプ中の処理をStateパターンにした
enum class JumpState
{
	Idle,			// 待機状態
	Junmping,		// ジャンプ状態
	Falling			// 落下状態
};


class AttackProcessor;
class Input;
class Camera;
class Player
{
private:			// メンバー変数
	// モデル
	int m_model;				// プレイヤーのモデル


	// 向きを保存するためのもの
	float m_rotY;
	float m_getCameraAtan2;		// カメラの回転量をもとにプレイヤーの向きや移動を変更
	
	float m_attackFrameCount;		// 攻撃のフレーム

	// キャラクターの情報
	float m_hp;					// プレイヤーのHP
	float m_attack;				// プレイヤーの攻撃力
	
	// 位置
	VECTOR m_pos;				// プレイヤーの位置
	
	// ベクトル
	VECTOR m_vec;				// プレイヤーのベクトル
	
	// Stateのパターン
	JumpState m_state;

	bool m_isAttacking;			// 攻撃中かどうかのフラグ

	std::unique_ptr<ColliderSphere3D> m_attackCollider; // 攻撃用の当たり判定
public:				// パブリック関数
	Player();
	~Player();

	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Input& input, Camera* camera, float deltaTime);
	void Draw();
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }
	bool IsAttacking() const { return m_isAttacking; }
	ColliderSphere3D* GetAttackCollider() const { return m_attackCollider.get(); }

	VECTOR GetColPos()const;
	float GetColRadius()const;
private:			// プライベート関数
	void HandleInput(Input& input);
	void Jump(float deltaTime);
	void Gravity(float deltaTime);
	void Movement(float deltaTime);
	void UpdateTransform();
	void StartAttack();                 // 攻撃を開始する
	AttackProcessor* m_attackProcessor = nullptr;
	Player* m_targetPlayer = nullptr;
};