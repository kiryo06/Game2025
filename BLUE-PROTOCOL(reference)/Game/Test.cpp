#include "Test.h"

namespace
{
	constexpr float kMoveSpeed = 0.1f;
}

Test::Test() :
	m_posD1(0.0f, 50.0f, 0.0f),
	m_posD2(0.0f, 350.0f, 0.0f),
	m_posD3(100.0f, 50.0f, 0.0f),
	m_posD4(100.0f, 350.0f, 0.0f),
	m_MoveX(0.0f),
	m_MoveZ(0.0f)
{
}

Test::~Test()
{
}

void Test::Init()
{
}

void Test::Update()
{
	if (CheckHitKey(KEY_INPUT_H))
	{
		m_MoveX += kMoveSpeed;
		m_MoveZ += kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_L) && m_MoveX > 0)
	{
		m_MoveX -= kMoveSpeed;
		m_MoveZ -= kMoveSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_posD3.x -= m_MoveX;
		m_posD4.x -= m_MoveX;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_posD3.x += m_MoveX;
		m_posD4.x += m_MoveX;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_posD3.z += m_MoveZ;
		m_posD4.z += m_MoveZ;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_posD3.z -= m_MoveZ;
		m_posD4.z -= m_MoveZ;
	}
}

void Test::Draw()
{
	DrawFormatString(10, 20, 0xff0000, "pos1 X:%.3f | Y:%.3f | Z:%.3f", m_posD1.x, m_posD1.y, m_posD1.z);
	DrawFormatString(10, 36, 0xff0000, "pos2 X:%.3f | Y:%.3f | Z:%.3f", m_posD2.x, m_posD2.y, m_posD2.z);
	DrawFormatString(10, 52, 0xff0000, "pos3 X:%.3f | Y:%.3f | Z:%.3f", m_posD3.x, m_posD3.y, m_posD3.z);
	DrawFormatString(10, 68, 0xff0000, "pos4 X:%.3f | Y:%.3f | Z:%.3f", m_posD4.x, m_posD4.y, m_posD4.z);
	DrawFormatString(10, 84, 0xff0000, "Move X:%.3f | Move Z:%.3f", m_MoveX, m_MoveZ);
//	DrawCapsule3D(VGet(30, 0, 0), VGet(30, 200, 0), 100, 16, 0xff00ff, 0xff00ff, false);
	DrawCapsule3DD(m_posD1, m_posD2, 100, 16, 0xff00ff, 0xff00ff, false);
	DrawCapsule3DD(m_posD3, m_posD4, 100, 16, 0xff00ff, 0xff00ff, false);
}
