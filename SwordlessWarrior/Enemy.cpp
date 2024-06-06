#include "Enemy.h"

namespace
{
	/// <summary>
	/// ���̓����蔻�蔼�a
	/// </summary>
	constexpr float kSphereRadius = 10.0f;
	/// <summary>
	/// ���̐����Ԋu
	/// </summary>
	constexpr int kSphereCreateFrame = 50;
	/// <summary>
	/// �{���̓����Ԋu
	/// </summary>
	constexpr int kBombCreateFrame = 70;

	/// <summary>
	/// �����I�u�W�F�N�g�̓����蔻��̑傫��
	/// </summary>
	constexpr float kFightBackObjRadius = 10.0f;

	/// <summary>
	/// �čU���܂ł̃N�[���^�C��
	/// </summary>
	constexpr int kAttackCoolDownTime = 60;

	/// <summary>
	/// �X�e�[�W���f���̏c���T�C�Y/2
	/// </summary>
	constexpr int kStageSizeHalf = 200;

	/// <summary>
	/// �{���𐶐�����ʒu�̍���
	/// </summary>
	constexpr float kBombCreatePosY = 50.0f;


}

/*�v���g�^�C�v�錾*/
VECTOR ToVec(VECTOR a, VECTOR b);
VECTOR norm(VECTOR a);

Enemy::Enemy(int modelhandle, std::shared_ptr<Object> obj) :
	m_obj(obj),
	m_modelHandle(MV1DuplicateModel(modelhandle)),
	m_anim_nutral(Loader::GetAnimationFalling()),
	m_enemyUpdate(&Enemy::StartUpdate),
	m_Hp(70),
	m_radius(kSphereRadius),
	m_attackCoolDownCount(0),
	m_attackDir(VGet(1.0f, 0.0f, 0.0f)),
	m_centerToEnemyAngle(0),
	m_idleSpeed(1.0f)
{
	m_tag = Tag::Enemy;
	m_pos = VGet(200, 50, 0);
	MV1SetPosition(m_modelHandle, m_pos);
	CollisonSetRadius(m_radius);
	CollisionSetPos(m_pos);

	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZ���ꂼ��1/5�X�P�[��

	MV1SetMatrix(m_modelHandle, scaleMtx);
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);

}

void Enemy::Init()
{
	//���f���̃T�C�Y����S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZ���ꂼ��1/5�X�P�[��
	//m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//�I�u�W�F�N�g�Ɍ������x�N�g���𐳋K����������

	float Angle = -90 - atan2(m_attackDir.z, m_attackDir.x);
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
			bool isOut = sphere->IsDelete() == true;

			//if (sphere->GetTag() == Tag::EnemyAttackSphere)
			//{
			//	m_sphereNum--;
			//}
			//if (sphere->GetTag() == Tag::EnemyAttackBomb)
			//{
			//	m_bombNum--;
			//}
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

void Enemy::HitFightBackObj()
{
	m_Hp -= 20;
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
	return VGet(m_pos.x, m_pos.y + 30, m_pos.z);
}

void Enemy::StartUpdate()
{
	m_velocity.y = -1;

	//���f���̃T�C�Y����S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZ���ꂼ��1/5�X�P�[��
	m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//�I�u�W�F�N�g�Ɍ������x�N�g���𐳋K����������

	float Angle = -atan2(m_attackDir.z, m_attackDir.x);

	m_pos.y += m_velocity.y;

	MATRIX transMtx = MGetTranslate(m_pos);
	MATRIX rotateMtx = MGetRotY(Angle);
	MATRIX Mtx = MMult(scaleMtx, rotateMtx);
	Mtx = MMult(Mtx, transMtx);

	MV1SetMatrix(m_modelHandle, Mtx);

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_enemyUpdate = &Enemy::AttackBombUpdate;
	}
}

void Enemy::IdleUpdate()
{
	//���f���̃T�C�Y����S
	MATRIX scaleMtx = MGetScale(VGet(0.5f, 0.5f, 0.5f));//XYZ���ꂼ��1/5�X�P�[��
	//m_attackDir = norm(ToVec(m_pos, m_obj->GetPos()));//�I�u�W�F�N�g�Ɍ������x�N�g���𐳋K����������
	/*VECTOR tovec= ToVec(m_pos, m_obj->GetPos());
	m_centerToEnemyAngle = atan2(tovec.z, tovec.x);*/

	float Angle = -90 - atan2(m_attackDir.z, m_attackDir.x);
	m_centerToEnemyAngle += m_idleSpeed;

	float Length = sqrt(m_pos.x * m_pos.x + m_pos.z * m_pos.z);

	m_pos.x = Length * static_cast<float>(cos(m_centerToEnemyAngle * DX_PI_F / 180.0));
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
		int attackState = GetRand(1);
		if (attackState == 0)
		{
			m_attackCoolDownCount = 0;
			m_enemyUpdate = &Enemy::AttackSphereUpdate;
		}
		else
		{
			m_attackCoolDownCount = 0;
			m_enemyUpdate = &Enemy::AttackBombUpdate;
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
			m_attackDir = GetAttackDir();//�I�u�W�F�N�g�Ɍ������x�N�g���𐳋K����������

			m_createFrameCount = 0;
			m_sphere.push_back(std::make_shared<EnemyAttackSphere>(shared_from_this(), GetMyPos(), m_attackDir, 1));
		}
		else
		{
			m_sphereNum = 0;
			m_sphere.push_back(std::make_shared<FightBackObj>(shared_from_this(), GetMyPos(), m_attackDir, 1, 0x00ff00));

			m_idleSpeed = static_cast<float>(GetRand(19) + 1);
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
	if (m_bombNum == 5)
	{
		m_bombNum = 0;
		m_idleSpeed = static_cast<float>(GetRand(19) + 1);
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
	//moveNum�ɂ���ċ������ς��̂�������Ȃ�(�������邩�킩���)
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
	}
}

/*FightBackObject*/

FightBackObj::FightBackObj(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum, int color) :EnemyAttackSphere(enemy, pos, velocity, moveNum, color),
m_enemy(std::dynamic_pointer_cast<Enemy>(enemy)),
m_radius(kFightBackObjRadius),
m_velocity(velocity),
m_isTransFlag(false)
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
		m_velocity = VGet(m_velocity.x * 5, m_velocity.y + 5, m_velocity.z * 5);
		m_isTransFlag = true;
	}
	else
	{
		//�v���C���[���擾��ɃJ�E���^�[����
		m_enemy->HitFightBackObj();
	}
}

/// <summary>
/// ����񂩂������
/// </summary>
void FightBackObj::MoveUpdate()
{
	VAdd(m_pos, m_velocity);
}

void FightBackObj::FightBackUpdate()
{
	m_velocity.y--;
	VAdd(m_pos, m_velocity);
}

/*�֗��֐�*/
//a����b�֌������x�N�g��
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

EnemyAttackBomb::EnemyAttackBomb(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum, int color) : EnemyAttackSphere(enemy, pos, velocity, moveNum, color)
{
	m_moveUpdate = &EnemyAttackBomb::MoveUpdate;
	m_tag = Tag::EnemyAttackBomb;
}

EnemyAttackBomb::~EnemyAttackBomb()
{
}

void EnemyAttackBomb::Init()
{
}

void EnemyAttackBomb::Update()
{
	(this->*m_moveUpdate)();
	if (m_radius > 50.0f)
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
	VAdd(m_pos, m_velocity);
}

void EnemyAttackBomb::ExplosionUpdate()
{
	m_radius++;
}
