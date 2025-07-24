#include "Debug.h"  
#include <stdio.h>
#include <istream>
#include "Input.h"
#include "Pad.h"
#include "CsvLoad.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

namespace
{
	constexpr int kDrawGrid = 500;
	constexpr int kLine = 3;
	constexpr int kColumn = 6;
}


Debug::Debug():
	Sad()
{
	// 3行6列の空文字列で初期化したい場合
	Sad = std::vector<std::vector<std::string>>(kLine, std::vector<std::string>(kColumn, ""));
	CsvLoad load;
	std::vector<std::vector<std::string>> data = load.LoadFile("../../BLUE_Data.csv");
	SetDebugData(data);
}

Debug::~Debug()
{
}

void Debug::Init()
{
	printf("設定保存, 移動速度, 総フレーム, 回転速度, 加速度, 注視点\n");
	for (int i = 0; i < kLine; ++i)
	{
		printf("%1s, %1s, %1s, %1s, %1s, %1s\n",
			Sad[i][0].c_str(),
			Sad[i][1].c_str(),
			Sad[i][2].c_str(),
			Sad[i][3].c_str(),
			Sad[i][4].c_str(),
			Sad[i][5].c_str()
		);
	}
//	int test = 0;
//	test = std::stoi(Sad[1][2]);
//	test = test + 20;
//	printf("%d", test);
}

void Debug::Update(Input& input)
{
	if (input.IsTrigger("BACK"))
	{
		WriteSadToCsv("../../BLUE_Data.csv");
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

// データを読み込んで、読み込んだデータを保存する
void Debug::SetDebugData(std::vector<std::vector<std::string>> debugData)
{
	int j = 0;
	int NotEnough = 0;
	for (auto& item : debugData)
	{
		if (kLine <= j)
		{
			NotEnough++;
			printf("読み込んだデータを保存するためのスペースがあと%d行足りません\n", NotEnough);
		}
		else
		{
			DebugData pushData;
			// 名前を読み込んで保存
			pushData.kSetName = item[static_cast<int>(DebugDataSort::kName)];
			Sad[j][0] = pushData.kSetName;

			// 移動速度を読み込んで保存
			pushData.moveSpeed = item[static_cast<int>(DebugDataSort::kMoveSpeed)];
			Sad[j][1] = pushData.moveSpeed;

			// を読み込んで保存
			pushData.totalFrame = item[static_cast<int>(DebugDataSort::kTotalFrame)];
			Sad[j][2] = pushData.totalFrame;

			// を読み込んで保存
			pushData.attackFrame = item[static_cast<int>(DebugDataSort::kAttackFrame)];
			Sad[j][3] = pushData.attackFrame;

			// を読み込んで保存
			pushData.speed = item[static_cast<int>(DebugDataSort::kSpeed)];
			Sad[j][4] = pushData.speed;

			// を読み込んで保存
			pushData.animationName = item[static_cast<int>(DebugDataSort::kTorigerName)];
			Sad[j][5] = pushData.animationName;

			m_debugData[item[static_cast<int>(DebugDataSort::kName)]] = pushData;
			j++;
		}
	}
}

// Sadの内容をCSVファイルに書き込む
void Debug::WriteSadToCsv(const std::string& filename)
{
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		printf("ファイル %s を開けませんでした\n", filename.c_str());
		return;
	}

	// ヘッダー行を書き込む
	ofs << "設定保存,移動速度,総フレーム,回転速度,加速度,注視点\n";

	// Sadの内容を書き込む
	for (const auto& row : Sad) {
		for (size_t i = 0; i < row.size(); ++i) {
			// カンマやダブルクォートを含む場合はクォートで囲む
			std::string field = row[i];
			if (field.find(',') != std::string::npos || field.find('"') != std::string::npos)
			{
				std::string quoted;
				quoted += '"';
				for (char c : field)
				{
					if (c == '"') quoted += "\"\"";
					else quoted += c;
				}
				quoted += '"';
				field = quoted;
			}
			ofs << field;
			if (i != row.size() - 1) ofs << ",";
		}
		ofs << "\n";
	}
	ofs.close();
	printf("ファイル %s に保存しました\n", filename.c_str());
}


void Debug::DrawAxis() const
{
	DrawLine3D(VGet(0, 0, 0), VGet(100, 0, 0), 0xff0000); // X軸
	DrawLine3D(VGet(0, 0, 0), VGet(0, 100, 0), 0x00ff00); // Y軸
	DrawLine3D(VGet(0, 0, 0), VGet(0, 0, 100), 0x0000ff); // Z軸
	// 軸のラベルを描画
	DrawString3D(VGet(100.0f,  10.0f,  10.0f), "X", 20, 0xff0000);
	DrawString3D(VGet( 10.0f, 100.0f,  10.0f), "Y", 20, 0x00ff00);
	DrawString3D(VGet( 10.0f,  10.0f, 100.0f), "Z", 20, 0x0000ff);
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
