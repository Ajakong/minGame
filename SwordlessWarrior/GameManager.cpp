#include"Loader.h"

#include "GameManager.h"
#include"Player.h"
#include"Camera.h"


GameManager::GameManager():
	player(std::make_shared<Player>(Loader::playerHandle)),
	camera(std::make_shared<Camera>())
{
	

}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	player->Init();
	
}

void GameManager::Update()
{
	player->Update();
	camera->Update(player);
}

void GameManager::Draw()
{
	player->Draw();
}
