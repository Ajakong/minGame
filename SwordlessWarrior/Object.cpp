#include "Object.h"
#include"SphereCollision.h"

Object::Object(VECTOR pos) :
	m_pos(pos),
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

void Object::CollisonSetRadius(float& radius)
{
	 m_SphereCol->SetRadius(radius); 
}

