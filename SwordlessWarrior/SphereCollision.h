#pragma once
#include"Dxlib.h"
#include"Collider.h"
#include<iostream>


using namespace std;

class SphereCollision:public Collider
{
public:
	SphereCollision();
	~SphereCollision();

	void Update(VECTOR position) { pos = position; }
private:

};

