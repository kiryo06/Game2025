#include "Scene.h"

// 基底クラスでシーンコントローラーを持たせておく
Scene::Scene(SceneController& controller)
	: controller_(controller)
{
}