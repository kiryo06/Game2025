#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include <vector>

class Input;
class Debug
{
private:
	std::vector<std::vector<std::string>> m_FileData;
	std::vector<std::vector<std::string>> Sad;

public:
	/// <summary>
	/// 通常攻撃の情報
	/// </summary>
	struct DebugData
	{
		std::string kSetName		= "empty";
		std::string moveSpeed		= "empty";
		std::string totalFrame		= "empty";
		std::string attackFrame		= "empty";
		std::string speed			= "empty";
		std::string animationName	= "empty";
	};

	Debug();
	~Debug();
	void Init();
	void Update(Input& input);
	void Draw();
	/// <summary>
	/// 各キャラ共通で使用する通常攻撃を設定する
	/// </summary>
	/// <param name="debugData">csvファイルから持ってきた情報</param>
	void SetDebugData(std::vector<std::vector<std::string>> debugData);
	// Csvに書き込む
	void WriteSadToCsv(const std::string& filename);
private:
	// デバッグ用の座標軸を描画するための関数
	void DrawAxis() const;
	// デバッグ用のグリッドを描画するための関数
	void DrawGrid() const;

	/// <summary>
	/// csvファイルに入っている順番
	/// </summary>
	enum class DebugDataSort
	{
		kName,				//設定保存
		kMoveSpeed,			//移動速度
		kTotalFrame,		//行動フレーム
		kAttackFrame,		//回転速度
		kSpeed,				//加速度
		kTorigerName		//注視点
	};
	//すべてのキャラで共通で使う通常攻撃の情報
	std::map<std::string, DebugData> m_debugData;
};

