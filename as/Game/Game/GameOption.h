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
		std::string name					= "empty";		// 設定の種類
		std::string upDownInversion			= "empty";		// カメラの上下反転
		std::string leftRightInversion		= "empty";		// カメラの左右の反転
		std::string horizontalSensitivity	= "empty";		// カメラの水平感度
		std::string verticalSensitivity		= "empty";		// カメラの垂直感度
		std::string decision				= "empty";		// 決定
		std::string cancel					= "empty";		// キャンセル
		std::string jump					= "empty";		// ジャンプ
		std::string dash					= "empty";		// ダッシュ
		std::string attack					= "empty";		// 攻撃
		std::string skill_1					= "empty";		// スキル1
		std::string skill_2					= "empty";		// スキル2
		std::string avoidance				= "empty";		// 回避
		std::string lockOn					= "empty";		// ロックオン
		std::string squat					= "empty";		// しゃがむ
		std::string menu					= "empty";		// メニュー
		std::string option					= "empty";		// オプション
	};

	/// <summary>
	/// オーディオの情報
	/// </summary>
	struct AudioOptionData
	{
		std::string name					= "empty";		// 設定の種類
		std::string volume					= "empty";		// ボリューム
	};

	GameOption();
	~GameOption();
	void Init();
	void Update();
	void Draw();
private:
	/// <summary>
	/// ControllerOptionData.csvファイルに入っている順番
	/// </summary>
	enum class ControllerOptionDataSort
	{
		kName,								// 設定の種類
		kUpDownInversion,					// カメラの上下反転
		kLeftRightInversion,				// カメラの左右の反転
		kHorizontalSensitivity,				// カメラの水平感度
		kVerticalSensitivity,				// カメラの垂直感度
		kDecision,							// 決定
		kCancel,							// キャンセル
		kJump,								// ジャンプ
		kDash,								// ダッシュ
		kAttack,							// 攻撃
		kSkill_1,							// スキル1
		kSkill_2,							// スキル2
		kAvoidance,							// 回避
		kLockOn,							// ロックオン
		kSquat,								// しゃがむ
		kMenu,								// メニュー
		kOption								// オプション
	};

	/// <summary>
	/// AudioOptionData.csvファイルに入っている順番
	/// </summary>
	enum class AudioOptionDataSort
	{
		kName,								// 設定の種類
		kVolume								// ボリューム
	};

};

