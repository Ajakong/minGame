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
			if (obj1.second == obj2.second)continue;

			if (obj1.first == obj2.first)continue;
			////��1,2�̒��S�̋��������߂�
			//float DisX= obj1.second->GetSphereCol()->GetPos().x + obj2.second->GetSphereCol()->GetPos().x;
			//float DisY= obj1.second->GetSphereCol()->GetPos().y + obj2.second->GetSphereCol()->GetPos().y;
			//float DisZ= obj1.second->GetSphereCol()->GetPos().z + obj2.second->GetSphereCol()->GetPos().z;
			//float Distance = sqrt(DisX * DisX + DisY * DisY+DisZ*DisZ);//�O����

			////���a�̍��v
			//float totalRadius = obj1.second->GetSphereCol()->GetRadius() + obj2.second->GetSphereCol()->GetRadius();
			//if (Distance < totalRadius)//���S�̋��������a�̍��v�����Ȃ�Փ˂ɂ���
			if(JudgeColision(obj1.second,obj2.second))
			{
				obj1.second->Hit();
				obj2.second->Hit();
			}

		}
	}
}

void Physic::Entry(std::shared_ptr<Object> obj,const char* NameTag)
{
	data::object[NameTag] = obj;
}


void Physic::Exit(const char* NameTag)
{
	data::object.erase(NameTag);
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

