#pragma once
#include<iostream>

class Physic;
class Player;
class Enemy;
class Camera;
class SkyDome;

using namespace std;
class GameManager
{
public:
	GameManager();
	~GameManager();
	void Init();
	void Update();
	void Draw();

	bool GetGameOver() { return m_isGameOverFlag; }
	bool GetClear() { return m_isClearFlag; }
private:
	std::shared_ptr<Physic> pPhysic;
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<Enemy> pEnemy;
	std::shared_ptr<Camera> pCamera;
	std::shared_ptr<SkyDome>pSkyDome;


	int m_stageHandle = 0;

	bool m_isGameOverFlag = false;
	bool m_isClearFlag = false;

};

