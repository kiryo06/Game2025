#pragma once
#include "DxLib.h"

class Debug
{
private:

public:
	void Init()const;
	void Update()const;
	void Draw()const;

private:
	// �f�o�b�O�p�̍��W����`�悷�邽�߂̊֐�
	void DrawAxis() const;
	// �f�o�b�O�p�̃O���b�h��`�悷�邽�߂̊֐�
	void DrawGrid() const;

};

