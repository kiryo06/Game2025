#pragma once
// �X�}�[�g�|�[���^�[���g��
#include <memory>
#include <list>

class Input;
class BaseScene;

/// <summary>
/// �e�V�[�����Ǘ����邽�߂̃N���X
/// �Ǘ��͂��邪�V�[���J�ڂ͊Ǘ����Ȃ�
/// �C���^�[�t�F�[�X��񋟂��邽�߂̃N���X
/// </summary>
class SceneController
{
private:
	std::list<std::shared_ptr<BaseScene>> _scenes; ///< �V�[���̃��X�g
public:
	SceneController();

	/// <summary>
	///  Application����Ă΂��֐��B���݂̃V�[����Init�����̂܂܎��s�B
	/// </summary>
	void Init();
	/// <summary>
	/// Application����Ă΂��֐��B���݂̃V�[����Update�����̂܂܎��s�B
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input, float deltaTime);
	/// <summary>
	/// Application����Ă΂��֐��B���݂̃V�[����Draw�����̂܂܎��s�B
	/// </summary>
	void Draw();
	/// <summary>
	/// ���̏�Ԃ��Z�b�g����(�Z�b�g����̂͊e��Ԃ̖���)
	/// �e�V�[�����R���g���[���[�����Đ؂�ւ�������H
	/// </summary>
	/// <param name="">���̏�Ԃ̃|�C���^�i�X�}�|�j</param>
	void ChangeScene(std::shared_ptr<BaseScene>);

	/// <summary>
	/// ���ݎ��s���̃V�[���̏�ɕʂ̃V�[�����������
	/// </summary>
	/// <param mane="scene">����������V�[��</param>
	void PushScene(std::shared_ptr<BaseScene> scene);

	/// <summary>
	/// ���݁A��ԏ�ɂ�����s���̃V�[������菜��
	/// </summary>
	void PopScene();
};

