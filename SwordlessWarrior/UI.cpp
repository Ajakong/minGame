#include "UI.h"
#include"Loader.h"
UI::UI():
	m_EnemyHpBarHandle(Loader::GetEnemyHpBarHandle())
{
}

UI::~UI()
{
}

void UI::Init()
{
}

void UI::Update()
{
}

void UI::DrawEnemyHp(int enemyHp)
{
	for (int i = 0; i < enemyHp; i += 10)
	{
		DrawBox(1425, 50 + i * 10, 1475, 100 + i * 10, 0x00ff00, true);
	}

	//DrawBox(1425, 50, 1475, 850, 0xff0000, true);

	//DrawBox(1425, enemyHp, 1475, 850,0x00ff00,true);

	//DrawGraph(1400, 0, m_EnemyHpBarHandle, true);
}

void UI::Draw(std::shared_ptr<Enemy>enemy)
{
	

}
