#pragma once
#include "DxLib.h"
#include <memory>

class Input;
class Player
{
private:
	int m_model;
	VECTOR m_pos;
	VECTOR m_vec;
	float m_rotY;

	int m_hp;
public:
	Player();
	~Player();

	void SetModel(int model) { m_model = model; }

	void Init();
	void Update(Input& input);
	void Draw();

	VECTOR GetPos()const { return m_pos; }
	VECTOR GetVec()const { return m_vec; }
//	VECTOR GetRot()const { return m_modelRot; }

	VECTOR GetColPos() const;


	int GetHp() const { return m_hp; }
	float GetColRadius() const;

private:

	bool isJumping() const;
};

