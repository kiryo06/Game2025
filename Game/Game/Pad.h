#pragma once
#include "Vec2.h"

// �R���g���[���[�̓��͏�Ԃ��擾����
namespace Pad
{
	// �p�b�g�̓��͏�Ԃ��擾����
	void Update();

	// ������������
	bool isPress(int button);
	// �g���K�[����
	bool isTrigger(int button);
	// ����������
	bool isRelase(int button);

	bool isInputPadA();

	// ���X�e�B�b�N
	Vec2 GetLeftStick();
	// �E�X�e�B�b�N
	Vec2 GetRightStick();
};

