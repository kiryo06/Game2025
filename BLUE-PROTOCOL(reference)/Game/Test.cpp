#include "Test.h"
#include <memory>
#include "Vec2.h"

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
	m_MoveZ(0.0f),
	circlePos(0.0f,100.0f,200.0f),
	lineStart(100.0f, 100.0f, 200.0f),
	lineEnd(-100.0f, 100.0f, 200.0f)
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
		circlePos.y += m_MoveZ;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_posD3.z -= m_MoveZ;
		m_posD4.z -= m_MoveZ;
		circlePos.y -= m_MoveZ;
	}
	Hit();
	
	LineAndBallHit();
}

void Test::Draw()
{
	DrawFormatString(10, 20, 0xff0000, "pos1 X:%.3f | Y:%.3f | Z:%.3f", m_posD1.x, m_posD1.y, m_posD1.z);
	DrawFormatString(10, 36, 0xff0000, "pos2 X:%.3f | Y:%.3f | Z:%.3f", m_posD2.x, m_posD2.y, m_posD2.z);
	DrawFormatString(10, 52, 0xff0000, "pos3 X:%.3f | Y:%.3f | Z:%.3f", m_posD3.x, m_posD3.y, m_posD3.z);
	DrawFormatString(10, 68, 0xff0000, "pos4 X:%.3f | Y:%.3f | Z:%.3f", m_posD4.x, m_posD4.y, m_posD4.z);
	DrawFormatString(10, 84, 0xff0000, "Move X:%.3f | Move Z:%.3f", m_MoveX, m_MoveZ);

	// カプセル1
	DrawCapsule3DD(m_posD1, m_posD2, kColRadius1, 16, 0xff00ff, 0xffffff, false);
	// カプセル2
	DrawCapsule3DD(m_posD3, m_posD4, kColRadius2, 16, 0xff00ff, 0xff00ff, false);

	// ライン
	DrawLine3D(lineStart, lineEnd, 0xffffff);
	// 球
	DrawSphere3D(circlePos, kColRadius1, 16, 0xffffff, 0xffffff, false);
}

void Test::Hit()
{
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
 
static float CalculationVectorLength(const VECTOR & vec) 
{  
   return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);  
}  

bool Test::LineAndBallHit()
{   
	// 仮
   VECTOR StartToCenter = VECTOR(circlePos.x - lineStart.x, circlePos.y - lineStart.y, circlePos.z - lineStart.z);  
   VECTOR EndToCenter = VECTOR(circlePos.x - lineEnd.x, circlePos.y - lineEnd.y, circlePos.z - lineEnd.z);
   VECTOR StartToEnd = VECTOR(lineEnd.x - lineStart.x, lineEnd.y - lineStart.y, lineEnd.z - lineStart.z);  
   VECTOR NormalStartToEnd = VNorm(StartToEnd);
   float DistanceProjection = StartToCenter.x * NormalStartToEnd.y - NormalStartToEnd.x * StartToCenter.y;

   if (fabs(DistanceProjection) < kColRadius1)
   {  
	   printfDx("Hit!!\n");
   }  
   else  
   {  
	   printfDx("--\n");
   }  

   float dot01 = StartToCenter.x * StartToEnd.x + StartToCenter.y * StartToEnd.y;
   float dot02 = EndToCenter.x * StartToEnd.x + EndToCenter.y * StartToEnd.y;

   if (dot01 * dot02 <= 0.0f)  
   {  
       return true;  
   }  

   if (CalculationVectorLength(StartToCenter) < kColRadius1 ||
       CalculationVectorLength(EndToCenter) < kColRadius1)
   {  
       return true;  
   }  

   return false;  
}


float Test::GetColRadius1() const
{
	return kColRadius1;
}

float Test::GetColRadius2() const
{
	return kColRadius2;
}
