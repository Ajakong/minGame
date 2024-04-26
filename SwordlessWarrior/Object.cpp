#include "Object.h"
#include"SphereCollision.h"

Object::Object(int& m_modelhandle) :
	m_modelHandle(m_modelhandle),
	m_pos(VGet(0,0,0)),
	m_SphereCol(std::make_shared<SphereCollision>())
{
}

Object::~Object()
{
}

