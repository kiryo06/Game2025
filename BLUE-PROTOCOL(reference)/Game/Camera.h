#pragma once
#include "DxLib.h"
#include <memory>

class Camera
{
private:
	VECTOR m_pos;				// カメラの位置
	VECTOR m_targetPos;			// カメラの注視点
	VECTOR m_move;				// カメラの動き
	VECTOR m_cameraRot;			// カメラの回転量

	VECTOR m_cemeraGetPos;		// カメラの位置を取得
	VECTOR m_cameraGetTarget;	// カメラの注視点を取得
public:
	Camera();
	~Camera();
	void Init()const;
	void Update();
	void Draw()const;
private:
};

