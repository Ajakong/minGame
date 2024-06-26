#include "Camera.h"
#include"Pad.h"
#include <math.h>


namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;
}

Camera::Camera()
{
	//奥行0.1〜1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);

	// FOV(視野角)を60度に
	SetupCamera_Perspective(60.0f * (static_cast<float>(DX_PI_F) / 180.0f));

	pos = VGet(0, 0, 0);
}

Camera::~Camera()
{
	// 処理なし.
}

void Camera::Update()
{

	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		cameraAngle += 0.05f;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		cameraAngle -= 0.05f;
	}


	SetCameraNearFar(1.0f, 180.0f);
	VECTOR cameraPos;
	cameraPos.x = cosf(cameraAngle) * kCameraDist;
	cameraPos.y = kCameraHeight;
	cameraPos.z = sinf(cameraAngle) * kCameraDist;
	SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0, 0, 0));

	Pad::Update();
}