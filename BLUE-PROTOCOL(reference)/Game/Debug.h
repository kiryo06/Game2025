#pragma once
#include "DxLib.h"

class Input;
class Debug
{
private:
//	const char* m_FileData;
	std::vector<std::vector<std::string>> m_FileData;
	char* m_Data1;
//	char* m_Data2[256];
//	const char* m_Data1[256];
	const char* m_Data2[256];
public:
	Debug();
	~Debug();
	void Init();
	void Update(Input& input);
	void Draw();

private:
	// デバッグ用の座標軸を描画するための関数
	void DrawAxis() const;
	// デバッグ用のグリッドを描画するための関数
	void DrawGrid() const;
};

