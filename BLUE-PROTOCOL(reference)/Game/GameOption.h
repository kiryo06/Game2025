#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include <vector>
			
class Input;
class GameOption
{
private:
	// �ǂݍ��ނ��߂̃t�@�C����ۑ����邽�߂̃����o�[�ϐ�
	std::vector<std::vector<std::string>> m_controllerOptionDataFile;	// �R���g���[���[�p�̃t�@�C�����ۑ�
	std::vector<std::vector<std::string>> m_audioOptionDataFile;		// �I�[�f�B�I�p�̃t�@�C�����ۑ�
	// �ǂݍ��񂾃f�[�^��ۑ����Ă������߂̃����o�[�ϐ�
	std::vector<std::vector<std::string>> m_controllerOptionData;		// �R���g���[���[�p�̃f�[�^�ۑ�
	std::vector<std::vector<std::string>> m_audioOptionData;			// �I�[�f�B�I�p�̃f�[�^�ۑ�
public:


	/// <summary>
	/// �R���g���[���[�̏��
	/// </summary>
	struct ControllerOptionData
	{
		std::string kSetName				= "empty";							// �ݒ�̎��
		std::string kUpDownInversion		= "empty";					// �J�����̏㉺���]
		std::string kLeftRightInversion		= "empty";				// �J�����̍��E�̔��]
		std::string kHorizontalSensitivity	= "empty";			// �J�����̐������x
		std::string kVerticalSensitivity	= "empty";				// �J�����̐������x
		std::string kDecision				= "empty";						// ����
		std::string kCancel					= "empty";							// �L�����Z��
		std::string kJump			= "empty";		// �W�����v
		std::string kDash			= "empty";		// �_�b�V��
		std::string kSetName			= "empty";		// �U��
		std::string kSetName			= "empty";		// �X�L��1
		std::string kSetName			= "empty";		// �X�L��2
		std::string kSetName			= "empty";		// ���
		std::string kSetName			= "empty";		// ���b�N�I��
		std::string kSetName			= "empty";		// ���Ⴊ��
		std::string kSetName			= "empty";		// ���j���[
		std::string kSetName			= "empty";		// �I�v�V����
	};

	/// <summary>
	/// �I�[�f�B�I�̏��
	/// </summary>
	struct AudioOptionData
	{
		std::string kSetName	= "empty";
		std::string kVolume		= "empty";
	};

	GameOption();
	~GameOption();
	void Init();
	void Update();
	void Draw();
private:
};

