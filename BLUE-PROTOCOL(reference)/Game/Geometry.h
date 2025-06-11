#pragma once
// �Q�[�����Ŏg�p����􉽊w�I�Ȓ萔��֐����`����w�b�_�[�t�@�C��

/// <summary>
/// �x�N�g��2D��\���\����
/// </summary>
struct Vector2
{
	float x, y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	// cpp�ɒ��g������
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scalar);
	void operator/=(float scalar);

	Vector2 operator+(const Vector2& right) const;
	Vector2 operator-(const Vector2& right) const;
	Vector2 operator*(const float& right) const;
	Vector2 operator/(const float& right) const;

	// �������g��ύX����
	void Normalize();
	// ���K�����ꂽ�x�N�g����Ԃ�(const�����Ă���̂ň��S)
	Vector2 Normalize() const;
	float Length() const;
};

// �ʖ������
using Position2 = Vector2;

/// <summary>
/// �T�C�Y��\���\����
/// </summary>
struct Size
{
	int w, h;
};

struct Rect
{
	Position2 center; // ���S���W
	Size size; // �T�C�Y
	float Left() const;
	float Top() const;
	float Right() const;
	float Bottom() const;

	void Draw();
};
