#include "Enemy.h"

namespace
{
	constexpr float kSphereRadius = 50;

	constexpr float kFightBackObjRadius = 10;

	constexpr int kAttackCoolDownTime = 300;

}

/*プロトタイプ宣言*/
VECTOR ToVec(VECTOR a, VECTOR b);
VECTOR norm(VECTOR a);

Enemy::Enemy(int modelhandle,std::shared_ptr<Object> obj):
	m_obj(obj),
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
	(this->*m_enemyUpdate)();
}

void Enemy::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Enemy::WantToPlayer(VECTOR cameraToPlayer)
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
	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.2f, 0.2f, 0.2f));//XYZそれぞれ1/5スケール
	MV1SetMatrix(m_modelHandle, scaleMtx);

	m_attackCoolDownCount++;

	if (m_attackCoolDownCount > kAttackCoolDownTime)
	{
		m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//オブジェクトに向かうベクトルを正規化したもの
		m_enemyUpdate = &Enemy::AttackSphereUpdate;
	}
}

void Enemy::OnDamageUpdate()
{

}

void Enemy::AttackSphereUpdate()
{
	m_sphere.push_back(std::make_shared<EnemyAttackSphere>(shared_from_this(), m_pos, m_attackDir, 1));
	
	for (auto& sphere : m_sphere)
	{
		if (CheckCameraViewClip(sphere->GetPos()) != 0)
		{
			m_sphere.pop_front();
		}
	}
}

EnemyAttackBox::EnemyAttackBox(std::shared_ptr<Enemy>enemy)
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

/*EnemyAttackSphere*/

EnemyAttackSphere::EnemyAttackSphere(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum): Object(pos),
	m_enemy(std::dynamic_pointer_cast<Enemy>(enemy)),
	m_radius(kSphereRadius),
	m_velocity(velocity)
{
	
	if (moveNum == 0)
	{
		m_moveUpdate = &EnemyAttackSphere::StraightUpdate;
	}
	CollisonSetRadius(m_radius);
}

EnemyAttackSphere::~EnemyAttackSphere()
{
}

void EnemyAttackSphere::Init()
{
}

void EnemyAttackSphere::Update()
{
	(this->*m_moveUpdate)();
}

void EnemyAttackSphere::Draw()
{
	DrawSphere3D(m_pos, m_radius, 10, 0xffff00, 0xff0000, false);
}

void EnemyAttackSphere::Hit()
{
}

void EnemyAttackSphere::StraightUpdate()
{
	m_pos = VAdd(m_pos, m_velocity);

	CollisionSetPos(m_pos);
}


/*FightBackObject*/

FightBackObj::FightBackObj(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity):Object(pos),
	m_enemy(std::dynamic_pointer_cast<Enemy>(enemy)),
	m_radius(kFightBackObjRadius),
	m_velocity(velocity)
{
	CollisonSetRadius(m_radius);
}

FightBackObj::~FightBackObj()
{
}

void FightBackObj::Init()
{
}

void FightBackObj::Update()
{
	(this->*m_moveUpdate)();
	CollisionSetPos(m_pos);
}

void FightBackObj::Draw()
{
}

void FightBackObj::Hit()
{
	if (!m_isTransFlag)
	{
		m_moveUpdate = &FightBackObj::FightBackUpdate;
		m_velocity = norm(ToVec(m_pos, m_enemy->GetPos()));
	}
	else
	{

	}
	
}

void FightBackObj::MoveUpdate()
{
	VAdd(m_pos , m_velocity);
}

void FightBackObj::FightBackUpdate()
{
	VAdd(m_pos, m_velocity);
}


/*便利関数*/

VECTOR ToVec(VECTOR a, VECTOR b)
{
	float x = (b.x - a.x);
	float y = (b.y - a.y);
	float z = (b.z - a.z);
	return VGet(x, y, z);
}

VECTOR norm(VECTOR a)
{
	float num = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	return VGet(a.x / num, a.y / num, a.z / num);
}

