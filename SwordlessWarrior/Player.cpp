#include "Player.h"
#include"Pad.h"
#include"Vec2.h"

namespace
{
	constexpr int kNetralRadius = 0;//通常時の当たり半径

	//アニメーション番号
	constexpr int kIdleAnimIndex = 1;
	//constexpr int kIdleAnimIndex = 2;//待機テスト
	constexpr int kAttackAnimIndex = 30;

	constexpr float kAnimFrameSpeed = 30.0f;//アニメーション進行速度

	//アニメーションの切り替えにかかるフレーム数
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//アナログスティックによる移動関連
	constexpr float kMaxSpeed = 10.0f;//プレイヤーの最大速度
	constexpr float kAnalogRangeMin = 0.1f;//アナログスティックの入力判定範囲
	constexpr float kAnalogRangeMax = 0.8f;
	constexpr float kAnalogInputMax = 1000.0f;//アナログスティックから入力されるベクトルの最大値

	constexpr float frameParSecond = 60.0f;
}


Player::Player(int modelhandle) :
	m_modelHandle(MV1DuplicateModel(modelhandle)),
	m_anim_move(Loader::GetAnimationRun()),
	m_radius(30),
	m_Hp(50),
	m_playerUpdate(&Player::NeutralUpdate)
{
	m_tag = Tag::Player;
}

Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	m_pos = VGet(0, 0, 0);

}

void Player::Update()
{
	(this->*m_playerUpdate)();

	Pad::Update();

	if (m_visibleCount > 200)
	{
		m_isVisibleFlag = false;
		m_visibleCount = 0;
	}
	if (m_isVisibleFlag)
	{
		m_visibleCount++;
	}
	else
	{
		CollisonSetRadius(m_radius);
		CollisionSetPos(VGet(m_pos.x, m_pos.y + 20, m_pos.z));
	}
}

void Player::Draw()
{
	if (m_visibleCount % 10 == 0)
	{
		MV1DrawModel(m_modelHandle);
	}
	DrawSphere3D(m_pos,m_radius, 10, 0x000000, 0x00ffff, false);
	MakeShadowMap(50, 50);
}

void Player::SetCameraToPlayer(VECTOR cameraToPlayer)
{
	m_cameraToPlayer = cameraToPlayer;
}

void Player::Hit()
{
	/*printfDx("PlayerIsHit");*/
	m_Hp -= 10;
	m_isVisibleFlag = true;
	m_isHitFlag=false;
	
	ChangeAnim(m_attach_hit);
	m_playerUpdate = &Player::HitUpdate;
}

void Player::SetCameraAngle(float cameraAngle)
{
	m_cameraAngle = cameraAngle;
}

VECTOR Player::GetCameraToPlayer() const
{
	return m_cameraToPlayer;
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

void Player::StartUpdate()
{
}

void Player::IdleUpdate()
{
}

void Player::NeutralUpdate()
{
	//アナログスティックを使って移動

	int analogX = 0, analogY = 0;

	GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

	//アナログスティックの入力10%~80%を使用する
	//ベクトルの長さが最大1000になる

	//プレイヤーの最大移動速度は0.01f/frame

	//ベクトルの長さを取得
	VECTOR move = VGet(static_cast<float>(analogX), 0.0f, static_cast<float>(-analogY));

	float len = VSize(move);
	//ベクトルの長さを0.0~1.0の割合に変換する
	float rate = len / kAnalogInputMax;

	//アナログスティック無効な範囲を除外する
	rate = (rate - kAnalogRangeMin / (kAnalogRangeMax - kAnalogRangeMin));
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	//カメラのいる角度から
	//コントローラーによる移動方向を決定する
	MATRIX mtx;
	MATRIX scale = MGetScale(VGet(0.5f, 0.5f, 0.5f));
	float angle = fmodf(m_cameraAngle, 360);
	MATRIX rotate = MGetRotY((angle)-DX_PI_F / 2);//本来はカメラを行列で制御し、その行列でY軸回転

	//速度が決定できるので移動ベクトルに反映
	move = VNorm(move);
	float speed = kMaxSpeed * rate;

	move = VScale(move, speed);

	move = VTransform(VGet(move.x, 0, move.z), rotate);
	m_velocity = move;

	m_pos = VAdd(m_pos, m_velocity);

	//move = VTransform(VGet(m_velocity.x+m_pos.x, m_velocity.y, m_velocity.z+m_pos.z), rotate);
	MATRIX moveDir = MGetRotY((angle)+DX_PI_F / 2);
	mtx = MMult(scale, moveDir);

	MATRIX moving = MGetTranslate(m_pos);

	mtx = MMult(mtx, moving);

	MV1SetMatrix(m_modelHandle, mtx);


	m_velocity.x = 0;
	m_velocity.y = 0;
	
}

void Player::WalkingUpdate()
{
}

void Player::JumpingUpdate()
{
}

void Player::HitUpdate()
{
	//ダメージアニメーションのみ
	m_playerUpdate = &Player::NeutralUpdate;
	
	
}
