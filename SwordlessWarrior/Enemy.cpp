#include "Enemy.h"


namespace
{
	/// <summary>
	/// 最大HP
	/// </summary>
	constexpr int kHp = 80;

	constexpr int kStartPosX = 200;
	constexpr int kStartPosY = 50;
	constexpr int kStartPosZ = 0;

	/// <summary>
	/// 足元からモデルの中心までの距離
	/// </summary>
	constexpr int kFootToCenter = 30;

	/// <summary>
	/// 攻撃クールタイム中の最低移動速度
	/// </summary>
	constexpr int kIdleSpeed = 20;
	/// <summary>
	/// 球の当たり判定半径
	/// </summary>
	constexpr float kSphereRadius = 10.0f;
	/// <summary>
	/// 球の生成間隔
	/// </summary>
	constexpr int kSphereCreateFrame = 50;
	/// <summary>
	/// ボムの投下間隔
	/// </summary>
	constexpr int kBombCreateFrame = 70;

	constexpr float kBombExplodeRadiusMax = 50.0f;

	/// <summary>
	/// 反撃オブジェクトの当たり判定の大きさ
	/// </summary>
	constexpr float kFightBackObjRadius = 10.0f;
	constexpr int kFightBackObjNeutralSpeed = 1000;

	constexpr float kFightBackObjAcceleration = 1.10f;

	/// <summary>
	/// 再攻撃までのクールタイム
	/// </summary>
	constexpr int kAttackCoolDownTime = 60;

	/// <summary>
	/// ステージモデルの縦横サイズ/2
	/// </summary>
	constexpr int kStageSizeHalf = 200;

	/// <summary>
	/// ボムを生成する位置の高さ
	/// </summary>
	constexpr float kBombCreatePosY = 50.0f;
}

/*プロトタイプ宣言*/
VECTOR ToVec(VECTOR a, VECTOR b);
VECTOR norm(VECTOR a);
float lerp(float start, float end, float t);

Enemy::Enemy(int modelhandle, std::shared_ptr<Object> obj) :
	m_obj(obj),
	m_modelHandle(MV1DuplicateModel(modelhandle)),
	m_anim_nutral(Loader::GetAnimationFalling()),
	m_enemyUpdate(&Enemy::StartUpdate),
	m_Hp(kHp),
	m_radius(kSphereRadius),
	m_attackCoolDownCount(0),
	m_attackDir(VGet(1.0f, 0.0f, 0.0f)),
	m_centerToEnemyAngle(0),
	m_idleSpeed(1.0f)
{
	m_tag = Tag::Enemy;
	m_pos = VGet(kStartPosX, kStartPosY, kStartPosZ);
	MV1SetPosition(m_modelHandle, m_pos);
	CollisonSetRadius(m_radius);
	CollisionSetPos(m_pos);
	
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);

}

void Enemy::Init()
{
	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/2スケール
	
	float Angle = -DX_PI_F/2 - atan2(m_attackDir.z, m_attackDir.x);//調整しやすいように90°回転させた角度を取得
	m_centerToEnemyAngle += m_idleSpeed;

	float Length = sqrt(m_pos.x * m_pos.x + m_pos.z * m_pos.z);

	m_pos.x = Length * static_cast<float>(cos(m_centerToEnemyAngle * DX_PI_F / 180.0));
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

	m_sphere.remove_if([this](const auto& sphere)
		{
			bool isOut = sphere->IsDelete() == true;
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
#if _DEBUG
	//printfDx("EnemyIsHit");
#endif
	
}

void Enemy::HitFightBackObj(int Damege=20)
{
	m_Hp -= Damege;
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
	return VGet(m_pos.x, m_pos.y + kFootToCenter, m_pos.z);//モデルの中心の座標
}

void Enemy::StartUpdate()
{
	m_velocity.y = -1;

	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/2スケール
	m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//オブジェクトに向かうベクトルを正規化したもの

	float Angle = -DX_PI_F / 2 -atan2(m_attackDir.z, m_attackDir.x);

	m_pos.y += m_velocity.y;

	MATRIX transMtx = MGetTranslate(m_pos);
	MATRIX rotateMtx = MGetRotY(Angle);
	MATRIX Mtx = MMult(scaleMtx, rotateMtx);
	Mtx = MMult(Mtx, transMtx);

	MV1SetMatrix(m_modelHandle, Mtx);

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_enemyUpdate = &Enemy::IdleUpdate;
	}
}

void Enemy::IdleUpdate()
{
	//モデルのサイズ調整S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZそれぞれ1/2スケール
	
	m_centerToEnemyAngle += m_idleSpeed;
	float Angle = -DX_PI_F / 2 - atan2(GetAttackDir().z, GetAttackDir().x);
	float Length = sqrt(m_pos.x * m_pos.x + m_pos.z * m_pos.z);

	m_pos.x = Length * static_cast<float>(cos(m_centerToEnemyAngle * DX_PI_F / 180.0));
	m_pos.z = Length * static_cast<float>(sin(m_centerToEnemyAngle * DX_PI_F / 180.0));

	MATRIX transMtx = MGetTranslate(m_pos);
	MATRIX rotateMtx = MGetRotY(Angle);
	MATRIX Mtx = MMult(scaleMtx, rotateMtx);
	Mtx = MMult(Mtx, transMtx);

	MV1SetMatrix(m_modelHandle, Mtx);

	m_attackCoolDownCount++;

	if (m_attackCoolDownCount > kAttackCoolDownTime)
	{
		int attackState = GetRand(1);
		switch (attackState)
		{
		case 0:
			m_attackCoolDownCount = 0;
			m_enemyUpdate = &Enemy::AttackSphereUpdate;
		
			/*m_attackCoolDownCount = 0;
			m_enemyUpdate = &Enemy::AttackBombUpdate;*/
		default:
			break;
		}
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
			m_sphereNum = 0;
			m_sphere.push_back(std::make_shared<FightBackObj>(shared_from_this(), GetMyPos(), m_attackDir, 1, 0x00ff00));

			m_idleSpeed = static_cast<float>(GetRand(kIdleSpeed) + 1);//攻撃後の移動速度
			m_enemyUpdate = &Enemy::IdleUpdate;
		}
	}
}

void Enemy::AttackBombUpdate()
{
	m_createFrameCount++;
	if (m_createFrameCount > kBombCreateFrame)
	{
		m_bombNum++;

		m_sphere.push_back(std::make_shared<EnemyAttackBomb>(shared_from_this(),
			VGet(static_cast<float>(GetRand(kStageSizeHalf) - kStageSizeHalf), kBombCreatePosY, static_cast<float>(GetRand(kStageSizeHalf) - kStageSizeHalf)),
			VGet(0, -1, 0), 1));
	}
	if (m_bombNum == 1)
	{
		m_bombNum = 0;
		m_idleSpeed = static_cast<float>(GetRand(kIdleSpeed) + 1);
		m_enemyUpdate = &Enemy::IdleUpdate;
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
	m_tag = Tag::EnemyAttackBox;
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

EnemyAttackSphere::EnemyAttackSphere(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum, int color) : Object(pos),
m_enemy(std::dynamic_pointer_cast<Enemy>(enemy)),
m_radius(kSphereRadius),
m_velocity(velocity)
{
	m_tag = Tag::EnemyAttackSphere;
	m_color = color;
	//moveNumによって挙動が変わるのかもしれない(実装するかわからん)
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
	DeleteJudge();
}

void EnemyAttackSphere::Draw()
{
	DrawSphere3D(m_pos, kSphereRadius, 10, 0xffff00, m_color, false);
}

void EnemyAttackSphere::Hit()
{
	m_isDeleteFlag = true;
	m_isExtinction = true;
}

void EnemyAttackSphere::StraightUpdate()
{
	m_pos = VAdd(m_pos, VGet(m_velocity.x * 20, m_velocity.y * 20, m_velocity.z * 20));

	CollisionSetPos(m_pos);
}

void EnemyAttackSphere::DeleteJudge()
{
	if (CheckCameraViewClip(m_pos) != 0)
	{
		m_isDeleteFlag = true;
		m_isExtinction = true;
	}
}

/*FightBackObject*/

FightBackObj::FightBackObj(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum, int color) :EnemyAttackSphere(enemy, pos, velocity, moveNum, color),
m_isTransFlag(false),
m_speed(kFightBackObjNeutralSpeed)
{
	m_tag = Tag::FightBackObj;
	m_color = color;
	CollisonSetRadius(m_radius);
	m_moveUpdate = &FightBackObj::MoveUpdate;
	m_velocity = VGet(m_velocity.x * 5, m_velocity.y * 5, m_velocity.z * 5);
	VECTOR to = ToVec(m_pos, VAdd(m_pos, VGet(m_velocity.x * 10, m_velocity.y * 10, m_velocity.z * 10)));//進行方向に少し進んだ位置を回転の中心軸とする
	m_centerAngle = atan2(to.z, to.x);
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
	DrawSphere3D(m_pos, kSphereRadius, 10, 0xffffff, m_color, true);

}

void FightBackObj::Hit()
{
	if (!m_isTransFlag)
	{
		m_moveUpdate = &FightBackObj::TurnUpdate;
		
		m_isTransFlag = true;
		m_isHitFlag = false;
	}
	else
	{
		//*応急処置！！
		//ToDo:Playerと当たった際は判定しないようにしたい
		float DisX = (m_pos.x - m_enemy->GetPos().x);
		float DisY = (m_pos.y - m_enemy->GetPos().y);
		float DisZ = (m_pos.z - m_enemy->GetPos().z);
		float Distance = sqrt(DisX * DisX + DisZ * DisZ);
		if (Distance < m_radius + m_enemy->GetColRadius())
		{
			//プレイヤーが取得後にカウンター挙動
			m_enemy->HitFightBackObj();
			m_isDeleteFlag = true;
			m_isExtinction = true;
		}
	}
}

/// <summary>
/// いらんかもしらん
/// </summary>
void FightBackObj::MoveUpdate()
{
	m_pos=VAdd(m_pos, m_velocity);
}

void FightBackObj::FightBackUpdate()
{
	
	m_velocity = norm(ToVec(m_pos, m_enemy->GetPos()));//現在地からEnemyまでの方向ベクトルを取得

	m_speed *= kFightBackObjAcceleration;//徐々にスピードを上げる
	m_velocity = VGet(m_velocity.x * m_speed, m_velocity.y  * m_speed, m_velocity.z  * m_speed);//ToDo:イージングのライブラリを作って使うのが理想
	
	m_pos=VAdd(m_pos, m_velocity);
}

void FightBackObj::TurnUpdate()
{
	m_turnFrame++;
	
	m_centerAngle += 10.0f;//回転軸からの角度を大きくする
	float Length = sqrt(m_pos.x * m_pos.x + m_pos.z * m_pos.z);

	m_pos.x = Length * static_cast<float>(cos(m_centerAngle * DX_PI_F / 180.0));
	m_pos.z = Length * static_cast<float>(sin(m_centerAngle * DX_PI_F / 180.0));
	if (m_turnFrame > 30)
	{
		m_moveUpdate = &FightBackObj::FightBackUpdate;
	}
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
	return VGet(a.x / num, a.y / num, a.z / num);
}

float lerp(float start, float end, float t)
{
	return (1 - t) * start + t * end;
}

EnemyAttackBomb::EnemyAttackBomb(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum, int color) : EnemyAttackSphere(enemy, pos, velocity, moveNum, color)
{
	m_moveUpdate = &EnemyAttackBomb::MoveUpdate;
	m_tag = Tag::EnemyAttackBomb;
	m_radius = 1;
}

EnemyAttackBomb::~EnemyAttackBomb()
{
}

void EnemyAttackBomb::Init()
{
}

void EnemyAttackBomb::Update()
{
	(this->*m_moveUpdate)();//状態関数の実行


	if (m_radius > kBombExplodeRadiusMax)
	{
		m_isDeleteFlag = true;
	}
	if (m_pos.y <= 0)
	{
		m_isDeleteFlag = true;
	}
}

void EnemyAttackBomb::Draw()
{
	DrawSphere3D(m_pos, m_radius, 10, 0xffff00, m_color, false);
}

void EnemyAttackBomb::Hit()
{
	m_moveUpdate = &EnemyAttackBomb::ExplosionUpdate;
	m_color = 0xffff00;
}

void EnemyAttackBomb::MoveUpdate()
{
	m_pos=VAdd(m_pos, m_velocity);
}

void EnemyAttackBomb::ExplosionUpdate()
{
	m_radius++;
}
