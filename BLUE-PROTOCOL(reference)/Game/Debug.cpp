#include "Debug.h"  
#include <stdio.h>
#include <istream>

#include <string>
#include <sstream>

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

	char* dasd = const_cast<char*>("dasdsad");
	// データを書き込む
	fprintf(fp, "Name,Age,City,43,31,312,31,31,31,31,31,31\n");
	fprintf(fp, "Yamada,25,Tokyo\n");
	fprintf(fp, "Tanaka,30,Osaka\n");
	fprintf(fp, "m_Data1,%s\n", dasd);
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

//	char data[256];
//	// データを読み込み
//	fscanf_s(fp, "%255s", data, (unsigned)_countof(data));
//
//	// 
//
////	std::string neme;
//	while (std::getline(fp, data, ','))
//	{
//		std::string neme;
//		printf("読み込んだデータ: %s\n", neme.c_str());
//	}


	char buffer[1024];
	std::string data;

	// ファイル全体を読み込む
	while (fgets(buffer, sizeof(buffer), fp)) {
		data += buffer;
	}

	fclose(fp);

	// データを解析
	std::istringstream stream(data);
	std::string token;
	while (std::getline(stream, token, ',')) {
		printf("読み込んだデータ: %s\n", token.c_str());
	}


	printf("データが読み込まれました。\n");
//	printf("%s\n",data);
	// ファイルを閉じる
	fclose(fp);
	return true;
}

Debug::Debug():
	m_FileData("../../BLUE_Data.csv"),
	m_Data1(),
	m_Data2(),
	m_Data3(),
	m_Data4()
{
}

Debug::~Debug()
{
}

void Debug::Init()
{
	// サンプルデータを読み込み
	ReadDataFromFile(m_FileData);

	//FILE* fp = nullptr;
	//errno_t err = fopen_s(&fp, m_FileData, "r");

	//// データを読み込み  
	//fscanf_s(fp, "%s", m_Data1);
	//fscanf_s(fp, "%s", m_Data2);
	//fscanf_s(fp, "%s", m_Data3);
	//fscanf_s(fp, "%s", m_Data4);
	//printf("%s\n", m_Data1);
	//printf("%s\n", m_Data2);
	//printf("%s\n", m_Data3);
	//printf("%s\n", m_Data4);
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
