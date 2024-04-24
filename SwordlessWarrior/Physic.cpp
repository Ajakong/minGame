#include "Physic.h"
#include"Object.h"
#include<list>
#include <functional>
#include<unordered_map>

namespace data
{

	std::unordered_map<const char*,std::function<void(void)>>hitFunction;
}

void Physic::Update()
{
	
}

void Physic::Entry(std::shared_ptr<SphereCollision> collion, std::function<void(void) >fp,const char* NameTag)
{
	data::hitFunction[NameTag] = fp;
}


void Physic::Exit(std::function<void(void) >fp, const char* NameTag)
{

}
