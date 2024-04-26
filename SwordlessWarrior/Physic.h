#pragma once
#include"SphereCollision.h"
#include"Object.h"
#include<iostream>
#include<list>
#include <functional>


using namespace std;

namespace Physic
{
	void Update();

	void Entry(std::shared_ptr<SphereCollision> collion, std::shared_ptr<Object> obj, const char* NameTag);


	void Exit( const char* NameTag);


};

