#pragma once
// ゲーム内で使用する幾何学的な定数や関数を定義するヘッダーファイル

/// <summary>
/// ベクトル2Dを表す構造体
/// </summary>
struct Vector2
{
	float x, y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	// cppに中身を実装
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scalar);
	void operator/=(float scalar);

	Vector2 operator+(const Vector2& right) const;
	Vector2 operator-(const Vector2& right) const;
	Vector2 operator*(const float& right) const;
	Vector2 operator/(const float& right) const;

	// 自分自身を変更する
	void Normalize();
	// 正規化されたベクトルを返す(constをつけているので安心)
	Vector2 Normalize() const;
	float Length() const;
};

// 別名を作る
using Position2 = Vector2;

/// <summary>
/// サイズを表す構造体
/// </summary>
struct Size
{
	int w, h;
};

struct Rect
{
	Position2 center; // 中心座標
	Size size; // サイズ
	float Left() const;
	float Top() const;
	float Right() const;
	float Bottom() const;

	void Draw();
};
