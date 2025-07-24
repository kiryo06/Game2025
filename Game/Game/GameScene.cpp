#include "Application.h"
#include "Input.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "SceneController.h"
#include "GameScene.h"
#include <cassert>
#include "Player.h"
#include "Boss.h"
#include "Camera.h"
#include "Debug.h"
#include "Test.h"

namespace
{
	constexpr int fade_interval = 60; // �t�F�[�h�C���E�A�E�g�̃t���[����
}

void GameScene::Init()
{
	// �Q�[���V�[���̏���������
	m_frameCount = fade_interval; // �t�F�[�h�C���̃t���[���������Z�b�g
	pUpdateFunc = &GameScene::FadeInUpdate; // �����̓t�F�[�h�C��
	pDrawFunc = &GameScene::FadeDraw; // �����̓t�F�[�h�`��
	
	m_playerHandle = MV1LoadModel("data/model/player.mv1");
	m_bossHandle = MV1LoadModel("data/model/Boss/boss.mv1");
//	m_fieldHandle = MV1LoadModel("data/model/field.mv1");
	
	// �J�����̏�����
	m_pCamera = std::make_shared<Camera>();
	// �v���C���[�̏�����
	m_pPlayer = std::make_shared<Player>();
	// �{�X�̏�����
	m_pBoss = std::make_shared<Boss>();

	m_pPlayer->SetModel(m_playerHandle);
	m_pBoss->SetModel(m_bossHandle);

	m_pCamera->Init();
	m_pPlayer->Init();
	m_pBoss->Init();



#ifdef _DEBUG
	// �f�o�b�O���̏�����
	m_pDebug = std::make_shared<Debug>();
	m_pDebug->Init();


	// ���Ɨp
	m_pTest = std::make_shared<Test>();
	m_pTest->Init();
#endif // _DEBUG

}

void GameScene::End()
{
	// ���f���̉��
	MV1DeleteModel(m_playerHandle);
//	MV1DeleteModel(m_enemyHandle);
//	MV1DeleteModel(m_fieldHandle);
}

void GameScene::Update(Input& input, float deltaTime)
{
	m_pCamera->Update(m_pPlayer.get());
	m_pPlayer->Update(input, m_pCamera.get(),deltaTime);
	m_pBoss->Update(m_pPlayer.get());



#ifdef _DEBUG
	m_pDebug->Update(input);
//	m_pTest->Update();
#endif // _DEBUG
	// Update�֐��̓|�C���^���g���ē��I�ɕύX�����
	(this->*pUpdateFunc)(input);
}

void GameScene::Draw()
{
	m_pCamera->Draw();
	m_pPlayer->Draw();
	m_pBoss->Draw();

#ifdef _DEBUG
	m_pDebug->Draw(); // �f�o�b�O���̕`��
	m_pTest->Draw();
	m_pBoss->DebugFormatDraw();
#endif // _DEBUG

	// Draw�֐��̓|�C���^���g���ē��I�ɕύX�����
	(this->*pDrawFunc)();
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
	if (input.IsTrigger("next") || input.IsTrigger("START"))
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
	: BaseScene(controller),
	m_frameCount(fade_interval), // �t���[���J�E���g���t�F�[�h�C���̃t���[�����ŏ�����
	pUpdateFunc(&GameScene::FadeInUpdate), // �����̓t�F�[�h�C��
	pDrawFunc(&GameScene::FadeDraw),// �����̓t�F�[�h�`��
	m_playerHandle(-1)
{
	// �Q�[���V�[���̏���������
	//m_playerHandle = MV1LoadModel("data/model/player.mv1");
	//assert(m_playerHandle != -1);
}
