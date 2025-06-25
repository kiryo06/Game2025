#pragma once
#include "DxLib.h"
#include <memory>

class Input;
class Camera;
class Player
{
private:
	int m_model;
	VECTOR m_pos;
	VECTOR m_vec;
	float m_rotY;

	int m_hp;

	float m_getCameraAtan2;

public:
	Player();
	~Player();

	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Input& input, Camera* camera);
	void Draw();
public:
	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }
//	VECTOR GetRot()const { return m_modelRot; }
	VECTOR GetColPos() const;
	float GetColRadius() const;
	int GetHp() const { return m_hp; }
private:
	void Move();
	bool isJumping() const;

};

