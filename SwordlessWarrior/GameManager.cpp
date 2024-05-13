#include"Loader.h"

#include "GameManager.h"
#include"Player.h"
#include"Enemy.h"
#include"Camera.h"


GameManager::GameManager():
	player(std::make_shared<Player>(MV1LoadModel("model/knight.mv1"))),
	enemy(std::make_shared<Enemy>(MV1LoadModel("enemy/idle.mv1"))),
	camera(std::make_shared<Camera>()),
	m_stageHandle(MV1LoadModel("obj/Stage.mv1"))
{
	

}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	player->Init();
	player->WantCameraToPlayer(camera->cameraToPlayer(player));
	
	enemy->Init();
}

void GameManager::Update()
{
	player->SetCameraAngle(camera->GetCameraAngle());
	player->Update();
	camera->Update();

	enemy->Update();

	
	MV1SetPosition(m_stageHandle, VGet(0, -50, 0));

}

void GameManager::Draw()
{
	player->Draw();
	enemy->Draw();

	MV1DrawModel(m_stageHandle);
}
