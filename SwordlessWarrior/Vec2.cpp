#include"Dxlib.h"
#include"cassert"
#include"Vec2.h"


Vec2 Vec2::operator+(const Vec2& val) const
{
	return Vec2(x + val.x, y + val.y);
}

Vec2 Vec2::operator-(const Vec2& val) const
{
	return Vec2(x - val.x, y - val.y);
}

Vec2 Vec2::operator*(float scale) const
{
	return Vec2(x * scale, y * scale);
}

Vec2 Vec2::operator/(float div) const
{
	assert(div != 0.0f);
	return Vec2(x / div, y / div);
}


