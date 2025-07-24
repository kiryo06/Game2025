#include "DebugDraw.h"  
#include "DxLib.h"  
using namespace MyLib;  

// ���Ԓ�`  
std::vector<DebugDraw::LineInfo>DebugDraw::lineinfo;  
std::vector<DebugDraw::SphysicsInfo>DebugDraw::Sphysicsinfo;  

/// <summary>  
/// �N���A  
/// </summary>  
void MyLib::DebugDraw::Clear()  
{  
    lineinfo.clear();
    Sphysicsinfo.clear();
}  

/// <summary>  
/// �`��  
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
/// ���C���̕`��
/// </summary>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
/// <param name="color">�J���[</param>
void MyLib::DebugDraw::DrawLine(const VECTOR_D& start, const VECTOR_D& end, int color)  
{  
   LineInfo newInfo;  
   newInfo.start = start;  
   newInfo.end = end;  
   newInfo.color = color;  
   lineinfo.emplace_back(newInfo);
}

/// <summary>
/// ���̕`��
/// </summary>
/// <param name="pos1">���S���W</param>
/// <param name="radius">���a</param>
/// <param name="divNum">���������̐�</param>
/// <param name="difColor">�f�B�t�[�Y�J���[</param>
/// <param name="spcColor">�X�y�L�����[�J���[</param>
/// <param name="flag">�`��̏��</param>
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
