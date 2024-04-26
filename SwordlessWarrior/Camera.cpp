#include "Camera.h"
#include"Pad.h"
#include <math.h>
#include"Player.h"


namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;
}

Camera::Camera()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(0.1f, 1000.0f);

	// FOV(����p)��60�x��
	SetupCamera_Perspective(60.0f * (static_cast<float>(DX_PI_F) / 180.0f));

	pos = VGet(-100, 200, -200);
}

Camera::~Camera()
{
	// �����Ȃ�.
}

void Camera::Update(std::shared_ptr<Player> player)
{

	//SetCameraNearFar(1.0f, 180.0f);
	VECTOR cameraPos;
	cameraPos.x = cosf(cameraAngle) * kCameraDist;
	cameraPos.y = kCameraHeight+velocity.y;
	cameraPos.z = sinf(cameraAngle) * kCameraDist;
	SetCameraPositionAndTarget_UpVecY(pos,player->GetPos());

	Pad::Update();
}