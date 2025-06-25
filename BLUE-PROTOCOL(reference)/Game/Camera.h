#pragma once
#include "DxLib.h"
#include <memory>

class Player;
class Camera
{
private:
	VECTOR m_pos;				// �J�����̈ʒu
	VECTOR m_targetPos;			// �J�����̒����_
	VECTOR m_move;				// �J�����̓���
	VECTOR m_cameraRot;			// �J�����̉�]��

	float m_cameraPosAtan2;		// �J�����̃A�[�N�^���W�F���g��ۑ����邽�߂̕ϐ�
	VECTOR m_cemeraGetPos;		// �J�����̈ʒu���擾
	VECTOR m_cameraGetTarget;	// �J�����̒����_���擾
public:
	Camera();
	~Camera();
	void Init()const;
	void Update(Player* m_pPlayer);
	void Draw()const;
	float GetAtan2()const { return m_cameraPosAtan2; }
private:
};

