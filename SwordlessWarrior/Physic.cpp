#include "Physic.h"
#include"Object.h"
#include<list>
#include <functional>

namespace
{
	std::list<std::function<void(void)>>hitFunction;
}

void Physic::Update()
{
}

void Physic::Entry(std::shared_ptr<SphereCollision> collion, void(*fp)() )
{
	hitFunction.push_back(fp);
}


void Physic::Exit()
{

}
