#pragma once
#include <vector>
#include "DxLib.h"

namespace MyLib
{
	class DebugDraw
	{
	public:
		static void Clear();
		static void Draw();

		// 3D���C���̕`��
		static void DrawLine(const VECTOR_D& start, const VECTOR_D& end, int color);

		// ���̕`��
		static void DrawSphysics(const VECTOR_D& pos1, float radius, int divNum, int difColor, int spcColor, bool flag);

		// �J�v�Z���̕`��


	private:
		// ���C���̏��
		struct LineInfo
		{
			VECTOR_D start;
			VECTOR_D end;
			int color;
		};
		// ���̏��
		struct SphysicsInfo
		{
			VECTOR_D pos1;
			float radius;
			int divNum;
			int difColor;
			int spcColor;
			bool flag;
		};
		static std::vector<LineInfo>		lineinfo;
		static std::vector<SphysicsInfo>	Sphysicsinfo;
	};
}

