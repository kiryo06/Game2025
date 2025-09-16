#include "Application.h"
#include "Input.h"
#include "DxLib.h"
#include "GameScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include <cassert>

namespace
{
	constexpr int fade_interval = 60;
}

void TitleScene::Init()
{
	// 初期化処理
	// ここでは特に何もしない
	// ただし、必要な初期化があればここに書く
	m_frameCount = fade_interval;
	pUpdateFunc = &TitleScene::FadeInUpdate;
	pDrawFunc = &TitleScene::FadeDraw;
}

void TitleScene::End()
{
}

void TitleScene::Update(Input& input,float deltaTime)
{
	(this->*pUpdateFunc)(input);
}

void TitleScene::Draw()
{
	// 画像の中心を出すだけ
	const Size& wSize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wSize.w) * 0.5f, static_cast<float>(wSize.h) * 0.5f };
	// 背景の表示
//	DrawRotaGraph(static_cast<int>(center.x), static_cast<int>(center.y), 1.0, 0.0f, m_background, true);
	// 実行
	// これは画面効果とかの描画に使ったらいいかも
	(this->*pDrawFunc) ();
}

void TitleScene::FadeInUpdate(Input& input)
{
	--m_frameCount;
	// トリガー
	if (m_frameCount <= 0)
	{
		pUpdateFunc = &TitleScene::NormalUpdate;
		pDrawFunc = &TitleScene::NormalDraw;
	}
}

void TitleScene::FadeOutUpdate(Input& input)
{
	++m_frameCount;

	// この後にscene遷移がしたい
	if (m_frameCount >= 60)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_));
		// ここでタイトルシーンは消える
		// この後の処理は不要
		return;
	}
	// 何かあった時returnがなければ←いろいろまずいことになる
}

void TitleScene::NormalUpdate(Input& input)
{
	// キーが押されるまで何もしない
	if (input.IsTrigger("next")|| input.IsTrigger("START"))
	{
		pUpdateFunc = &TitleScene::FadeOutUpdate;
		pDrawFunc = &TitleScene::FadeDraw;
	}
}

void TitleScene::FadeDraw()
{
	// 画像の中心を出すだけ
	const Size& wSize = Application::GetInstance().GetWindowSize();

	// おなじみ透過描画を高速で実装する
	// まずフェード割合の計算
	float rate = static_cast<float>(m_frameCount) / static_cast<float>(fade_interval);
	// この書き方なら引数のパラメータを0~1にできるらしい
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(255 * rate));
	DrawBox(0, 0, wSize.w, wSize.h, 0x000000, true);
	// BlendModeを使用した後はNoblendを忘れない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(10, 10, "Title Scene", 0xffffff);
}

TitleScene::TitleScene(SceneController& controller):
	BaseScene(controller),
	pUpdateFunc(&TitleScene::FadeInUpdate),
	pDrawFunc(&TitleScene::FadeDraw),
	m_frameCount(fade_interval)
{
	// ロード
	m_background = LoadGraph("image/Title.png");
	assert(m_background != -1);
}
