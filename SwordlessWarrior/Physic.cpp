#include "Physic.h"
#include"Object.h"
#include<list>
#include <functional>
#include<unordered_map>
#include"Object.h"

namespace data
{

	std::unordered_map <Tag, std::shared_ptr<Object>> object;
}

void Physic::Update()
{
	for (const auto& obj1 : data::object)
	{
		for (const auto& obj2 : data::object)
		{
			if (obj1.first == obj2.first)continue;
			
			if(JudgeColision(obj1.second,obj2.second))
			{
				m_collisionObjectList.push_back({ obj1.second,obj2.second });
			}
		}
	}

	
}

void Physic::Entry(std::shared_ptr<Object> obj,Tag name)
{
	data::object[name] = obj;
}


void Physic::Exit(Tag name)
{
	data::object.erase(name);
}

bool Physic::JudgeColision(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2)
{
	float DisX = (obj2->GetPos().x - obj1->GetPos().x);
	float DisY = (obj2->GetPos().y - obj1->GetPos().y);
	float DisZ = (obj2->GetPos().z - obj1->GetPos().z);
	float Distance = sqrt(DisX * DisX + DisY * DisY+DisZ*DisZ);
	if (Distance < obj1->GetSphereCol()->GetRadius() + obj2->GetSphereCol()->GetRadius()) return true;

	
	return false;
}

void Physic::CollisionManage()
{
	for (const auto& item : m_collisionObjectList)
	{
		if (item.objA->GetTag() == Tag::Player && item.objB->GetTag() == Tag::FightBackObj)
		{
			item.objB->Hit();
		}
		else
		{

		}
		item.objA->Hit();
		item.objB->Hit();
	}
}

