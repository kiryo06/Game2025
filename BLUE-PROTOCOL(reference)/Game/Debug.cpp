#include "Debug.h"  

void Debug::Init() const
{
}

void Debug::Update() const
{
}

void Debug::Draw() const
{
	//	DrawAxis();
	DrawGrid();
}

// DrawString3D の代替関数を定義
void DrawString3D(const VECTOR& position, const char* text, int size, unsigned int color)
{
	// 3D座標を2Dスクリーン座標に変換
	VECTOR screenPos;
	screenPos = VGet(0.0f, 0.0f, 0.0f);
	//	screenPos = ConvWorldPosToScreenPos(VGet(position.x, position.y, position.z));
	screenPos = VGet(position.x, position.y, position.z);
	// 変換された座標に文字列を描画
	DrawStringToHandle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), text, size, color);
}

void Debug::DrawAxis() const
{
	DrawLine3D(VGet(0, 0, 0), VGet(100, 0, 0), 0xff0000); // X軸
	DrawLine3D(VGet(0, 0, 0), VGet(0, 100, 0), 0x00ff00); // Y軸
	DrawLine3D(VGet(0, 0, 0), VGet(0, 0, 100), 0x0000ff); // Z軸
	// 軸のラベルを描画
	DrawString3D(VGet(100.0f, 10.0f, 10.0f), "X", 20, 0xff0000);
	DrawString3D(VGet(10, 100, 10), "Y", 20, 0x00ff00);
	DrawString3D(VGet(10, 10, 100), "Z", 20, 0x0000ff);
}

void Debug::DrawGrid() const
{
	for (int z = -500; z <= 500; z += 100)
	{
		DrawLine3D(VGet(-500, 0, z), VGet(500, 0, z), 0xff000);
	}
	for (int x = -500; x <= 500; x += 100)
	{
		DrawLine3D(VGet(x, 0, -500), VGet(x, 0, 500), 0x0000ff);
	}
}
