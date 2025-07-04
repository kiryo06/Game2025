#include "Input.h"
#include <cassert>
#include <DxLib.h>

namespace
{
	const char* key_config_signature = "kcfg";
	const char* key_config_filemane = "keyconfig.dat";
}

void Input::SetDefault()
{
	inputTable_["next"] =
	{
		{PeripheralType::keybd, KEY_INPUT_RETURN}
//		{PeripheralType::pad1, PAD_INPUT_8}
	};

	inputTable_["Aボタン"] =
	{
		{PeripheralType::pad1, PAD_INPUT_1}
	};
	inputTable_["Bボタン"] =
	{
		{PeripheralType::pad1, PAD_INPUT_2}
	};
	inputTable_["Xボタン"] =
	{
		{PeripheralType::pad1, PAD_INPUT_3}
	};
	inputTable_["Yボタン"] =
	{
		{PeripheralType::pad1, PAD_INPUT_4}
	};
	inputTable_["Lボタン"] =
	{
		{PeripheralType::pad1, PAD_INPUT_5}
	};
	inputTable_["Rボタン"] =
	{
		{PeripheralType::pad1, PAD_INPUT_6}
	};
	inputTable_["BACK"] =
	{
		{PeripheralType::pad1, PAD_INPUT_7}
	};
	inputTable_["START"] =
	{
		{PeripheralType::pad1, PAD_INPUT_8}
	};
	inputTable_["左スティック押しこみ"] =
	{
		{PeripheralType::pad1, PAD_INPUT_9}
	};
	inputTable_["右スティック押しこみ"] =
	{
		{PeripheralType::pad1, PAD_INPUT_10}
	};

#if false
	// Aボタン
	inputTable_["Pad_1"] =
	{
		{PeripheralType::pad1, PAD_INPUT_1}
	};
	// Bボタン
	inputTable_["Pad_2"] =
	{
		{PeripheralType::pad1, PAD_INPUT_2}
	};
	// Xボタン
	inputTable_["Pad_3"] =
	{
		{PeripheralType::pad1, PAD_INPUT_3}
	};
	// Yボタン
	inputTable_["Pad_4"] =
	{
		{PeripheralType::pad1, PAD_INPUT_4}
	};
	// 左ボタン(小さいやつ)
	inputTable_["Pad_5"] =
	{
		{PeripheralType::pad1, PAD_INPUT_5}
	};
	// 右ボタン(小さいやつ)
	inputTable_["Pad_6"] =
	{
		{PeripheralType::pad1, PAD_INPUT_6}
	};
	// BACKボタン
	inputTable_["Pad_7"] =
	{
		{PeripheralType::pad1, PAD_INPUT_7}
	};
	// STARTボタン
	inputTable_["Pad_8"] =
	{
		{PeripheralType::pad1, PAD_INPUT_8}
	};
	// 左スティック押しこみ
	inputTable_["Pad_9"] =
	{
		{PeripheralType::pad1, PAD_INPUT_9}
	};
	// 右スティック押しこみ
	inputTable_["Pad_10"] =
	{
		{PeripheralType::pad1, PAD_INPUT_10}
	};
#endif
}


void Input::SetTempDefault()
{
	tempInputTable_["next"] =
	{
		{PeripheralType::keybd, KEY_INPUT_RETURN},
		{PeripheralType::pad1, PAD_INPUT_1} // A
	};
	tempInputTable_["pause"] =
	{
		{PeripheralType::keybd, KEY_INPUT_P},
		{PeripheralType::pad1, PAD_INPUT_8} // START
	};
}


void Input::CommitEdittedInputTable()
{
	inputTable_ = tempInputTable_;
}

void Input::RollbackEdittedInputTable()
{
	tempInputTable_ = inputTable_;
}

int Input::GetLastKeyboadState()
{
	for (int i = 0; i < _countof(currentRawKeybdState_); ++i)
	{
		if (currentRawKeybdState_[i] && !lastRawKeybdState_[i])
		{
			return i;
		}
	}
	return -1;
}

int Input::GetLastPadState()
{
	uint32_t bit = 1;
	for (int i = 0; i < 32; ++i)
	{
		int inputId = bit << i;
		if ((inputId & currentRawPadState_) && !(inputId & lastRawPadState_))
		{
			return inputId;
		}
	}

	return -1;
}

void Input::SaveInputTable()
{
	FILE* fp = nullptr;
	fopen_s(&fp, key_config_filemane, "wb"); // バイナリで書き込み用に開く
	// シグネチャ
	std::string signature = key_config_signature;
	fwrite(signature.data(), signature.size(), 1, fp);
	// バージョン
	float version = 1.0f;
	fwrite(&version, sizeof(version), 1, fp);
	// データサイズ
	size_t size = inputTable_.size();
	fwrite(&size, sizeof(size), 1, fp);
	// データ
	for (const auto& record : inputTable_)
	{
		// キーの書き込み
		byte nameSize = static_cast<byte>(record.first.length());
		fwrite(&nameSize, sizeof(nameSize), 1, fp);
		fwrite(record.first.data(), record.first.size(), 1, fp);
		// 値(InputState)の書き込み
		// まず要素数の記録
		byte inputDataSize = static_cast<byte>(record.second.size());
		fwrite(&inputDataSize, sizeof(inputDataSize), 1, fp);
		// InputStateのサイズは8バイトなので、8*要素数書き込めばいい
		fwrite(record.second.data(), // 書き込む実データの先頭アドレス
			sizeof(record.second[0]), // 書き込むデータのサイズ
			record.second.size(), // 書き込むデータ数
			fp);
	}

	fclose(fp);
}

void Input::LoadInputTable()
{
	std::string filename = key_config_filemane;

	int handle = FileRead_open(filename.c_str());
	assert(handle && "キー設定の読み込みに失敗しました");

	struct Header
	{
		char signature[4]; // シグネチャ
		float varsion; // バージョン
		size_t dataNum; // データ数
	};
	Header header = {}; // ヘッダーの読み込み
	FileRead_read(&header, sizeof(header), handle);

	// データの数だけ読んでいく
	for (int i = 0; i < header.dataNum; ++i)
	{
		// データはまず、イベント名を読み込む
		byte nameSize = 0;
		FileRead_read(&nameSize, sizeof(nameSize), handle);
		// キー名を取得
		std::string strEventName;
		strEventName.resize(nameSize);
		FileRead_read(strEventName.data(), nameSize * sizeof(char), handle);
		// 実データ
		byte inputDataNum = 0;
		FileRead_read(&inputDataNum, sizeof(inputDataNum), handle);
		std::vector<InputState> inputStates;
		inputStates.resize(inputDataNum);
		// これListじゃできないんだろうな
		FileRead_read(inputStates.data(), sizeof(inputStates[0]) * inputDataNum, handle);
		inputTable_[strEventName] = inputStates;
	}

	// tempにも反映
	tempInputTable_ = inputTable_;

	FileRead_close(handle);
}

// カッコに何も入ってないときは0で初期化されてる
Input::Input()
{
	// 入力と名前の対応表を作る
	SetDefault();

	//LoadInputTable();

	// キーコンフィグに出てくる順番を示す
	// キーコンされていいやつだけ書く
	orderForDisplay =
	{
		"ok",
		"next",
		"action",
		"jump",
	};
}

void Input::Update()
{
	// 前回のフレームの入力を取っておく
	last_ = current_;

	std::copy(std::begin(currentRawKeybdState_), std::end(currentRawKeybdState_), std::begin(lastRawKeybdState_));
	currentRawPadState_ = GetJoypadInputState(DX_INPUT_PAD1);
	// 入力をとる
	GetHitKeyStateAll(currentRawKeybdState_);
	// テーブルに記憶されたすべての入力をチェックする
	for (const auto& keyValue : inputTable_)
	{
		// 出てきたキーイベントに対し、
		const auto& key = keyValue.first;
		current_[key] = false;
		// それぞれの入力形式でチェックする
		for (const auto& input : keyValue.second)
		{
			switch (input.type)
			{
			case PeripheralType::keybd:
				current_[keyValue.first] = current_[key] || currentRawKeybdState_[input.id];
				break;
			case PeripheralType::pad1:
				current_[keyValue.first] = current_[key] || (input.id & currentRawPadState_);
				break;
			default:
				break;
			}
		}
	}
}

bool Input::IsTrigger(std::string key) const
{
	// idが前回押されていなくて、現在押されている時にtrueを返す
	// []演算子ではなく、at(key)を使うこと！！！！！
	return (current_.at(key) && !last_.at(key));
}

bool Input::IsPressed(const char* key) const
{
	// 今回押された入力しか見ない
	return current_.at(key);
}
