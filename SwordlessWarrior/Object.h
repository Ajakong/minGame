#pragma once
#include"Dxlib.h"
#include <functional>
#include<iostream>

class SphereCollision;

class Object : public std::enable_shared_from_this<Object>
{
public:
	Object(int& m_modelhandle);
	virtual  ~Object();

	virtual void Update()=0;
	virtual void Draw() = 0;
	virtual void Hit()=0;

protected:
	int m_modelHandle = 0;
	VECTOR m_pos;
	std::shared_ptr<SphereCollision> m_SphereCol;



	bool HitFlag = false;
};

