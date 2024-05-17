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
			//��1,2�̒��S�̋��������߂�
			float DisX= obj1.second->GetSphereCol()->GetPos().x + obj2.second->GetSphereCol()->GetPos().x;
			float DisY= obj1.second->GetSphereCol()->GetPos().y + obj2.second->GetSphereCol()->GetPos().y;
			float DisZ= obj1.second->GetSphereCol()->GetPos().z + obj2.second->GetSphereCol()->GetPos().z;
			float Distance = sqrt(DisX * DisX + DisY * DisY+DisZ*DisZ);//�O����

			//���a�̍��v
			float totalRadius = obj1.second->GetSphereCol()->GetRadius() + obj2.second->GetSphereCol()->GetRadius();
			if (Distance < totalRadius)//���S�̋��������a�̍��v�����Ȃ�Փ˂ɂ���
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

}
