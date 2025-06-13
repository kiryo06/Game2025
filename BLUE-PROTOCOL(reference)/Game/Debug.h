#pragma once
#include "DxLib.h"

class Debug
{
private:

public:
	void Init()const;
	void Update()const;
	void Draw()const;

private:
	// デバッグ用の座標軸を描画するための関数
	void DrawAxis() const;
	// デバッグ用のグリッドを描画するための関数
	void DrawGrid() const;

};

