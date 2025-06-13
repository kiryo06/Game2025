#pragma once
#include "BaseScene.h"
#include <memory>

class Player;
//class Enemy;
class Camera;
class Debug;
class GameScene : public BaseScene
{
private:
	int m_frameCount = 0; // フレームカウント

	std::shared_ptr<Player> m_pPlayer;
//	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Debug> m_pDebug;

	using UpdateFunc = void (GameScene::*)(Input&);
	using DrawFunc = void (GameScene::*)();

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
	GameScene(SceneController& controller);

	/// <summary>
	/// 
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

