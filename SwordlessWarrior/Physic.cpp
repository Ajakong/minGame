#include "Physic.h"
#include"Object.h"
#include<list>
#include <functional>
#include<unordered_map>
#include"Object.h"

namespace data
{

	std::unordered_map < const char*, std::shared_ptr<Object>> object;
}

void Physic::Update()
{
	
}

void Physic::Entry(std::shared_ptr<SphereCollision> collion, std::shared_ptr<Object> obj,const char* NameTag)
{
	data::object[NameTag] = obj;
}


void Physic::Exit(const char* NameTag)
{

}
