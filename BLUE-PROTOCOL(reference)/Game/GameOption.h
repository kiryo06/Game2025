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
		std::string name					= "empty";		// �ݒ�̎��
		std::string upDownInversion			= "empty";		// �J�����̏㉺���]
		std::string leftRightInversion		= "empty";		// �J�����̍��E�̔��]
		std::string horizontalSensitivity	= "empty";		// �J�����̐������x
		std::string verticalSensitivity		= "empty";		// �J�����̐������x
		std::string decision				= "empty";		// ����
		std::string cancel					= "empty";		// �L�����Z��
		std::string jump					= "empty";		// �W�����v
		std::string dash					= "empty";		// �_�b�V��
		std::string attack					= "empty";		// �U��
		std::string skill_1					= "empty";		// �X�L��1
		std::string skill_2					= "empty";		// �X�L��2
		std::string avoidance				= "empty";		// ���
		std::string lockOn					= "empty";		// ���b�N�I��
		std::string squat					= "empty";		// ���Ⴊ��
		std::string menu					= "empty";		// ���j���[
		std::string option					= "empty";		// �I�v�V����
	};

	/// <summary>
	/// �I�[�f�B�I�̏��
	/// </summary>
	struct AudioOptionData
	{
		std::string name					= "empty";		// �ݒ�̎��
		std::string volume					= "empty";		// �{�����[��
	};

	GameOption();
	~GameOption();
	void Init();
	void Update();
	void Draw();
private:
	/// <summary>
	/// ControllerOptionData.csv�t�@�C���ɓ����Ă��鏇��
	/// </summary>
	enum class ControllerOptionDataSort
	{
		kName,								// �ݒ�̎��
		kUpDownInversion,					// �J�����̏㉺���]
		kLeftRightInversion,				// �J�����̍��E�̔��]
		kHorizontalSensitivity,				// �J�����̐������x
		kVerticalSensitivity,				// �J�����̐������x
		kDecision,							// ����
		kCancel,							// �L�����Z��
		kJump,								// �W�����v
		kDash,								// �_�b�V��
		kAttack,							// �U��
		kSkill_1,							// �X�L��1
		kSkill_2,							// �X�L��2
		kAvoidance,							// ���
		kLockOn,							// ���b�N�I��
		kSquat,								// ���Ⴊ��
		kMenu,								// ���j���[
		kOption								// �I�v�V����
	};

	/// <summary>
	/// AudioOptionData.csv�t�@�C���ɓ����Ă��鏇��
	/// </summary>
	enum class AudioOptionDataSort
	{
		kName,								// �ݒ�̎��
		kVolume								// �{�����[��
	};

};

