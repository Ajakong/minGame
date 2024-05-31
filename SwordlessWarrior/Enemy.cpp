#include "Enemy.h"

namespace
{
	constexpr float kSphereRadius = 10;
	constexpr int kSphereCreateFrame = 50;

	constexpr float kFightBackObjRadius = 10;

	constexpr int kAttackCoolDownTime = 60;

}

/*プロトタイプ宣言*/
VECTOR ToVec(VECTOR a, VECTOR b);
VECTOR norm(VECTOR a);

Enemy::Enemy(int modelhandle,std::shared_ptr<Object> obj):
	m_obj(obj),
	m_modelHandle(MV1DuplicateModel(modelhandle)),
	m_anim_nutral(Loader::GetAnimationFalling()),
	m_enemyUpdate(&Enemy::StartUpdate),
	m_Hp(50),
	m_radius(kSphereRadius),
	m_attackCoolDownCount(0),
	m_attackDir(VGet(1.0f,0.0f,0.0f)),
	m_centerToEnemyAngle(0),
	m_idleSpeed(1.0f)
{
	m_tag = Tag::Enemy;
	m_pos = VGet(200, 50, 0);
	MV1SetPosition(m_modelHandle,m_pos );
	CollisonSetRadius(m_radius);
	CollisionSetPos(m_pos);

	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/5スケール

	MV1SetMatrix(m_modelHandle,scaleMtx);
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);

}

void Enemy::Init()
{
	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/5スケール
	//m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//オブジェクトに向かうベクトルを正規化したもの

	float Angle =-90-atan2(m_attackDir.z,m_attackDir.x );
	m_centerToEnemyAngle += m_idleSpeed;

	float Length = sqrt(m_pos.x * m_pos.x + m_pos.z * m_pos.z);

	m_pos.x = Length * static_cast<float>(cos(m_centerToEnemyAngle *DX_PI_F / 180.0));
	m_pos.z = Length * static_cast<float>(sin(m_centerToEnemyAngle * DX_PI_F / 180.0));
	
	MATRIX transMtx = MGetTranslate(m_pos);
	MATRIX rotateMtx = MGetRotY(Angle);
	MATRIX Mtx = MMult(scaleMtx, rotateMtx);
	Mtx = MMult(Mtx, transMtx);
	
	MV1SetMatrix(m_modelHandle, Mtx);
}

void Enemy::Update()
{
	(this->*m_enemyUpdate)();

	for (auto& sphere : m_sphere)
	{
		if (m_sphere.size() == 0)return;
		sphere->Update();
		
	}

	//for (auto& sphere : m_sphere)
	//{
	//	if (CheckCameraViewClip(sphere->GetPos()) != 0)
	//	{
	//		m_sphereNum--;
 //			m_sphere.remove(sphere);
	//	}
	//}
	
	m_sphere.remove_if([this](const auto& sphere)
		{
			bool isOut = CheckCameraViewClip(sphere->GetPos()) != 0;
			if (isOut)
			{
				//m_sphereNum--;
			}
			return isOut;
		});
}

void Enemy::Draw()
{
	MV1DrawModel(m_modelHandle);

	for (auto& sphere : m_sphere)
	{
		sphere->Draw();
	}
}

void Enemy::WantToPlayer(VECTOR cameraToPlayer)
{

}

void Enemy::Hit()
{
	m_Hp -= 10;
	printfDx("EnemyIsHit");
}

void Enemy::SetCameraAngle(float cameraAngle)
{
}

void Enemy::SetAttackDir(VECTOR targetPos)
{
	m_attackDir = norm(ToVec(GetMyPos(), targetPos));
}

VECTOR Enemy::GetMyPos()
{
	return VGet(m_pos.x,m_pos.y+30,m_pos.z);
}

void Enemy::StartUpdate()
{
	m_velocity.y = -1;

	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/5スケール
	m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//オブジェクトに向かうベクトルを正規化したもの

	float Angle = -90 - atan2(m_attackDir.z, m_attackDir.x);
	
	m_pos.y += m_velocity.y;

	MATRIX transMtx = MGetTranslate(m_pos);
	MATRIX rotateMtx = MGetRotY(Angle);
	MATRIX Mtx = MMult(scaleMtx, rotateMtx);
	Mtx = MMult(Mtx, transMtx);

	MV1SetMatrix(m_modelHandle, Mtx);

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_enemyUpdate = &Enemy::AttackSphereUpdate;
	}
}

void Enemy::IdleUpdate()
{
	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/5スケール
	//m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//オブジェクトに向かうベクトルを正規化したもの
	/*VECTOR tovec= ToVec(m_pos, m_obj->GetPos());
	m_centerToEnemyAngle = atan2(tovec.z, tovec.x);*/

	float Angle =-90-atan2(m_attackDir.z,m_attackDir.x );
	m_centerToEnemyAngle += m_idleSpeed;

	float Length = sqrt(m_pos.x * m_pos.x + m_pos.z * m_pos.z);

	m_pos.x = Length * static_cast<float>(cos(m_centerToEnemyAngle *DX_PI_F / 180.0));
	m_pos.z = Length * static_cast<float>(sin(m_centerToEnemyAngle * DX_PI_F / 180.0));
	
	MATRIX transMtx = MGetTranslate(m_pos);
	MATRIX rotateMtx = MGetRotY(Angle);
	MATRIX Mtx = MMult(scaleMtx, rotateMtx);
	Mtx = MMult(Mtx, transMtx);
	
	MV1SetMatrix(m_modelHandle, Mtx);

	//MV1SetPosition(m_modelHandle, VGet(m_pos.x, m_pos.y, m_pos.z));

	m_attackCoolDownCount++;

	if (m_attackCoolDownCount > kAttackCoolDownTime)
	{
		m_attackCoolDownCount = 0;
		m_enemyUpdate = &Enemy::AttackSphereUpdate;
	}
}

void Enemy::OnDamageUpdate()
{

}

void Enemy::AttackSphereUpdate()
{
	m_createFrameCount++;
	if (m_createFrameCount > kSphereCreateFrame)
	{
		m_sphereNum++;
		if (m_sphereNum <= 5)
		{
			m_attackDir = GetAttackDir();//オブジェクトに向かうベクトルを正規化したもの

			m_createFrameCount = 0;
			m_sphere.push_back(std::make_shared<EnemyAttackSphere>(shared_from_this(), GetMyPos(), m_attackDir, 1));
		}	
		else
		{
			m_sphere.push_back(std::make_shared<FightBackObj>(shared_from_this(), GetMyPos(), m_attackDir, 1, 0x00ff00));
			m_sphereNum = 0;
			m_idleSpeed = static_cast<float>(GetRand(19)+1);
			m_enemyUpdate = &Enemy::IdleUpdate;
		}
	}
}

VECTOR Enemy::GetAttackDir() const
{
	VECTOR toVec = ToVec(m_pos, m_obj->GetPos());
	VECTOR vec = norm(ToVec(m_pos, m_obj->GetPos()));
	vec = VGet(vec.x * abs(toVec.x), vec.y * abs(toVec.y), vec.z * abs(toVec.z));
	return vec;
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

EnemyAttackSphere::EnemyAttackSphere(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum,int color): Object(pos),
	m_enemy(std::dynamic_pointer_cast<Enemy>(enemy)),
	m_radius(kSphereRadius),
	m_velocity(velocity)
{
	m_tag = Tag::EnemyAttackSphere;
	m_color = color;
	//if (moveNum == 0)
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
	DrawSphere3D(m_pos, kSphereRadius, 10, 0xffff00, m_color, false);
}

void EnemyAttackSphere::Hit()
{
}

void EnemyAttackSphere::StraightUpdate()
{
	m_pos = VAdd(m_pos, VGet(m_velocity.x*20,m_velocity.y*20,m_velocity.z*20));

	CollisionSetPos(m_pos);
}


/*FightBackObject*/

FightBackObj::FightBackObj(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity,int moveNum,int color):EnemyAttackSphere(enemy,pos,velocity,moveNum,color),
	m_enemy(std::dynamic_pointer_cast<Enemy>(enemy)),
	m_radius(kFightBackObjRadius),
	m_velocity(velocity)
{
	m_tag = Tag::FightBackObj;
	m_color = color;
	CollisonSetRadius(m_radius);
	m_moveUpdate = &FightBackObj::StraightUpdate;
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
	DrawSphere3D(m_pos, kSphereRadius, 10, 0xffff00, m_color, false);

}

void FightBackObj::Hit()
{
	if (!m_isTransFlag)
	{
		m_moveUpdate = &FightBackObj::FightBackUpdate;
		m_velocity = norm(ToVec(m_pos, m_enemy->GetPos()));
		m_velocity = VGet(m_velocity.x * 5, m_velocity.y+5, m_velocity.z * 5);
		m_isTransFlag = true;
	}
	else
	{
		//プレイヤーが取得後にカウンター挙動

	}
}

void FightBackObj::MoveUpdate()
{
	VAdd(m_pos , m_velocity);
}

void FightBackObj::FightBackUpdate()
{
	m_velocity.y--;
	VAdd(m_pos, m_velocity);
}

/*便利関数*/
//aからbへ向かうベクトル
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
	return VGet(a.x / num, a.y / num, a.z  / num);
}

