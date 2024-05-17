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
	//‰œs0.1`1000‚Ü‚Å‚ğƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚Æ‚·‚é
	SetCameraNearFar(0.1f, 1000.0f);

	// FOV(‹–ìŠp)‚ğ60“x‚É
	SetupCamera_Perspective(60.0f * (static_cast<float>(DX_PI_F) / 180.0f));

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
	VECTOR cameraToPlayer = VGet(sqrtf((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)),0.0f, sqrtf((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)));
	return cameraToPlayer;
}
