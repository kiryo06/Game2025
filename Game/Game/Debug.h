#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include <vector>

class Input;
class Debug
{
private:
	std::vector<std::vector<std::string>> m_FileData;
	std::vector<std::vector<std::string>> Sad;

public:
	/// <summary>
	/// �ʏ�U���̏��
	/// </summary>
	struct DebugData
	{
		std::string kSetName		= "empty";
		std::string moveSpeed		= "empty";
		std::string totalFrame		= "empty";
		std::string attackFrame		= "empty";
		std::string speed			= "empty";
		std::string animationName	= "empty";
	};

	Debug();
	~Debug();
	void Init();
	void Update(Input& input);
	void Draw();
	/// <summary>
	/// �e�L�������ʂŎg�p����ʏ�U����ݒ肷��
	/// </summary>
	/// <param name="debugData">csv�t�@�C�����玝���Ă������</param>
	void SetDebugData(std::vector<std::vector<std::string>> debugData);
	// Csv�ɏ�������
	void WriteSadToCsv(const std::string& filename);
private:
	// �f�o�b�O�p�̍��W����`�悷�邽�߂̊֐�
	void DrawAxis() const;
	// �f�o�b�O�p�̃O���b�h��`�悷�邽�߂̊֐�
	void DrawGrid() const;

	/// <summary>
	/// csv�t�@�C���ɓ����Ă��鏇��
	/// </summary>
	enum class DebugDataSort
	{
		kName,				//�ݒ�ۑ�
		kMoveSpeed,			//�ړ����x
		kTotalFrame,		//�s���t���[��
		kAttackFrame,		//��]���x
		kSpeed,				//�����x
		kTorigerName		//�����_
	};
	//���ׂẴL�����ŋ��ʂŎg���ʏ�U���̏��
	std::map<std::string, DebugData> m_debugData;
};

