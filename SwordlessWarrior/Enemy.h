#pragma once
#include "Object.h"
#include<iostream>
#include<list>

using namespace std;

class Player;
class EnemyAttackBox;
class EnemyAttackSphere;
class FightBackObj;

class Enemy : public Object
{
public:
	
	/// <param name="m_modelhandle">�G�l�~�[�̃��f��</param>
	/// <param name="obj">�e����^����I�u�W�F</param>
	Enemy(int m_modelhandle,std::shared_ptr<Object> obj);
	~Enemy();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos()const { return m_pos; }
	void WantToPlayer(VECTOR toPlayer);

	void Hit();

	void SetCameraAngle(float cameraAngle);

	void SetAttackDir(VECTOR targetPos);
	VECTOR GetMyPos();


	std::list<std::shared_ptr<EnemyAttackSphere>> GetAttackObj() { return m_sphere; }

	//�����o�֐��|�C���^
	using enemyState_t = void(Enemy::*)();
	enemyState_t m_enemyUpdate;
private:
	/// <summary>
	/// �o�ꎞ
	/// </summary>
	void StartUpdate();
	/// <summary>
	/// �ʏ�(�N�[���_�E��)���
	/// </summary>
	void IdleUpdate();
	/// <summary>
	/// �_���[�W���󂯂���
	/// </summary>
	void OnDamageUpdate();
	/// <summary>
	/// ���̂𐶐����čU��
	/// </summary>
	void AttackSphereUpdate();
private:
	int m_Hp;

	int m_attackCoolDownCount;

	float m_radius=0;

	int m_modelHandle = 0;

	int m_createFrameCount = 0;

	VECTOR m_velocity;
	VECTOR m_attackDir;

	//�A�j���[�V�����ϐ�
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_jump = 0;
	int m_anim_attack = 0;

	std::list<std::shared_ptr<EnemyAttackSphere>> m_sphere;
	std::shared_ptr<Object>m_obj;//�e����^������Object
};

class EnemyAttackBox :public Object
{
public:
	EnemyAttackBox(std::shared_ptr<Enemy>enemy );
	~EnemyAttackBox();

	void Init();
	void Update();
	void Draw();

private:
	

	VECTOR m_velocity;
	std::shared_ptr<Enemy>m_enemy;
};

/// <summary>
/// Enemy���U���̍ۂɐ������鋅�̃I�u�W�F�N�g
/// </summary>
class EnemyAttackSphere : public Object
{
public:
	EnemyAttackSphere(std::shared_ptr<Object>enemy,VECTOR pos,VECTOR velocity,int moveNum);
	~EnemyAttackSphere();

	void Init();
	void Update();
	void Draw();

	void Hit();

	//�����o�֐��|�C���^
	using MoveState_t = void(EnemyAttackSphere::*)();
	MoveState_t m_moveUpdate;

private:
	void  StraightUpdate();//���𒼐���ɔ�΂�

private:
	

	float m_radius = 0;


	VECTOR m_velocity;
	std::shared_ptr<Enemy>m_enemy;
};

/// <summary>
/// Player���擾��Enemy�Ƀ_���[�W
/// </summary>
class FightBackObj :public Object
{
public:
	FightBackObj(std::shared_ptr<Object>enemy,VECTOR pos, VECTOR velocity);
	~FightBackObj();

	void Init();
	void Update();
	void Draw();

	void Hit();

	bool GetTransFlag() const { return m_isTransFlag; }

	//�����o�֐��|�C���^
	using MoveState_t = void(FightBackObj::*)();
	MoveState_t m_moveUpdate;

private:
	void MoveUpdate();
	void FightBackUpdate();

private:


	float m_radius = 0;

	bool m_isTransFlag = false;

	VECTOR m_velocity;

	std::shared_ptr<Enemy>m_enemy;
};

