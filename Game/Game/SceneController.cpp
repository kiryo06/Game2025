#include "SceneController.h"
#include <memory>
#include "TitleScene.h"
#include "cassert"

SceneController::SceneController()
{
	// �����̃V�[����ݒ肷��ꍇ�͂����ōs��
	// ��: ChangeBaseScene(std::make_shared<TitleScene>());
	ChangeScene(std::make_shared<TitleScene>(*this));
	// �������Ascene�̏�������SceneController�̊O�ōs�����Ƃ������̂ł����ł͓��ɉ������Ȃ�
}

void SceneController::Init()  
{  

}

void SceneController::Update(Input& input, float deltaTime)
{
	// ��ԏ�ɂ���V�[����Update���Ăяo��
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
	// �X�}�[�g�|�C���^�[
	if (_scenes.empty())
	{
		_scenes.push_back(scene);
	}
	else
	{
		// �����̗v�f�̎Q��
		_scenes.back() = scene;
	}
	_scenes.back()->Init();
	// ���O�̃I�u�W�F�N�g�͎Q�Ƃ������̂ŏ��������
}

void SceneController::PushScene(std::shared_ptr<BaseScene> scene)
{
	// �V�����V�[������ԏ�ɒǉ�����
	_scenes.push_back(scene);
	// �����ł̓V�[���̐؂�ւ����s��Ȃ�
	// �V�[���̐؂�ւ��͊e�V�[���̑J�ڂōs��
	// �������ASceneController�̓V�[���̃|�C���^���󂯎�邱�Ƃ��ł���
	// ���̂��߁A�V�[���̐؂�ւ���SceneController���s�����Ƃ�����
}

void SceneController::PopScene()
{
	// ���s���ׂ��V�[�����Ȃ��Ȃ�̂ŋ����Ȃ�
	if (_scenes.size() == 1) return;

	// ��������菜��
	_scenes.pop_back();
}
