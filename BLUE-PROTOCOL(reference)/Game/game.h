#pragma once

// ゲームの状態を管理するクラス

namespace Game
{
	// 定数にはkを先頭につける
	// m,s,kなどなど
//	constexpr int kScreenWidth = 1660;
//	constexpr int kScreenHeight = 720;
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;

	constexpr int kColorBitNum = 32;

	constexpr bool kDefaultWindowMode = true; // ウィンドウモードで起動する
}