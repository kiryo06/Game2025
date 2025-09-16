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

		// 3Dラインの描画
		static void DrawLine(const VECTOR_D& start, const VECTOR_D& end, int color);

		// 球の描画
		static void DrawSphysics(const VECTOR_D& pos1, float radius, int divNum, int difColor, int spcColor, bool flag);

		// カプセルの描画


	private:
		// ラインの情報
		struct LineInfo
		{
			VECTOR_D start;
			VECTOR_D end;
			int color;
		};
		// 球の情報
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

