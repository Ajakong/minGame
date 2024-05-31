#pragma once
#include"SphereCollision.h"
#include"Object.h"
#include<iostream>
#include<list>
#include <functional>


using namespace std;

struct CollisionObject
{
	std::shared_ptr<Object> objA;
	std::shared_ptr<Object> objB;

	CollisionObject(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2) { objA = obj1; objB = obj2; }
};


class Physic
{
public:
	void Update();

	void Entry(std::shared_ptr<Object> obj,Tag name);


	void Exit(Tag name);

	
private:
	bool JudgeColision(std::shared_ptr<Object> ob1, std::shared_ptr<Object> obj2);


	void CollisionManage();

private:
	std::list<CollisionObject> m_collisionObjectList;
	int collisionLogNum;
};

