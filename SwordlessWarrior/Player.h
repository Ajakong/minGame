#pragma once
#include"Object.h"



class Player : public Object
{
public:
	Player(int& modelhandle);
	~Player();

	void Init();

	void Update();
	void Draw();

	VECTOR GetPos()const { return m_pos; }

	void Hit();
private:
	
};

