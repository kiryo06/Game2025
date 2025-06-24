#pragma once
#include "DxLib.h"
#include <memory>

class Camera
{
private:
	VECTOR m_pos;				// �J�����̈ʒu
	VECTOR m_targetPos;			// �J�����̒����_
	VECTOR m_move;				// �J�����̓���
	VECTOR m_cameraRot;			// �J�����̉�]��

	VECTOR m_cemeraGetPos;		// �J�����̈ʒu���擾
	VECTOR m_cameraGetTarget;	// �J�����̒����_���擾
public:
	Camera();
	~Camera();
	void Init()const;
	void Update();
	void Draw()const;
private:
};

