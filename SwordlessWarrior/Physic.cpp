#include "Physic.h"
#include"Object.h"

namespace data
{

	std::unordered_map <Tag, std::shared_ptr<Object>> object;

	std::list<CollisionObject> postCollisionObjectList;
}

void Physic::Update()
{
	for (const auto& obj1 : data::object)
	{
		//当たり判定が活動していなかったら判定しない
		if (!obj1.second->GetHitFlag()) continue;
		for (const auto& obj2 : data::object)
		{
			if (obj1.first == obj2.first)continue;

			if (JudgeColision(obj1.second, obj2.second))
			{
				m_collisionObjectList.push_back({ obj1.second,obj2.second });
			}
		}
	}

	CollisionManage();
	data::postCollisionObjectList = m_collisionObjectList;
	m_collisionObjectList.clear();

}

void Physic::Entry(std::shared_ptr<Object> obj,Tag name)
{
	data::object[name] = obj;
}


void Physic::Exit(Tag name)
{
	data::object.erase(name);
}

void Physic::Clear()
{
	data::object.clear();
}

bool Physic::JudgeColision(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2)
{
	float DisX = (obj2->GetPos().x - obj1->GetPos().x);
	float DisY = (obj2->GetPos().y - obj1->GetPos().y);
	float DisZ = (obj2->GetPos().z - obj1->GetPos().z);
	float Distance = sqrt(DisX * DisX + DisY * DisY+DisZ*DisZ);
	if (Distance < obj1->GetSphereCol()->GetRadius() + obj2->GetSphereCol()->GetRadius())
	{
		return true;
	}
	
	return false;
}

void Physic::CollisionManage()
{
	auto iterator = data::postCollisionObjectList.begin();
	for (const auto& item : m_collisionObjectList)
	{
		if (data::postCollisionObjectList.size() != 0)//1フレーム前の当たったオブジェクトが同じ場合衝突関数を呼ばない
		{
			if (iterator != data::postCollisionObjectList.end() && iterator->objB == item.objB)continue;

		}
		if (item.objA->GetTag() == Tag::Player && item.objB->GetTag() == Tag::FightBackObj)item.objB->Hit();
		else if (item.objA->GetTag() == Tag::FightBackObj && item.objB->GetTag() == Tag::Player)item.objA->Hit();
		else
		{
			item.objA->Hit();
			item.objB->Hit();

		}

		if(iterator!=data::postCollisionObjectList.end())iterator ++ ;
	}
}

