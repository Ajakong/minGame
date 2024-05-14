#include "Object.h"
#include"SphereCollision.h"

Object::Object() :
	m_pos(VGet(0,0,0)),
	m_SphereCol(std::make_shared<SphereCollision>())
{
}

Object::~Object()
{
}

void Object::CollisionSetPos(VECTOR pos)
{
	 m_SphereCol->SetPos(pos); 
}

void Object::CollisonSetRadius(int radius)
{
	 m_SphereCol->SetRadius(radius); 
}

