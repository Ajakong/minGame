#pragma once
#include "Object.h"
#include<iostream>
#include<list>

using namespace std;

class Player;
class EnemyAttackBox;
class EnemyAttackSphere;
class FightBackObj;

/// <summary>
/// ReadMe:Enemy.cpp,GameManager.cpp以外でincludeしない
/// </summary>
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

	void HitFightBackObj(int Damege);

	void SetCameraAngle(float cameraAngle);

	void SetAttackDir(VECTOR targetPos);
	VECTOR GetMyPos();
	int WatchHp() const { return m_Hp; }
	float GetColRadius() { return m_radius; }

	float GetIdleSpeed() { return m_idleSpeed; }


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
	/// <summary>
	/// 爆弾を上から投下して攻撃
	/// </summary>
	void AttackBombUpdate();

	VECTOR GetAttackDir() const;
private:
	int m_Hp;

	int m_attackCoolDownCount;

	float m_radius=0;

	int m_modelHandle = 0;

	int m_createFrameCount = 0;

	float m_centerToEnemyAngle;

	float m_idleSpeed = 0;

	int m_sphereNum = 0;
	int m_bombNum = 0;

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
	EnemyAttackSphere(std::shared_ptr<Object>enemy,VECTOR pos,VECTOR velocity,int moveNum,int color=0xff0000);
	virtual ~EnemyAttackSphere();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void Hit();

	virtual bool IsDelete() { return m_isDeleteFlag; }

	//メンバ関数ポインタ
	using MoveState_t = void(EnemyAttackSphere::*)();
	MoveState_t m_moveUpdate;

protected:
	void  StraightUpdate();//球を直線状に飛ばす

protected:
	

	int m_color = 0;
	bool m_isDeleteFlag = 0;

	float m_radius = 0;

	VECTOR m_velocity;
	std::shared_ptr<Enemy>m_enemy;

private:
	void DeleteJudge();

private:
	
};

/// <summary>
/// Playerが取得後、周囲を周ったのちにEnemyに攻撃するオブジェクト
/// </summary>
class FightBackObj :public EnemyAttackSphere
{
public:
	FightBackObj(std::shared_ptr<Object>enemy,VECTOR pos, VECTOR velocity,int moveNum,int color);
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
	/// <summary>
	/// コンストラクタのVelocityの軌道で飛ぶ
	/// </summary>
	void MoveUpdate();
	/// <summary>
	/// Enemyに向かって飛んでいく
	/// </summary>
	void FightBackUpdate();
	/// <summary>
	/// 取得後、周囲を回転
	/// </summary>
	void TurnUpdate();
protected:
	int m_color = 0xff0000;

	

	float m_centerAngle;

	int m_speed=0;

private:
	bool m_isTransFlag = false;

	int m_turnFrame = 0;

};

class EnemyAttackBomb :public EnemyAttackSphere
{
public:
	EnemyAttackBomb(std::shared_ptr<Object>enemy, VECTOR pos, VECTOR velocity, int moveNum, int color=0xff0000);
	~EnemyAttackBomb();

	void Init();
	void Update();
	void Draw();

	void Hit();

	//メンバ関数ポインタ
	using MoveState_t = void(EnemyAttackBomb::*)();
	MoveState_t m_moveUpdate;

private:
	void MoveUpdate();
	void ExplosionUpdate();

private:
	

};

