#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include <vector>
			
class Input;
class GameOption
{
private:
	// 読み込むためのファイルを保存するためのメンバー変数
	std::vector<std::vector<std::string>> m_controllerOptionDataFile;	// コントローラー用のファイル名保存
	std::vector<std::vector<std::string>> m_audioOptionDataFile;		// オーディオ用のファイル名保存
	// 読み込んだデータを保存しておくためのメンバー変数
	std::vector<std::vector<std::string>> m_controllerOptionData;		// コントローラー用のデータ保存
	std::vector<std::vector<std::string>> m_audioOptionData;			// オーディオ用のデータ保存
public:


	/// <summary>
	/// コントローラーの情報
	/// </summary>
	struct ControllerOptionData
	{
		std::string kSetName				= "empty";							// 設定の種類
		std::string kUpDownInversion		= "empty";					// カメラの上下反転
		std::string kLeftRightInversion		= "empty";				// カメラの左右の反転
		std::string kHorizontalSensitivity	= "empty";			// カメラの水平感度
		std::string kVerticalSensitivity	= "empty";				// カメラの垂直感度
		std::string kDecision				= "empty";						// 決定
		std::string kCancel					= "empty";							// キャンセル
		std::string kJump			= "empty";		// ジャンプ
		std::string kDash			= "empty";		// ダッシュ
		std::string kSetName			= "empty";		// 攻撃
		std::string kSetName			= "empty";		// スキル1
		std::string kSetName			= "empty";		// スキル2
		std::string kSetName			= "empty";		// 回避
		std::string kSetName			= "empty";		// ロックオン
		std::string kSetName			= "empty";		// しゃがむ
		std::string kSetName			= "empty";		// メニュー
		std::string kSetName			= "empty";		// オプション
	};

	/// <summary>
	/// オーディオの情報
	/// </summary>
	struct AudioOptionData
	{
		std::string kSetName	= "empty";
		std::string kVolume		= "empty";
	};

	GameOption();
	~GameOption();
	void Init();
	void Update();
	void Draw();
private:
};

