#include "SceneController.h"
#include <memory>
#include "TitleScene.h"
#include "cassert"

SceneController::SceneController()
{
	// 初期のシーンを設定する場合はここで行う
	// 例: ChangeBaseScene(std::make_shared<TitleScene>());
	ChangeScene(std::make_shared<TitleScene>(*this));
	// ただし、sceneの初期化はSceneControllerの外で行うことが多いのでここでは特に何もしない
}

void SceneController::Init()  
{  

}

void SceneController::Update(Input& input, float deltaTime)
{
	// 一番上にあるシーンのUpdateを呼び出す
	_scenes.back()->Update(input, deltaTime);
}

void SceneController::Draw()
{
	for (auto& scene : _scenes)
	{
		scene->Draw();
	}
}

void SceneController::ChangeScene(std::shared_ptr<BaseScene> scene)
{
	// スマートポインター
	if (_scenes.empty())
	{
		_scenes.push_back(scene);
	}
	else
	{
		// 末尾の要素の参照
		_scenes.back() = scene;
	}
	_scenes.back()->Init();
	// ↑前のオブジェクトは参照を失うので消去される
}

void SceneController::PushScene(std::shared_ptr<BaseScene> scene)
{
	// 新しいシーンを一番上に追加する
	_scenes.push_back(scene);
	// ここではシーンの切り替えを行わない
	// シーンの切り替えは各シーンの遷移で行う
	// ただし、SceneControllerはシーンのポインタを受け取ることができる
	// そのため、シーンの切り替えはSceneControllerが行うこともある
}

void SceneController::PopScene()
{
	// 実行すべきシーンがなくなるので許可しない
	if (_scenes.size() == 1) return;

	// 末尾を取り除く
	_scenes.pop_back();
}
