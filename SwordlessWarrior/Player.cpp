#include "Player.h"
#include"Physic.h"
#include<list>
#include <functional>
#include"NameTag.h"
#include"Pad.h"
#include"Vec2.h"

#include<math.h>

namespace
{
	//モデルのファイル名
	const char* const kRunFilePath = "model/Run.mv1";

	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;
	//constexpr int kIdleAnimIndex = 2;//待機テスト
	constexpr int kAttackAnimIndex = 30;

	constexpr float kAnimFrameSpeed = 30.0f;//アニメーション進行速度

	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//アナログスティックによる移動関連
	constexpr float kMaxSpeed = 0.05f;//プレイヤーの最大速度
	constexpr float kAnalogRangeMin = 0.1f;//アナログスティックの入力判定範囲
	constexpr float kAnalogRangeMax = 0.8f;
	constexpr float kAnalogInputMax = 1000.0f;//アナログスティックから入力されるベクトルの最大値

	constexpr float frameParSecond = 60.0f;
}

Player::Player(int modelhandle) :Object(modelhandle),
	m_playerUpdate(&Player::IdleUpdate),
	m_velocity(VGet(0,0,0)),
	m_cameraAngle(0)
{
	MV1SetPosition(m_modelHandle, VGet(0, 0, 0));
	m_anim_move = MV1LoadModel(kRunFilePath);
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

	Pad::Update();
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
	int total = MV1GetAttachAnimTotalTime(m_modelHandle,m_attach_move);
	
	UpdateAnim(0);

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

bool Player::UpdateAnim(int attachNo)
{
	//アニメーションが設定されていないので終了
	if (attachNo == -1) return false;

	//アニメーションを進行させる
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);//現在の再生カウント
	now += kAnimFrameSpeed / frameParSecond;//アニメーションカウントを進める

	//現在再生中のアニメーションの総カウントを取得する
	float total = MV1GetAttachAnimTotalTime(m_modelHandle, attachNo);
	bool isLoop = false;
	while (now >= total)
	{
		now -= total;
		isLoop = true;
	}

	MV1SetAttachAnimTime(m_modelHandle, attachNo, now);

	return isLoop;
}

void Player::ChangeAnim(int animIndex)
{
	//さらに古いアニメーションがアタッチされている場合はこの時点で削除しておく
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevAnimNo);
	}

	//現在再生中の待機アニメーションは変更前のアニメーション扱いに
	m_prevAnimNo = m_currentAnimNo;

	//変更後のアニメーションとして攻撃アニメーションを改めて設定する
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, animIndex, -1, false);

	//切り替えの瞬間は変更前のアニメーションが再生される状態にする
	m_animBlendRate = 0.0f;

	//変更前のアニメーション100%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//変更後のアニメーション0%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimNo, m_animBlendRate);

}

