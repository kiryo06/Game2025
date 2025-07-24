#pragma once

// ゲームの状態を管理するクラス

namespace Game
{
	// 定数にはkを先頭につける
	// m,s,kなどなど
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 640;

	constexpr int kColorBitNum = 32;

	constexpr bool kDefaultWindowMode = true; // ウィンドウモードで起動する
}