#include "Player.h"
#include"Physic.h"
#include<list>
#include <functional>
#include"NameTag.h"
#include"Pad.h"
#include"Vec2.h"

#include<math.h>


Player::Player(int modelhandle) :Object(modelhandle),
	m_playerUpdate(&Player::IdleUpdate),
	m_velocity(VGet(0,0,0)),
	m_cameraAngle(0)
{
	MV1SetPosition(m_modelHandle, VGet(0, 0, 0));
	m_anim_move = MV1LoadModel("model/Run.mv1");
	m_attach_move = MV1AttachAnim(m_modelHandle, 0, m_anim_move);
}

Player::~Player()
{
	Physic::Exit(NameTag::Player);
}

void Player::Init()
{
	Physic::Entry(m_SphereCol, shared_from_this(), NameTag::Player);
}

void Player::Update()
{
	(this->*m_playerUpdate)();
}

void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Player::WantCameraToPlayer(VECTOR cameraToPlayer)
{
	m_cameraToPlayer = cameraToPlayer;
}

VECTOR Player::GetCameraToPlayer() const
{
	return m_cameraToPlayer;
}

void Player::Hit()
{
	
}

void Player::SetCameraAngle(float cameraAngle)
{
	m_cameraAngle = cameraAngle;
}

void Player::StartUpdate()
{
}

void Player::IdleUpdate()
{
	int m_inputX = 0;
	int m_inputY = 0;
	GetJoypadAnalogInput(&m_inputX, &m_inputY, DX_INPUT_PAD1);
	Vec2 stickInput((float)m_inputX, -(float)m_inputY);
	if (stickInput.Length() >= 1)
	{
		m_playerUpdate = &Player::WalkingUpdate;
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_velocity.y += 50;
		m_playerUpdate = &Player::JumpingUpdate;
	}

	MATRIX scaleMtx = MGetScale(VGet(0.2f, 0.2f, 0.2f));//XYZそれぞれ1/5スケール
	MV1SetMatrix(m_modelHandle, scaleMtx);


	MV1SetPosition(m_modelHandle, m_pos);
	m_playerRotateY = atan2f((float)m_velocity.x,(float)m_velocity.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0, m_playerRotateY, 0));
}

void Player::WalkingUpdate()
{
	int m_inputX = 0;
	int m_inputY = 0;
	GetJoypadAnalogInput(&m_inputX, &m_inputY, DX_INPUT_PAD1);
	/*if (m_velocity.x != 0)
	{
		m_velocity.x = m_inputX;

	}*/
	Vec2 stickInput((float)m_inputX, -(float)m_inputY);
	if (stickInput.Length() >= 1)
	{
		m_playerUpdate = &Player::WalkingUpdate;
	}
	else
	{
		m_playerUpdate = &Player::IdleUpdate;
	}
	stickInput.Normalize();

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_velocity.y += 50;
		m_playerUpdate = &Player::JumpingUpdate;
	}

	//ベクトル調整
	m_velocity.x = stickInput.x;
	m_velocity.z = stickInput.y;//上入力で奥に移動
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);//本来はカメラを行列で制御し、その行列でY軸回転
	m_velocity = VTransform(m_velocity, mtx);

	m_playerRotateY = -atan2f((float)m_velocity.z, (float)m_velocity.x )-DX_PI_F/2;

	if (m_velocity.z < 0)
	{
		MV1SetRotationXYZ(m_modelHandle, VGet(0, m_playerRotateY, 0));
	}
	else
	{
		MV1SetRotationXYZ(m_modelHandle, VGet(0, m_playerRotateY, 0));
	}
	
	//アニメーション
	m_playAnimTime += 0.5f;
	if (m_playAnimTime > 16)m_playAnimTime = 0.0f;
	MV1SetAttachAnimTime(m_modelHandle, m_attach_move, m_playAnimTime);

	//モデルのサイズ調整
	MATRIX scaleMtx = MGetScale(VGet(0.2f, 0.2f, 0.2f));//XYZそれぞれ1/5スケール
	MATRIX moveMtx = MGetTranslate(VGet(m_velocity.x*10,m_velocity.y*10,m_velocity.z*10));
	MATRIX modelMtx = MMult(scaleMtx, moveMtx);
	MV1SetMatrix(m_modelHandle, scaleMtx);

}

void Player::JumpingUpdate()
{
	m_velocity.y -= 5;
	MV1SetPosition(m_modelHandle, m_pos);
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_playerUpdate = &Player::IdleUpdate;
	}
}

