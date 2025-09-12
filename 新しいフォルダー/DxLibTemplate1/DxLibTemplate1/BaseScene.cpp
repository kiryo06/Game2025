#include "BaseScene.h"

// 基底クラスでシーンコントローラーを持たせておく
BaseScene::BaseScene(SceneController& controller)
	: controller_(controller)
{
}