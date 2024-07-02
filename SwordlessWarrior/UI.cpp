#include "UI.h"
#include"Loader.h"
namespace
{

}


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

void UI::DrawEnemyHp(int enemyHp,int playerHp)
{
	for (int i = 0; i < enemyHp; i += 10)
	{
		DrawBox(1425, 50 + i * 10, 1475, 100 + i * 10, 0x00ff00, true);
	}

	DrawBox(400, 850, 1200, 870, 0xff0000, true);

	if (playerHp > 20)
	{
		DrawBox(400, 850, 400 + playerHp * 16, 870, 0x00ff00, true);//Player‚ÌHP•`‰æ
	}
	else
	{
		DrawBox(400, 850, 400 + playerHp * 16, 870, 0xffff00, true);//Player‚ÌHP•`‰æ
	}
	
	//DrawGraph(1400, 0, m_EnemyHpBarHandle, true);
}

void UI::Draw(std::shared_ptr<Enemy>enemy)
{
	

}
