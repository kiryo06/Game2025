#pragma once
#include "BaseScene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public BaseScene
{
private:
	int m_frameCount = 0; // フレームカウント
	int m_background = -1; // 背景画像のハンドル

	using UpdateFunc = void (TitleScene::*)(Input&);
	using DrawFunc = void (TitleScene::*)();

	UpdateFunc pUpdateFunc; // 更新処理の関数ポインタ
	DrawFunc pDrawFunc; // 描画処理の関数ポインタ

	// フェードイン時のUpdate関数
	void FadeInUpdate(Input& input);
	// フェードアウト時のUpdate関数
	void FadeOutUpdate(Input& input);
	// そうでないときのUpdate関数
	void NormalUpdate(Input& input);

	// 描画
	void FadeDraw();
	void NormalDraw();

public:
	TitleScene(SceneController& controller);

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 派生クラスで実装を実装
	/// virtual はこれを継承するかもしれないから、
	/// overrideは明示的にオーバーライドをエディタに示すため
	/// </summary>
	void Update(Input& input) override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

