#pragma once

#include"SphereCollision.h"
#include"Dxlib.h"

class Object
{
public:
	Object();
	virtual  ~Object();

	virtual void Update()=0;
	virtual void Draw()=0;

	void Hit();
protected:
	VECTOR m_pos;
	std::shared_ptr<SphereCollision> m_SphereCol;

	bool HitFlag = false;
};

