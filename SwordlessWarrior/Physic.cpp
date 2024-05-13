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
	for (const auto& obj1 : data::object)
	{
		for (const auto& obj2 : data::object)
		{


		}
	}
}

void Physic::Entry(std::shared_ptr<SphereCollision> collion, std::shared_ptr<Object> obj,const char* NameTag)
{
	data::object[NameTag] = obj;
}


void Physic::Exit(const char* NameTag)
{

}
