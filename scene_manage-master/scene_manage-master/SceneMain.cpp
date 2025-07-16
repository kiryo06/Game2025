#include "SceneMain.h"
#include "DxLib.h"

void SceneMain::init()
{
	// 以降のファイルの読み込みが非同期化される
	SetUseASyncLoadFlag(true);
	// 読み込み
	for (auto& handle : m_handle)
	{
		handle = LoadGraph("dummy000.bmp");
	}
	// デフォルトの設定にもどしておく
	SetUseASyncLoadFlag(false);
	m_textPosX = 0;
	m_textVecX = 4;

	m_isEnd = false;
}

void SceneMain::update()
{
	// 非同期読み込みを1つ以上行っている場合はupdate処理を行わない
	if (GetASyncLoadNum() > 0)
	{
		// グラフィックを使った処理が行われている可能性があるので
		// 最初にチェックしてロードが終わっていなければここでupdate終了
		return;
	}


	// 文字の移動
	m_textPosX += m_textVecX;
	if (m_textPosX < 0)
	{
		m_textPosX = 0;
		m_textVecX = 4;
	}
	if (m_textPosX > 300)
	{
		m_textPosX = 300;
		m_textVecX = -4;
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_2)
	{
		m_isEnd = true;
	}
}

void SceneMain::draw()
{
	// 非同期読み込みが終わるまではdrawの処理を行わない
	if (GetASyncLoadNum() > 0)
	{
		// 現在何パーセントロードが完了しているかを表示する
		// ファイルの数しか見ていないので(サイズを見ていない)時間がかかる部分とかからない部分がある
		// ので実際の時間とはずれる場合がある
		int total = _countof(m_handle);	// 読み込むファイルの総数
		int now = total - GetASyncLoadNum();
		float rate = static_cast<float>(now) / total;
		DrawFormatString(0, 0, 0xffffff, "ロード中...　%.1f%%", rate * 100);
		return;
	}
	DrawGraph(0, 0, m_handle[2047], true);
	DrawString(m_textPosX, 0,"メイン画面",GetColor(255,255,255));
}