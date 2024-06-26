#include"Loader.h"

#include "GameManager.h"

#include"Shadow.h"
#include"Physic.h"
#include"Player.h"
#include"Enemy.h"
#include"SkyDome.h"
#include"Camera.h"
#include"UI.h"


namespace nameTag
{
	const char* Player = "Player";
	const char* Enemy = "Enemy";
	const char* EnemyAttackObj = "EnemyAttackObj";
}

GameManager::GameManager():
	pShadow(std::make_shared<Shadow>()),
	pPhysic(std::make_shared<Physic>()),
	pPlayer(std::make_shared<Player>(Loader::GetPlayerHandle())),
	pEnemy(std::make_shared<Enemy>(Loader::GetEnemyHandle(),pPlayer)),
	pCamera(std::make_shared<Camera>()),
	m_stageHandle(Loader::GetStageHandle()),
	pSkyDome(std::make_shared<SkyDome>()),
	pUI(std::make_shared<UI>())
{
	pPhysic->Entry(pPlayer,pPlayer->GetTag());
	pPhysic->Entry(pEnemy, pEnemy->GetTag());

}

GameManager::~GameManager()
{

	pPhysic->Clear();
}

void GameManager::Init()
{
	pShadow->SetLight();

	pPlayer->Init();
	
	pEnemy->Init();

	pEnemy->SetAttackDir(pPlayer->GetPos());

	SetFogEnable(TRUE);					// フォグを有効にする
	SetFogColor(100, 0, 0);			// フォグの色にする
	SetFogStartEnd(0.0f, 3000.0f);	// フォグの開始距離

}

void GameManager::Update()
{
	pSkyDome->Update();

	pPlayer->SetCameraToPlayer(pCamera->cameraToPlayer(pPlayer));

	pPlayer->SetCameraAngle(pCamera->GetCameraAngle());
	pPlayer->Update();
	pCamera->Update();


	pEnemy->Update();

	for (auto& obj : pEnemy->GetAttackObj())
	{
		pPhysic->Entry(obj, obj->GetTag());
	}

	MV1SetPosition(m_stageHandle, VGet(0, -50, 0));

	pPhysic->Update();

	if (pPlayer->WatchHp() <= 0)
	{
		m_isGameOverFlag = true;
	}
	if (pEnemy->WatchHp() <= 0)
	{
		m_isClearFlag = true;
	}
	
}

void GameManager::Draw()
{

	pSkyDome->Draw();

	pShadow->Draw();

	pPlayer->Draw();
	pEnemy->Draw();
	MV1DrawModel(m_stageHandle);

	pShadow->DrawEnd();

	pShadow->UseShadowMap();

	pPlayer->Draw();
	pEnemy->Draw();
	MV1DrawModel(m_stageHandle);

	pShadow->Fin();

	pUI->DrawEnemyHp(pEnemy->WatchHp(),pPlayer->WatchHp());

}
