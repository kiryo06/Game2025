#include "SceneController.h"
#include <memory>
// 継承元の関数も認識してくれる!!
#include "TitleScene.h"
#include "cassert"

SceneController::SceneController()
{
	// 初期のシーンを設定する場合はここで行う
	// 例: ChangeBaseScene(std::make_shared<TitleScene>());
	ChangeScene(std::make_shared<TitleScene>(*this));
	// ただし、sceneの初期化はSceneControllerの外で行うことが多いのでここでは特に何もしなくていい
}

void SceneController::Update(Input& input)
{
	// 一番上にあるシーンのUpdateを呼び出す
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}

void SceneController::ChangeScene(std::shared_ptr<BaseScene> scene)
{
	// スマートポインターなのでこれでいい
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		// 末尾の要素の参照
		scenes_.back() = scene;
	}
	// ↑前のオブジェクトは参照を失うので消去される
}

void SceneController::PushScene(std::shared_ptr<BaseScene> scene)
{
	// 新しいシーンを一番上に追加する
	scenes_.push_back(scene);
	// ここではシーンの切り替えを行わない
	// シーンの切り替えは各シーンの遷移で行う
	// ただし、SceneControllerはシーンのポインタを受け取ることができる
	// そのため、シーンの切り替えはSceneControllerが行うこともある
}

void SceneController::PopScene()
{
	// 実行すべきシーンがなくなるので許可しない
	if (scenes_.size() == 1) return;

	// 末尾を取り除く
	scenes_.pop_back();
}
