#pragma once
#include"Dxlib.h"
#include<iostream>

class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual void Update(VECTOR position) = 0;
protected:
	VECTOR pos;
	int radius;
};

