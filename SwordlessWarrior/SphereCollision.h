#pragma once
#include"Dxlib.h"
#include<iostream>


using namespace std;

class SphereCollision
{
public:
	SphereCollision();
	~SphereCollision();

	void Update(VECTOR position) { pos = position; }
private:
	VECTOR pos;
	int radius;

};

