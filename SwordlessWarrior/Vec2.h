#pragma once


#pragma once
#include <cmath>

/// ベクトルを便利に使うためのクラス(2次元ベクトル)
class Vec2
{
public:
	float x;
	float y;
	Vec2 operator+(const Vec2& val)const;
	Vec2 operator-(const Vec2& val)const;
	Vec2 operator*(float scale)const;
	Vec2 operator/(float div)const;

public:
	Vec2() :
		x(0.0f),
		y(0.0f)
	{
	}

	Vec2(float posX, float posY) :
		x(posX),
		y(posY)
	{
	}

	/// 単項演算子+
	Vec2 operator +() const
	{
		// thisポインタ : 自分自身のアドレスを指す
		return *this;
	}

	/// 単項演算子- 逆ベクトル
	Vec2 operator -() const
	{
		return Vec2{ -x, -y };
	}

	/// 足し算
	Vec2 operator +(Vec2& vec) const
	{
		return Vec2{ x + vec.x, y + vec.y };
	}
	Vec2 operator +=(Vec2 vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	/// 引き算
	Vec2 operator -(Vec2& vec) const
	{
		return Vec2{ x - vec.x, y - vec.y };
	}
	Vec2 operator -=(Vec2 vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	//掛け算
	Vec2 operator *(Vec2 vec) const
	{
		return Vec2{ x * vec.x, y * vec.y };
	}
	Vec2 operator *=(Vec2 vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	//割り算
	Vec2 operator /(Vec2 vec) const
	{
		return Vec2{ x / vec.x, y / vec.y };
	}
	Vec2 operator /=(Vec2 vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	/// <summary>
	/// ベクトルの長さの2乗を求める
	/// </summary>
	/// <returns>長さの2乗</returns>
	float SqLength() const
	{
		return x * x + y * y;
	}

	/// <summary>
	/// ベクトルの長さを求める
	/// </summary>
	/// <returns>長さ</returns>
	float Length() const
	{
		return sqrt(SqLength());
	}

	/// <summary>
	/// 自身の正規化を行う
	/// </summary>
	void Normalize()
	{
		float len = Length();

		// 長さ0以下なら処理を行わない
		if (len <= 0.0f) return;

		x /= len;
		y /= len;
	}

	/// <summary>
	/// 自身を正規化したベクトルを取得する
	/// </summary>
	/// <returns>正規化したベクトル</returns>
	Vec2 GetNormalized() const
	{
		float len = Length();

		// 長さ0以下なら(0, 0)を返す
		/* 引数ありにしている理由 */
		// 引数なしコンストラクタの修正に強くするため
		if (len <= 0.0f) return Vec2{ 0.0f, 0.0f };

		return Vec2{ x / len, y / len };
	}

	float ToCross(Vec2 a) { return x * a.y - y * a.x; }
};
