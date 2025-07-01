#pragma once
#include "DxLib.h"
#include <memory>

class Input;
class Camera;
class Player
{
private:
	int m_model;				// �v���C���[�̃��f��
	VECTOR m_pos;				// �v���C���[�̈ʒu
	VECTOR m_vec;				// �v���C���[�̃x�N�g��
	float m_rotY;
	int m_hp;
	float m_getCameraAtan2;		// �J�����̉�]�ʂ����ƂɃv���C���[�̌�����ړ���ύX
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