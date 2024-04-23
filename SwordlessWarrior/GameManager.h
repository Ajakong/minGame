#pragma once
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

	bool m_isGameOverFlag = false;
	bool m_isClearFlag = false;

};

