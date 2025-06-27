#include "Debug.h"  
#include <stdio.h>
#include "Input.h"
#include "Pad.h"

namespace
{
	constexpr int kDrawGrid = 500;
}

// ファイルにデータを書き込む関数
static bool WriteSampleDataToFile(const char* filename)
{
	// はじめはnullptrを入れておく
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, filename, "w");
	if (err != 0 || fp == nullptr) {
		printf("ファイルが開けませんでした。\n");
		return false;
	}

	char* dasd = const_cast<char*>("dasd");
	// データを書き込む
	fprintf(fp, "Name,Age,City,43,31,312,31,31,31,31,31,31\n");
	fprintf(fp, "Yamada,25,Tokyo\n");
	fprintf(fp, "Tanaka,30,Osaka\n");
	fprintf(fp, "m_Data1,%s", dasd);
	fprintf(fp, "%s\n", dasd);
	fprintf(fp, "%s\n", dasd);
	// ファイルを閉じる
	fclose(fp);
	printf("データが書き込まれました。\n");
	return true;
}

// ファイルからデータを読み込む関数
static bool ReadDataFromFile(const char* filename)
{
	// はじめはnullptrを入れておく
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, filename, "r");
	if (err != 0 || fp == nullptr) {
		printf("ファイルが開けませんでした。\n");
		return false;
	}

	char data[256];
	// データを読み込み
	fscanf_s(fp, "%255s", data, (unsigned)_countof(data));
	printf("データが読み込まれました。\n");
	// ファイルを閉じる
	fclose(fp);
	return true;
}

Debug::Debug():
	m_FileData("../../BLUE_Data.csv"),
	m_Data1("test"),
	m_Data2("test"),
	m_Data3("test"),
	m_Data4("test")
{
}

Debug::~Debug()
{
}

void Debug::Init()
{
//	m_FileData = "../../BLUE_Data.csv";
	// サンプルデータを書き込む
	ReadDataFromFile(m_FileData);
}

void Debug::Update(Input& input)
{
	if (input.IsTrigger("DataDebug"))
	{
		// サンプルデータを書き込む
		WriteSampleDataToFile(m_FileData);
	}
}

void Debug::Draw()
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
	for (int z = -kDrawGrid; z <= kDrawGrid; z += 100)
	{
		DrawLine3D(VGet(-kDrawGrid, 0, z), VGet(kDrawGrid, 0, z), 0xff0099);
	}
	for (int x = -kDrawGrid; x <= kDrawGrid; x += 100)
	{
		DrawLine3D(VGet(x, 0, -kDrawGrid), VGet(x, 0, kDrawGrid), 0x0099ff);
	}
}
