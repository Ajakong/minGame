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
	//奥行0.1〜1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);

	// FOV(視野角)を60度に
	SetupCamera_Perspective(60.0f * (static_cast<float>(DX_PI_F) / 180.0f));

	pos = VGet(-300, 300, -200);
}

Camera::~Camera()
{
	// 処理なし.
}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(pos,VGet(0,0,0));

}

VECTOR Camera::cameraToPlayer(std::shared_ptr<Player> player)
{
	VECTOR cameraToPlayer = VGet(sqrtf((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)),0.0f, sqrtf((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)));
	return cameraToPlayer;
}
