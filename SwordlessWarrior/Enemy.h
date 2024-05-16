#pragma once
#include "Object.h"
class Enemy : public Object
{
public:
	Enemy(int m_modelhandle);
	~Enemy();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPos()const { return m_pos; }
	void WantCameratoPlayer(VECTOR cameraToPlayer);

	void Hit();

	void SetCameraAngle(float cameraAngle);

	//メンバ関数ポインタ
	using enemyState_t = void(Enemy::*)();
	enemyState_t m_enemyUpdate;
private:
	void StartUpdate();
	void IdleUpdate();
	void OnDamageUpdate();
private:
	int m_radius=0;

	int m_modelHandle = 0;

	VECTOR m_velocity;

	//アニメーション変数
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_jump = 0;
	int m_anim_attack = 0;


};

class EnemyAttackBox :public Object
{
public:
	EnemyAttackBox();
	~EnemyAttackBox();

	void Init();
	void Update();
	void Draw();

private:
	

	VECTOR m_velocity;
};

