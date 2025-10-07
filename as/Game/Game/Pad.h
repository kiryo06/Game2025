#pragma once
#include "Vec2.h"

// コントローラーの入力状態を取得する
namespace Pad
{
	// パットの入力状態を取得する
	void Update();

	// 押し下げ判定
	bool isPress(int button);
	// トリガー判定
	bool isTrigger(int button);
	// 離した判定
	bool isRelase(int button);

	bool isInputPadA();

	// 左スティック
	Vec2 GetLeftStick();
	// 右スティック
	Vec2 GetRightStick();
};

