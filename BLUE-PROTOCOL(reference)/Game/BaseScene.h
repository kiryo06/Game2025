#pragma once

class Input;
class SceneController;

/// <summary>
/// �e�V�[���̊��N���X
/// </summary>
class BaseScene
{
protected:
	// �e��Ԃ��؂�ւ�邽�߂�
	SceneController& controller_;
public:
	BaseScene(SceneController& controller);

	virtual void Init() = 0;

	virtual void End() = 0;

	/// <summary>
	/// �����ϐ��̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	virtual void Update(Input& input,float deltaTime) = 0;

	/// <summary>
	///  �`��
	/// </summary>
	virtual void Draw() = 0;
};

