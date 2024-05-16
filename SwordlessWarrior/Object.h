#pragma once
#include"Dxlib.h"
#include <functional>
#include<iostream>
#include"Loader.h"

class SphereCollision;
class Physic;

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object();
	virtual  ~Object();

	virtual void Update()=0;
	virtual void Draw() = 0;
	virtual void Hit()=0;

	void CollisionSetPos(VECTOR pos);
	void CollisonSetRadius(int radius);

	std::shared_ptr<SphereCollision> GetSphereCol() { return m_SphereCol; }

protected:
	
	VECTOR m_pos;
	std::shared_ptr<SphereCollision> m_SphereCol;

	bool m_isHitFlag = false;
};

