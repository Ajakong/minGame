#include "Camera.h"
#include"Pad.h"
#include <math.h>
#include"Player.h"


namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;

	constexpr float kCameraNear = 1.0f;
	constexpr float kCameraFar = 1000.0f;

	//constexpr VECTOR kFirstPos=VGet(300, 300, -200);

	constexpr float kCameraFOV = 60.0f;
}

Camera::Camera()
{
	SetCameraNearFar(kCameraNear, kCameraFar);//•`‰æ‚·‚é•K—v‚ª‚ ‚éêŠ‚Ü‚Å‹——£‚ª‚ ‚é‚Ì‚Å0.1‚È‚Ç–³‘Ê‚É’·‚­‚µ‚È‚¢

	// FOV(‹–ìŠp)‚ğ60“x‚É
	SetupCamera_Perspective(kCameraFOV * (static_cast<float>(DX_PI_F) / 180.0f));

	pos = VGet(-300, 300, -200);
}

Camera::~Camera()
{
	// ˆ—‚È‚µ.
}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(pos,VGet(0,0,0));

}

VECTOR Camera::cameraToPlayer(std::shared_ptr<Player> player)
{
	VECTOR cameraToPlayer = VGet(sqrt((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)),0.0f, sqrt((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)));
	return cameraToPlayer;
}
