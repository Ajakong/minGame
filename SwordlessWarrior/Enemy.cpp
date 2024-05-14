#include "Enemy.h"

Enemy::Enemy(int modelhandle):
	m_modelHandle(modelhandle),
	m_enemyUpdate(&Enemy::StartUpdate)
{
	MV1SetPosition(m_modelHandle, VGet(300, 0, 300));
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
	printfDx("EnemyIsHit");
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

//çUåÇ

EnemyAttackBox::EnemyAttackBox()
{
}

EnemyAttackBox::~EnemyAttackBox()
{
}

void EnemyAttackBox::Init()
{
}

void EnemyAttackBox::Update()
{
}

void EnemyAttackBox::Draw()
{
}
