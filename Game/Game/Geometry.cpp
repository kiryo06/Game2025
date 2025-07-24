#include "Geometry.h"
#include <cmath>
#include"DxLib.h"

void Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
}

Vector2 Vector2::operator+(const Vector2& right) const
{
	// 波かっこで囲むと一時オブジェクトを作らなくていいので楽
	// しかも値のコピーが減るので速い
	return { x + right.x, y + right.y };
}

Vector2 Vector2::operator-(const Vector2& right) const
{
	return { x - right.x, y - right.y };
}

Vector2 Vector2::operator*(const float& right) const
{
	return { x * right, y * right };
}

Vector2 Vector2::operator/(const float& right) const
{
	return { x / right, y / right };
}

void Vector2::Normalize()
{
	float length = Length();

	if (length == 0.0f) return; // ゼロ除算を防ぐ

	x /= length;
	y /= length;
}

Vector2 Vector2::Normalize() const
{
	float length = Length();

	if (length != 0.0f) return{};

	return { x / length, y / length };
}

float Vector2::Length() const
{
	return hypotf(x, y);
}

float Rect::Left() const
{
	return center.x - size.w / 2.0f;
}

float Rect::Top() const
{
	return center.y - size.h / 2.0f;
}

float Rect::Right() const
{
	return center.x + size.w / 2.0f;
}

float Rect::Bottom() const
{
	return center.y + size.h / 2.0f;
}

void Rect::Draw()
{
//	DrawBox(Left(), Top(), Right(), Bottom(), col, false, 2.0f);
	DrawBox(Left(), Top(), Right(), Bottom(), 0xffffff, false,2.0f); // 白色で塗りつぶし
}
