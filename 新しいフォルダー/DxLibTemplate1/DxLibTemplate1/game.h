#pragma once
// ゲームの状態を管理するクラス

namespace Game
{
	// 定数にはkを先頭につける
	// m,s,kなどなど
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 640;

	constexpr int kColorBitNum = 32;

#ifdef _DEBUG
	constexpr bool kDefaultWindowMode = true; // ウィンドウモードで起動する
#else
	constexpr bool kDefaultWindowMode = false; // ウィンドウモードで起動する
#endif // _DEBUG
}