#pragma once
#include<iostream>

class Player;
class Camera;

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
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;

	bool m_isGameOverFlag = false;
	bool m_isClearFlag = false;

};

