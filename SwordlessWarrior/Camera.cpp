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

	constexpr float kcameraRotateSpeed = 0.05f;
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

	//if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT))
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
	{
		cameraAngle += kcameraRotateSpeed;
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_6))
	{
		cameraAngle -= kcameraRotateSpeed;
	}

	SetCameraNearFar(kCameraNear, kCameraFar);
	VECTOR cameraPos;

	float Length = sqrt(pos.x * pos.x + pos.z * pos.z);
	

	cameraPos.x = Length * static_cast<float>(cos(-fmodf(cameraAngle, 360)));
	cameraPos.z = Length * static_cast<float>(sin(-fmodf(cameraAngle, 360)));
	cameraPos.y = 300;
	pos = cameraPos;
	SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0,20,0));

}

VECTOR Camera::cameraToPlayer(std::shared_ptr<Player> player)
{

	VECTOR cameraToPlayer = VGet(sqrt((player->GetPos().x - pos.x) * (player->GetPos().x - pos.x)),0.0f, sqrt((player->GetPos().z - pos.z) * (player->GetPos().z - pos.z)));
	return cameraToPlayer;
}
