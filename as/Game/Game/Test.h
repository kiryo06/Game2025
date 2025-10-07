#pragma once
#include "DxLib.h"
class Test
{
private:
	VECTOR_D m_posD1;
	VECTOR_D m_posD2;
	VECTOR_D m_posD3;
	VECTOR_D m_posD4;
	float m_MoveX;
	float m_MoveZ;

	VECTOR circlePos;
	VECTOR lineStart;
	VECTOR lineEnd;
public:
	Test();
	~Test();
	void Init();
	void Update();
	void Draw();
	void Hit();
	// ƒ‰ƒCƒ“‚Æ‹…‚Ì“–‚½‚è”»’è
	bool LineAndBallHit();

	float GetColRadius1() const;
	float GetColRadius2() const;
};

