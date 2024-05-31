#pragma once
#include "DxLib.h"
#include<iostream>

using namespace std;

class Player;

class Camera
{
public:
	Camera();							// コンストラクタ.
	~Camera();							// デストラクタ.

	void Update();	// 更新.
	VECTOR cameraToPlayer(std::shared_ptr<Player> player);
	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }

	float GetCameraAngle() const { return cameraAngle; }

private:
	VECTOR	pos;			// ポジション.

	float cameraAngle = -DX_PI_F / 2;
	VECTOR velocity = VGet(0,0,0);

	
};