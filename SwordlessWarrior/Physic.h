#pragma once
#include"SphereCollision.h"
#include"Object.h"
#include<iostream>
#include<list>
#include <functional>


using namespace std;

class Physic
{
public:
	void Update();

	void Entry(std::shared_ptr<Object> obj, const char* NameTag);


	void Exit( const char* NameTag);

	bool JudgeColision(std::shared_ptr<Object> ob1, std::shared_ptr<Object> obj2);
};

