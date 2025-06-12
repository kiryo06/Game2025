#include "Application.h"
#include "Input.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "SceneController.h"
#include "GameScene.h"
#include <cassert>

namespace
{
	constexpr int fade_interval = 60; // �t�F�[�h�C���E�A�E�g�̃t���[����
}

void GameScene::FadeInUpdate(Input& input)
{
	--m_frameCount;
	// �g���K�[
	if (m_frameCount <= 0)
	{
		pUpdateFunc = &GameScene::NormalUpdate;
		pDrawFunc = &GameScene::NormalDraw;
	}
}

void GameScene::FadeOutUpdate(Input& input)
{
	++m_frameCount;
	// ���̌��scene�J�ڂ�������
	if (m_frameCount >= fade_interval)
	{
		 controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		// �����ŃQ�[���V�[���͏�����
		// ���̌�̏����͕s�v
		return;
	}
	// ������������return���Ȃ���΁����낢��܂������ƂɂȂ�
}

void GameScene::NormalUpdate(Input& input)
{
	// �L�[���������܂ŉ������Ȃ�
	if (input.IsTrigger("next"))
	{
		pUpdateFunc = &GameScene::FadeOutUpdate;
		pDrawFunc = &GameScene::FadeDraw;
	}
}

void GameScene::FadeDraw()
{
	// �摜�̒��S���o������
	const Size& wSize = Application::GetInstance().GetWindowSize();

	// ���Ȃ��ݓ��ߕ`��������Ŏ�������
	// �܂��t�F�[�h�����̌v�Z
	float rate = static_cast<float>(m_frameCount) / static_cast<float>(fade_interval);
	// ���̏������Ȃ�����̃p�����[�^��0~1�ɂł���炵��
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(255 * rate));
	DrawBox(0, 0, wSize.w, wSize.h, 0x000000, true);
	// BlendMode���g�p�������Noblend��Y��Ȃ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::NormalDraw()
{
	// �����`�悵�Ȃ�
	// �Q�[���V�[���ł͉����`�悵�Ȃ�
	// �������A�Q�[���̓��e��`�悷��ꍇ�͂����ɏ���
	DrawString(10, 10, "GameScene", 0xffffff);
}

GameScene::GameScene(SceneController& controller)
	: Scene(controller),
	m_frameCount(fade_interval),
	pUpdateFunc(&GameScene::FadeInUpdate), // �����̓t�F�[�h�C��
	pDrawFunc(&GameScene::FadeDraw) // �����̓t�F�[�h�`��
{
	// �Q�[���V�[���̏���������
	// �����ł͓��ɉ������Ȃ�
	// �K�v�Ȃ�΁A�����ŃQ�[���̏��������s��
}

void GameScene::Init()
{
	// �Q�[���V�[���̏���������
	// �����ł͓��ɉ������Ȃ�
	// �K�v�Ȃ�΁A�����ŃQ�[���̏��������s��
	m_frameCount = fade_interval; // �t�F�[�h�C���̃t���[���������Z�b�g
	pUpdateFunc = &GameScene::FadeInUpdate; // �����̓t�F�[�h�C��
	pDrawFunc = &GameScene::FadeDraw; // �����̓t�F�[�h�`��
}

void GameScene::Update(Input& input)
{
	// Update�֐��̓|�C���^���g���ē��I�ɕύX�����
	(this->*pUpdateFunc)(input);
}

void GameScene::Draw()
{
	// Draw�֐��̓|�C���^���g���ē��I�ɕύX�����
	(this->*pDrawFunc)();
}
