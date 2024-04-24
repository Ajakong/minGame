#pragma once
#include"Object.h"



class Player : public Object
{
public:
	Player();
	~Player();

	void Update();
	void Draw();

	std::function<void(void) > Hit();
private:
	
};

