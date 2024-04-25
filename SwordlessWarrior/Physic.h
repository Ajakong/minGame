#pragma once
#include"SphereCollision.h"
#include<iostream>
#include<list>
#include <functional>


using namespace std;

namespace Physic
{
	void Update();

	void Entry(std::shared_ptr<SphereCollision> collision, std::function<void()>, const char* ObjectName);


	void Exit( const char* NameTag);


};

