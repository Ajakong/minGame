#pragma once
#include "DxLib.h"
#include<iostream>

using namespace std;

class Player;

class Camera
{
public:
	Camera();							// �R���X�g���N�^.
	~Camera();							// �f�X�g���N�^.

	void Update(std::shared_ptr<Player> player);	// �X�V.

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }

private:
	VECTOR	pos;			// �|�W�V����.

	float cameraAngle = -DX_PI_F / 2;
	VECTOR velocity = VGet(0,0,0);
};