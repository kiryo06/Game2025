#include "Application.h"
#include "Input.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "SceneController.h"
#include "GameScene.h"
#include <cassert>
#include "Player.h"
//#include "Enemy.h"
#include "Camera.h"
#include "Debug.h"

namespace
{
	constexpr int fade_interval = 60; // フェードイン・アウトのフレーム数
}

void GameScene::FadeInUpdate(Input& input)
{
	--m_frameCount;
	// トリガー
	if (m_frameCount <= 0)
	{
		pUpdateFunc = &GameScene::NormalUpdate;
		pDrawFunc = &GameScene::NormalDraw;
	}
}

void GameScene::FadeOutUpdate(Input& input)
{
	++m_frameCount;
	// この後にscene遷移がしたい
	if (m_frameCount >= fade_interval)
	{
		 controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		// ここでゲームシーンは消える
		// この後の処理は不要
		return;
	}
	// 何かあった時returnがなければ←いろいろまずいことになる
}

void GameScene::NormalUpdate(Input& input)
{
	// キーが押されるまで何もしない
	if (input.IsTrigger("next"))
	{
		pUpdateFunc = &GameScene::FadeOutUpdate;
		pDrawFunc = &GameScene::FadeDraw;
	}
}

void GameScene::FadeDraw()
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

void GameScene::NormalDraw()
{
	// 何も描画しない
	// ゲームシーンでは何も描画しない
	// ただし、ゲームの内容を描画する場合はここに書く
	DrawString(10, 10, "GameScene", 0xffffff);
}

GameScene::GameScene(SceneController& controller)
	: BaseScene(controller),
	m_frameCount(fade_interval), // フレームカウントをフェードインのフレーム数で初期化
	pUpdateFunc(&GameScene::FadeInUpdate), // 初期はフェードイン
	pDrawFunc(&GameScene::FadeDraw)// 初期はフェード描画
{
	// ゲームシーンの初期化処理
	// ここでは特に何もしない
	// 必要ならば、ここでゲームの初期化を行う
}

void GameScene::Init()
{
	// ゲームシーンの初期化処理
	m_frameCount = fade_interval; // フェードインのフレーム数をリセット
	pUpdateFunc = &GameScene::FadeInUpdate; // 初期はフェードイン
	pDrawFunc = &GameScene::FadeDraw; // 初期はフェード描画
	m_pPlayer = std::make_shared<Player>();
//	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();


#ifdef _DEBUG
	// デバッグ情報の初期化
	m_pDebug = std::make_shared<Debug>();
	m_pDebug->Init();
#endif // _DEBUG

}

void GameScene::Update(Input& input)
{
	// Update関数はポインタを使って動的に変更される
	(this->*pUpdateFunc)(input);



#ifdef _DEBUG
	m_pDebug->Update();
#endif // _DEBUG

}

void GameScene::Draw()
{
	// Draw関数はポインタを使って動的に変更される
	(this->*pDrawFunc)();



#ifdef _DEBUG
	m_pDebug->Draw(); // デバッグ情報の描画
#endif // _DEBUG

}
