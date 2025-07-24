#include "Application.h"
#include "Input.h"
#include "DxLib.h"
#include "GameScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include <cassert>

namespace
{
	constexpr int fade_interval = 60;
}

void TitleScene::Init()
{
	// ����������
	// �����ł͓��ɉ������Ȃ�
	// �������A�K�v�ȏ�����������΂����ɏ���
	m_frameCount = fade_interval;
	pUpdateFunc = &TitleScene::FadeInUpdate;
	pDrawFunc = &TitleScene::FadeDraw;
}

void TitleScene::End()
{
}

void TitleScene::Update(Input& input,float deltaTime)
{
	(this->*pUpdateFunc)(input);
}

void TitleScene::Draw()
{
	// �摜�̒��S���o������
	const Size& wSize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wSize.w) * 0.5f, static_cast<float>(wSize.h) * 0.5f };
	// �w�i�̕\��
//	DrawRotaGraph(static_cast<int>(center.x), static_cast<int>(center.y), 1.0, 0.0f, m_background, true);
	// ���s
	// ����͉�ʌ��ʂƂ��̕`��Ɏg�����炢������
	(this->*pDrawFunc) ();
}

void TitleScene::FadeInUpdate(Input& input)
{
	--m_frameCount;
	// �g���K�[
	if (m_frameCount <= 0)
	{
		pUpdateFunc = &TitleScene::NormalUpdate;
		pDrawFunc = &TitleScene::NormalDraw;
	}
}

void TitleScene::FadeOutUpdate(Input& input)
{
	++m_frameCount;

	// ���̌��scene�J�ڂ�������
	if (m_frameCount >= 60)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_));
		// �����Ń^�C�g���V�[���͏�����
		// ���̌�̏����͕s�v
		return;
	}
	// ������������return���Ȃ���΁����낢��܂������ƂɂȂ�
}

void TitleScene::NormalUpdate(Input& input)
{
	// �L�[���������܂ŉ������Ȃ�
	if (input.IsTrigger("next")|| input.IsTrigger("START"))
	{
		pUpdateFunc = &TitleScene::FadeOutUpdate;
		pDrawFunc = &TitleScene::FadeDraw;
	}
}

void TitleScene::FadeDraw()
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

void TitleScene::NormalDraw()
{
	DrawString(10, 10, "Title Scene", 0xffffff);
}

TitleScene::TitleScene(SceneController& controller):
	BaseScene(controller),
	pUpdateFunc(&TitleScene::FadeInUpdate),
	pDrawFunc(&TitleScene::FadeDraw),
	m_frameCount(fade_interval)
{
	// ���[�h
	m_background = LoadGraph("image/Title.png");
	assert(m_background != -1);
}
