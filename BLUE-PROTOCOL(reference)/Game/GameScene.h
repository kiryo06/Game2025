#pragma once
#include "BaseScene.h"
#include <memory>

class Player;
//class Enemy;
class Camera;
class Debug;
class Test;
class GameScene : public BaseScene
{
public:
	GameScene(SceneController& controller);

	/// <summary>
	/// 
	/// </summary>
	void Init() override;
	/// <summary>
	/// 
	/// </summary>
	void End() override;
	/// <summary>
	/// �h���N���X�Ŏ���������
	/// virtual �͂�����p�����邩������Ȃ�����A
	/// override�͖����I�ɃI�[�o�[���C�h���G�f�B�^�Ɏ�������
	/// </summary>
	void Update(Input& input) override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw() override;
private:
	int m_frameCount = 0;	// �t���[���J�E���g
	int m_playerHandle;		// �v���C���[�̃��f��
//	int m_enemyHandle;		// �G�̃��f��


	std::shared_ptr<Player> m_pPlayer;
//	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Debug> m_pDebug;
	std::shared_ptr<Test> m_pTest;

	using UpdateFunc = void (GameScene::*)(Input&);
	using DrawFunc = void (GameScene::*)();

	UpdateFunc pUpdateFunc; // �X�V�����̊֐��|�C���^
	DrawFunc pDrawFunc; // �`�揈���̊֐��|�C���^

	// �t�F�[�h�C������Update�֐�
	void FadeInUpdate(Input& input);
	// �t�F�[�h�A�E�g����Update�֐�
	void FadeOutUpdate(Input& input);
	// �����łȂ��Ƃ���Update�֐�
	void NormalUpdate(Input& input);

	// �`��
	void FadeDraw();
	void NormalDraw();
};

