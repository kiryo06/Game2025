#pragma once

class Input;
class SceneController;

/// <summary>
/// 各シーンの基底クラス
/// </summary>
class BaseScene
{
protected:
	// 各状態が切り替わるために
	SceneController& controller_;
public:
	BaseScene(SceneController& controller);

	virtual void Init() = 0;

	virtual void End() = 0;

	/// <summary>
	/// 内部変数の更新
	/// </summary>
	/// <param name="input">入力状態</param>
	virtual void Update(Input& input,float deltaTime) = 0;

	/// <summary>
	///  描画
	/// </summary>
	virtual void Draw() = 0;
};

