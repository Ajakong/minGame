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
	
	/// <param name="m_modelhandle">エネミーのモデル</param>
	/// <param name="obj">影響を与えるオブジェ</param>
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

	//メンバ関数ポインタ
	using enemyState_t = void(Enemy::*)();
	enemyState_t m_enemyUpdate;
private:
	/// <summary>
	/// 登場時
	/// </summary>
	void StartUpdate();
	/// <summary>
	/// 通常(クールダウン)状態
	/// </summary>
	void IdleUpdate();
	/// <summary>
	/// ダメージを受けた時
	/// </summary>
	void OnDamageUpdate();
	/// <summary>
	/// 球体を生成して攻撃
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

	//アニメーション変数
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_jump = 0;
	int m_anim_attack = 0;

	std::list<std::shared_ptr<EnemyAttackSphere>> m_sphere;
	std::shared_ptr<Object>m_obj;//影響を与えたいObject
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
/// Enemyが攻撃の際に生成する球体オブジェクト
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

	//メンバ関数ポインタ
	using MoveState_t = void(EnemyAttackSphere::*)();
	MoveState_t m_moveUpdate;

private:
	void  StraightUpdate();//球を直線状に飛ばす

private:
	

	float m_radius = 0;


	VECTOR m_velocity;
	std::shared_ptr<Enemy>m_enemy;
};

/// <summary>
/// Playerが取得でEnemyにダメージ
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

	//メンバ関数ポインタ
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

