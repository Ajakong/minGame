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

};

