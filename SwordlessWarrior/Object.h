#pragma once

#include"SphereCollision.h"
#include"Dxlib.h"
#include <functional>

namespace NameTag
{
	const char* Player = "Player";
	const char* Enemy = "Enemy";
}

class Object
{
public:
	Object();
	virtual  ~Object();

	virtual void Update()=0;
	virtual void Draw() = 0;
	virtual void Hit()=0;

protected:
	VECTOR m_pos;
	std::shared_ptr<SphereCollision> m_SphereCol;

	bool HitFlag = false;
};

