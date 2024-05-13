#include "Enemy.h"

Enemy::Enemy(int m_modelhandle):Object(m_modelhandle),
	m_enemyUpdate(&Enemy::StartUpdate)
{
	MV1SetPosition(m_modelHandle, VGet(0, 0, 0));
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Enemy::WantCameratoPlayer(VECTOR cameraToPlayer)
{

}

void Enemy::Hit()
{
}

void Enemy::SetCameraAngle(float cameraAngle)
{
}

void Enemy::StartUpdate()
{
}

void Enemy::IdleUpdate()
{
}
