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

	void SetPos(VECTOR pos) { m_pos = pos; }
	void SetRadius(float radius) { m_radius = radius; }

	VECTOR GetPos() { return m_pos; }
	float GetRadius() { return m_radius; }


protected:
	VECTOR m_pos;
	float m_radius;
};

