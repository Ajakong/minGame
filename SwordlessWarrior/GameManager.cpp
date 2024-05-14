#include"Loader.h"

#include "GameManager.h"

#include"Physic.h"
#include"Player.h"
#include"Enemy.h"
#include"SkyDome.h"
#include"Camera.h"
#include"Pad.h"

namespace nameTag
{
	const char* Player = "Player";
	const char* Enemy = "Enemy";
}

GameManager::GameManager():
	pPhysic(std::make_shared<Physic>()),
	pPlayer(std::make_shared<Player>(Loader::GetPlayerHandle())),
	pEnemy(std::make_shared<Enemy>(Loader::GetEnemyHandle())),
	pCamera(std::make_shared<Camera>()),
	m_stageHandle(Loader::GetStageHandle()),
	pSkyDome(std::make_shared<SkyDome>())
{
	pPhysic->Entry(pPlayer,nameTag::Player);
	pPhysic->Entry(pEnemy, nameTag::Enemy);

}

GameManager::~GameManager()
{

}

void GameManager::Init()
{
	pPlayer->Init();
	pPlayer->WantCameraToPlayer(pCamera->cameraToPlayer(pPlayer));
	
	pEnemy->Init();
}

void GameManager::Update()
{
	pSkyDome->Update();

	pPlayer->SetCameraAngle(pCamera->GetCameraAngle());
	pPlayer->Update();
	pCamera->Update();

	pEnemy->Update();

	
	MV1SetPosition(m_stageHandle, VGet(0, -50, 0));

	pPhysic->Update();

	Pad::Update();
}

void GameManager::Draw()
{
	pSkyDome->Draw();

	pPlayer->Draw();
	pEnemy->Draw();


	MV1DrawModel(m_stageHandle);
}
