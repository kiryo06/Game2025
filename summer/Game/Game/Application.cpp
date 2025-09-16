#include "Application.h"
#include "DxLib.h"
#include "game.h"
#include "Input.h"
#include "SceneController.h"
#include <cassert>
#include <string>

Application::Application():
	windowSize_{ Game::kScreenWidth, Game::kScreenHeight }// 初期ウィンドウサイズを設定
{
}

Application& Application::GetInstance()
{
	// この時点でメモリを確保
	static Application app;
	return app;
}

bool Application::Init()
{

	// TODO: return ステートメントをここに挿入します
	// こういった関数は、ウィンドウが開く前に処理しておく
	ChangeWindowMode(Game::kDefaultWindowMode);

	// 画面のサイズを変更する
	// 第三引数は色に使う情報量(ビット)
	SetGraphMode(windowSize_.w, windowSize_.h, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return false;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void Application::Run()
{
	SceneController sceneController;
	sceneController.Init();
	Input input;
	constexpr uint64_t frame_milliseconds = 16;
//	auto lastTime = 0;
	// 前フレームの時間を保持する変数
	long long lastTime = 0;
	// ゲームループ
	while (ProcessMessage() == 0) // Windowsが行う処理を受け取る関数をWhileのループごとに走らせている。
		// このWhile文はフレームの処理を行っているから毎フレーム走らせていることになる。
		// その戻り値でWhileの判定。異常(大抵ウィンドウが閉じられた時)が出たらループを抜けてプログラム終了。
	{
		// フレーム開始の時間
		LONGLONG startTime = GetNowHiPerformanceCount();
		// 現在の時間をマイクロ秒単位で取得
		long long currentTime = GetNowHiPerformanceCount();
		// lastTimeが初回(0)でなければ、経過時間を計算
		float deltaTime = 0.0f;
		if (lastTime != 0)
		{
			// (現在の時間 - 前フレームの時間) / 1,000,000.0f で秒単位に変換
			deltaTime = (currentTime - lastTime) / 1000000.0f;
		}
		// 現在の時間を次のフレームのために保存
		lastTime = currentTime;
		// 画面全体をクリアする
		ClearDrawScreen();


		input.Update();
		// ここにゲームの処理を書く
		sceneController.Update(input,deltaTime);
		sceneController.Draw();

		DrawFormatString(0, 0, 0xffffff, "fps = %2.2f", GetFPS());

		// 画面の切り替わりを待つ
		ScreenFlip();
		// 待ちを行う
		while (GetNowHiPerformanceCount() - startTime < 16667);
	}
}

void Application::Terminate()
{
	DxLib_End();				// ＤＸライブラリ使用の終了処理
}

const Size& Application::GetWindowSize() const
{
	return windowSize_;
}
