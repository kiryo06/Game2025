#pragma once  
#include "DxLib.h"  

class ColliderSphere3D  
{  
public:  
   VECTOR center; // "center" メンバーを追加  
   float radius;  

   ColliderSphere3D() : center(VGet(0.0f, 0.0f, 0.0f)), radius(0.0f) {}  
};
