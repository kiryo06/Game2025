#pragma once
#include "DxLib.h"

class Camera
{
private:
	VECTOR m_pos;
	VECTOR m_targetPos;
	VECTOR m_move;
public:
	Camera();
	~Camera();
	void Init()const;
	void Update();
	void Draw()const;
private:
};

