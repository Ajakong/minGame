#include"Loader.h"

#include "GameManager.h"
#include"Player.h"
#include"Camera.h"


GameManager::GameManager():
	player(std::make_shared<Player>(MV1LoadModel("model/knight.mv1"))),
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
	
}

void GameManager::Update()
{
	player->Update();
	camera->Update(player);

	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}
	MV1SetPosition(m_stageHandle, VGet(0, -50, 0));

}

void GameManager::Draw()
{
	player->Draw();

	MV1DrawModel(m_stageHandle);
}
