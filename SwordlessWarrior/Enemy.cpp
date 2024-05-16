#include "Enemy.h"

Enemy::Enemy(int modelhandle):
	m_modelHandle(modelhandle),
	m_enemyUpdate(&Enemy::StartUpdate)
{
	MV1SetPosition(m_modelHandle, VGet(300, 0, 300));
	CollisonSetRadius(m_radius);
	CollisionSetPos(m_pos);
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{

}

void Enemy::Update()
{
	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.2f, 0.2f, 0.2f));//XYZそれぞれ1/5スケール
	MV1SetMatrix(m_modelHandle, scaleMtx);

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

void Enemy::OnDamageUpdate()
{

}

//攻撃

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
