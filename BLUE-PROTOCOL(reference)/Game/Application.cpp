#include "Application.h"
#include "DxLib.h"
#include "game.h"
#include "Input.h"
#include "SceneController.h"
#include <cassert>
#include <string>

Application::Application():
	windowSize_{ Game::kScreenWidth, Game::kScreenHeight }// �����E�B���h�E�T�C�Y��ݒ�
{
}

Application& Application::GetInstance()
{
	// ���̎��_�Ń��������m��
	static Application app;
	return app;
}

bool Application::Init()
{

	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	// �����������֐��́A�E�B���h�E���J���O�ɏ������Ă���
	ChangeWindowMode(Game::kDefaultWindowMode);

	// ��ʂ̃T�C�Y��ύX����
	// ��O�����͐F�Ɏg������(�r�b�g)
	SetGraphMode(windowSize_.w, windowSize_.h, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return false;			// �G���[���N�����璼���ɏI��
	}

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void Application::Run()
{
	SceneController sceneController;
	sceneController.Init();
	Input input;
	constexpr uint64_t frame_milliseconds = 16;
//	auto lastTime = 0;
	// �O�t���[���̎��Ԃ�ێ�����ϐ�
	long long lastTime = 0;
	// �Q�[�����[�v
	while (ProcessMessage() == 0) // Windows���s���������󂯎��֐���While�̃��[�v���Ƃɑ��点�Ă���B
		// ����While���̓t���[���̏������s���Ă��邩�疈�t���[�����点�Ă��邱�ƂɂȂ�B
		// ���̖߂�l��While�̔���B�ُ�(���E�B���h�E������ꂽ��)���o���烋�[�v�𔲂��ăv���O�����I���B
	{
		// �t���[���J�n�̎���
		LONGLONG startTime = GetNowHiPerformanceCount();
		// ���݂̎��Ԃ��}�C�N���b�P�ʂŎ擾
		long long currentTime = GetNowHiPerformanceCount();
		// lastTime������(0)�łȂ���΁A�o�ߎ��Ԃ��v�Z
		float deltaTime = 0.0f;
		if (lastTime != 0)
		{
			// (���݂̎��� - �O�t���[���̎���) / 1,000,000.0f �ŕb�P�ʂɕϊ�
			deltaTime = (currentTime - lastTime) / 1000000.0f;
		}
		// ���݂̎��Ԃ����̃t���[���̂��߂ɕۑ�
		lastTime = currentTime;
		// ��ʑS�̂��N���A����
		ClearDrawScreen();


		input.Update();
		// �����ɃQ�[���̏���������
		sceneController.Update(input,deltaTime);
		sceneController.Draw();

		DrawFormatString(0, 0, 0xffffff, "fps = %2.2f", GetFPS());

		// ��ʂ̐؂�ւ���҂�
		ScreenFlip();
		// �҂����s��
		while (GetNowHiPerformanceCount() - startTime < 16667);
	}
}

void Application::Terminate()
{
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
}

const Size& Application::GetWindowSize() const
{
	return windowSize_;
}
