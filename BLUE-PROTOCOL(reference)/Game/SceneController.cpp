#include "SceneController.h"
#include <memory>
// �p�����̊֐����F�����Ă����!!
#include "TitleScene.h"
#include "cassert"

SceneController::SceneController()
{
	// �����̃V�[����ݒ肷��ꍇ�͂����ōs��
	// ��: ChangeBaseScene(std::make_shared<TitleScene>());
	ChangeScene(std::make_shared<TitleScene>(*this));
	// �������Ascene�̏�������SceneController�̊O�ōs�����Ƃ������̂ł����ł͓��ɉ������Ȃ��Ă���
}

void SceneController::Update(Input& input)
{
	// ��ԏ�ɂ���V�[����Update���Ăяo��
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
	// �X�}�[�g�|�C���^�[�Ȃ̂ł���ł���
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		// �����̗v�f�̎Q��
		scenes_.back() = scene;
	}
	// ���O�̃I�u�W�F�N�g�͎Q�Ƃ������̂ŏ��������
}

void SceneController::PushScene(std::shared_ptr<BaseScene> scene)
{
	// �V�����V�[������ԏ�ɒǉ�����
	scenes_.push_back(scene);
	// �����ł̓V�[���̐؂�ւ����s��Ȃ�
	// �V�[���̐؂�ւ��͊e�V�[���̑J�ڂōs��
	// �������ASceneController�̓V�[���̃|�C���^���󂯎�邱�Ƃ��ł���
	// ���̂��߁A�V�[���̐؂�ւ���SceneController���s�����Ƃ�����
}

void SceneController::PopScene()
{
	// ���s���ׂ��V�[�����Ȃ��Ȃ�̂ŋ����Ȃ�
	if (scenes_.size() == 1) return;

	// ��������菜��
	scenes_.pop_back();
}
