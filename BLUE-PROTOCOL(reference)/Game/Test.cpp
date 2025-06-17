#include "Test.h"
#include <memory>

namespace
{
	constexpr float kMoveSpeed = 0.1f;

	// プレイヤーの当たり判定
	constexpr float kColRadius1 = 100.0f;
	constexpr float kColRadius2 = 100.0f;
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
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_posD3.x -= m_MoveX;
		m_posD4.x -= m_MoveX;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_posD3.x += m_MoveX;
		m_posD4.x += m_MoveX;
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		m_posD3.z += m_MoveZ;
		m_posD4.z += m_MoveZ;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_posD3.z -= m_MoveZ;
		m_posD4.z -= m_MoveZ;
	}
	Hit();
}

void Test::Draw()
{
	DrawFormatString(10, 20, 0xff0000, "pos1 X:%.3f | Y:%.3f | Z:%.3f", m_posD1.x, m_posD1.y, m_posD1.z);
	DrawFormatString(10, 36, 0xff0000, "pos2 X:%.3f | Y:%.3f | Z:%.3f", m_posD2.x, m_posD2.y, m_posD2.z);
	DrawFormatString(10, 52, 0xff0000, "pos3 X:%.3f | Y:%.3f | Z:%.3f", m_posD3.x, m_posD3.y, m_posD3.z);
	DrawFormatString(10, 68, 0xff0000, "pos4 X:%.3f | Y:%.3f | Z:%.3f", m_posD4.x, m_posD4.y, m_posD4.z);
	DrawFormatString(10, 84, 0xff0000, "Move X:%.3f | Move Z:%.3f", m_MoveX, m_MoveZ);





	DrawCapsule3DD(m_posD1, m_posD2, kColRadius1, 16, 0xff00ff, 0xffffff, true);
	DrawCapsule3DD(m_posD3, m_posD4, kColRadius2, 16, 0xff00ff, 0xff00ff, false);
}

void Test::Hit()
{

	// 3D空間上の球同士の当たり判定(勉強用)
	// 3D空間上の球の中心位置同士の距離を求める
	float playerRadius = GetColRadius1();
	float enemyRadius = GetColRadius2();

	float distX = m_posD1.x - m_posD3.x;
	float distY = m_posD1.y - m_posD3.y;
	float distZ = m_posD1.z - m_posD3.z;

	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);
	if ((dist) < (playerRadius + enemyRadius))
	{
		printfDx("Hit!!\n");
	}
	else
	{
		printfDx("--\n");
	}
}


float Test::GetColRadius1() const
{
	return kColRadius1;
}

float Test::GetColRadius2() const
{
	return kColRadius2;
}
