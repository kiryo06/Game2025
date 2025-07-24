#pragma once
#include <map>
#include <string>
#include <vector>

class KeyConfigScene;

/// <summary>
/// 入力系をつかさどるクラス
/// </summary>
class Input
{
	friend KeyConfigScene; // KeyConfigSceneをお友達認定…privateでもprotectedでもアクセス可能
private:
	/// <summary>
	/// 周辺機器種別
	/// </summary>
	enum class PeripheralType
	{
		keybd, // キーボード
		pad1 // パッド1
	};
	// 入力情報定義用
	struct InputState
	{
		PeripheralType type;
		int id; // 入力のID
	};

	using InputTable_t = std::map < std::string, std::vector<InputState>>;
	using InputRecord_t = std::map < std::string, bool>;

	// 名前と実際の入力の対応表
	InputTable_t inputTable_;
	InputTable_t tempInputTable_;

	// 切り離して再利用できるように
	void SetDefault();
	// キーコンフィグ暫定処理用
	void SetTempDefault();
	// キーコンフィグ用の一時テーブルを本テーブルに反映
	void CommitEdittedInputTable();
	// 一時テーブルを元に戻す
	void RollbackEdittedInputTable();

	// 押されたかどうかを記録していくもの
	InputRecord_t current_;
	InputRecord_t last_;

	std::vector<std::string> orderForDisplay;

	// 直近の入力コードを返す関数
	// friendのKeyConfigに贈る関数
	int GetLastKeyboadState();
	// Pad版
	int GetLastPadState();

	void SaveInputTable();
	// 入力テーブルの反映までやる
	void LoadInputTable();

	// キーコン用
	int currentRawPadState_;
	int lastRawPadState_;

	char currentRawKeybdState_[256];
	char lastRawKeybdState_[256];
public:
	Input();

	/// <summary>
	/// 入力状態を更新
	/// </summary>
	void Update();

	/// <summary>
	/// 押した瞬間を検出
	/// </summary>
	/// <param name="id">入力コード</param>
	/// <returns>true:押した瞬間 false:押してないor押しっぱなし</returns>
	bool IsTrigger(std::string key) const;

	bool IsPressed(const char* key) const;
};

