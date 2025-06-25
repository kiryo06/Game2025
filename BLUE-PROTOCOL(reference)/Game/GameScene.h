#pragma once
#include "BaseScene.h"
#include <memory>

class Player;
//class Enemy;
class Camera;
class Debug;
class Test;
class GameScene : public BaseScene
{
public:
	GameScene(SceneController& controller);

	/// <summary>
	/// 
	/// </summary>
	void Init() override;
	/// <summary>
	/// 
	/// </summary>
	void End() override;
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
private:
	int m_frameCount = 0;	// フレームカウント
	int m_playerHandle;		// プレイヤーのモデル
//	int m_enemyHandle;		// 敵のモデル


	std::shared_ptr<Player> m_pPlayer;
//	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Debug> m_pDebug;
	std::shared_ptr<Test> m_pTest;

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
};

