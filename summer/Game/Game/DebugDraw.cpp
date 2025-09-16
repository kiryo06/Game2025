#include "DebugDraw.h"  
#include "DxLib.h"  
using namespace MyLib;  

// 実態定義  
std::vector<DebugDraw::LineInfo>DebugDraw::lineinfo;  
std::vector<DebugDraw::SphysicsInfo>DebugDraw::Sphysicsinfo;  

/// <summary>  
/// クリア  
/// </summary>  
void MyLib::DebugDraw::Clear()  
{  
    lineinfo.clear();
    Sphysicsinfo.clear();
}  

/// <summary>  
/// 描画  
/// </summary>  
void MyLib::DebugDraw::Draw()  
{  
   for (const auto& item : lineinfo)  
   {  
       DxLib::DrawLine3DD(item.start, item.end, item.color);  
   }  

   for (const auto& item : Sphysicsinfo)  
   {  
       DxLib::DrawSphere3DD(item.pos1, item.radius, item.divNum, item.difColor, item.spcColor, item.flag);
   }  
}  

/// <summary>
/// ラインの描画
/// </summary>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <param name="color">カラー</param>
void MyLib::DebugDraw::DrawLine(const VECTOR_D& start, const VECTOR_D& end, int color)  
{  
   LineInfo newInfo;  
   newInfo.start = start;  
   newInfo.end = end;  
   newInfo.color = color;  
   lineinfo.emplace_back(newInfo);
}

/// <summary>
/// 球の描画
/// </summary>
/// <param name="pos1">中心座標</param>
/// <param name="radius">半径</param>
/// <param name="divNum">球を作る線の数</param>
/// <param name="difColor">ディフーズカラー</param>
/// <param name="spcColor">スペキュラーカラー</param>
/// <param name="flag">描画の状態</param>
void MyLib::DebugDraw::DrawSphysics(const VECTOR_D& pos1, float radius, int divNum, int difColor, int spcColor, bool flag)
{
    SphysicsInfo newInfo;
    newInfo.pos1 = pos1;
    newInfo.radius = radius;
    newInfo.divNum = divNum;
    newInfo.difColor = difColor;
    newInfo.spcColor = spcColor;
    newInfo.flag = flag;
    Sphysicsinfo.emplace_back(newInfo);
}
