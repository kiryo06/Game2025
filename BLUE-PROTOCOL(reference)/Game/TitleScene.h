#pragma once
#include "BaseScene.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public BaseScene
{
private:
	int m_frameCount = 0; // �t���[���J�E���g
	int m_background = -1; // �w�i�摜�̃n���h��

	using UpdateFunc = void (TitleScene::*)(Input&);
	using DrawFunc = void (TitleScene::*)();

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

public:
	TitleScene(SceneController& controller);

	/// <summary>
	/// ����������
	/// </summary>
	void Init() override;
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
};

