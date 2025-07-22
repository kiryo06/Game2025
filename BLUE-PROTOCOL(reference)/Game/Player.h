#pragma once
#include "DxLib.h"
#include <memory>

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
private:
	// モデル
	int m_model;				// プレイヤーのモデル

	// 向きを保存するためのもの
	float m_rotY;

	float m_getCameraAtan2;		// カメラの回転量をもとにプレイヤーの向きや移動を変更
	
	// キャラクターの情報
	float m_hp;					// プレイヤーのHP
	float m_attack;				// プレイヤーの攻撃力
	
	// 位置
	VECTOR m_pos;				// プレイヤーの位置
	
	// ベクトル
	VECTOR m_vec;				// プレイヤーのベクトル
	
	// Stateのパターン
	JumpState m_state;
public:
	Player();
	~Player();

	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Input& input, Camera* camera, float deltaTime);
	void Draw();
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }
	VECTOR GetColPos()const;
	float GetColRadius()const;
private:
	void HandleInput(Input& input);
	void Jump(float deltaTime);
	void Gravity(float deltaTime);
	void Movement(float deltaTime);
	void UpdateTransform();
	AttackProcessor* m_attackProcessor = nullptr;
	Player* m_targetPlayer = nullptr;
};