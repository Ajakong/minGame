#pragma once
#include<iostream>

class Enemy;

class UI
{
public:
	UI();
	~UI();

	void Init();
	void Update();
	void DrawEnemyHp(int enemyHp);
	void Draw(std::shared_ptr<Enemy>enemy);

private:
	int m_EnemyHpBarHandle = 0;

};

