#pragma once
#include "DxLib.h"

class Input;
class Debug
{
private:
//	const char* m_FileData;
	std::vector<std::vector<std::string>> m_FileData;
	char* m_Data1;
//	char* m_Data2[256];
//	const char* m_Data1[256];
	const char* m_Data2[256];
public:
	Debug();
	~Debug();
	void Init();
	void Update(Input& input);
	void Draw();

private:
	// �f�o�b�O�p�̍��W����`�悷�邽�߂̊֐�
	void DrawAxis() const;
	// �f�o�b�O�p�̃O���b�h��`�悷�邽�߂̊֐�
	void DrawGrid() const;
};

