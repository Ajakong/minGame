#include "Player.h"
#include"Pad.h"
#include"Vec2.h"

namespace
{
	constexpr int kNetralRadius = 0;//�ʏ펞�̓����蔼�a

	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimIndex = 1;
	//constexpr int kIdleAnimIndex = 2;//�ҋ@�e�X�g
	constexpr int kAttackAnimIndex = 30;

	constexpr float kAnimFrameSpeed = 30.0f;//�A�j���[�V�����i�s���x

	//�A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//�A�i���O�X�e�B�b�N�ɂ��ړ��֘A
	constexpr float kMaxSpeed = 10.0f;//�v���C���[�̍ő呬�x
	constexpr float kAnalogRangeMin = 0.1f;//�A�i���O�X�e�B�b�N�̓��͔���͈�
	constexpr float kAnalogRangeMax = 0.8f;
	constexpr float kAnalogInputMax = 1000.0f;//�A�i���O�X�e�B�b�N������͂����x�N�g���̍ő�l

	constexpr float frameParSecond = 60.0f;
}


Player::Player(int modelhandle) :
	m_modelHandle(MV1DuplicateModel(modelhandle)),
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
	printfDx("PlayerIsHit");
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
	//�A�j���[�V�������ݒ肳��Ă��Ȃ��̂ŏI��
	if (attachNo == -1) return false;

	//�A�j���[�V������i�s������
	float now = MV1GetAttachAnimTime(m_modelHandle, attachNo);//���݂̍Đ��J�E���g
	now += kAnimFrameSpeed / frameParSecond;//�A�j���[�V�����J�E���g��i�߂�

	//���ݍĐ����̃A�j���[�V�����̑��J�E���g���擾����
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
	//����ɌÂ��A�j���[�V�������A�^�b�`����Ă���ꍇ�͂��̎��_�ō폜���Ă���
	if (m_prevAnimNo != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevAnimNo);
	}

	//���ݍĐ����̑ҋ@�A�j���[�V�����͕ύX�O�̃A�j���[�V����������
	m_prevAnimNo = m_currentAnimNo;

	//�ύX��̃A�j���[�V�����Ƃ��čU���A�j���[�V���������߂Đݒ肷��
	m_currentAnimNo = MV1AttachAnim(m_modelHandle, animIndex, -1, false);

	//�؂�ւ��̏u�Ԃ͕ύX�O�̃A�j���[�V�������Đ�������Ԃɂ���
	m_animBlendRate = 0.0f;

	//�ύX�O�̃A�j���[�V����100%
	MV1SetAttachAnimBlendRate(m_modelHandle, m_prevAnimNo, 1.0f - m_animBlendRate);
	//�ύX��̃A�j���[�V����0%
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
	//�A�i���O�X�e�B�b�N���g���Ĉړ�

	int analogX = 0, analogY = 0;

	GetJoypadAnalogInput(&analogX, &analogY, DX_INPUT_PAD1);

	//�A�i���O�X�e�B�b�N�̓���10%~80%���g�p����
	//�x�N�g���̒������ő�1000�ɂȂ�

	//�v���C���[�̍ő�ړ����x��0.01f/frame

	//�x�N�g���̒������擾
	VECTOR move = VGet(static_cast<float>(analogX), 0.0f, static_cast<float>(-analogY));

	float len = VSize(move);
	//�x�N�g���̒�����0.0~1.0�̊����ɕϊ�����
	float rate = len / kAnalogInputMax;

	//�A�i���O�X�e�B�b�N�����Ȕ͈͂����O����
	rate = (rate - kAnalogRangeMin / (kAnalogRangeMax - kAnalogRangeMin));
	rate = min(rate, 1.0f);
	rate = max(rate, 0.0f);

	//�J�����̂���p�x����
	//�R���g���[���[�ɂ��ړ����������肷��
	MATRIX mtx;
	MATRIX scale = MGetScale(VGet(0.5f, 0.5f, 0.5f));
	float angle = fmodf(m_cameraAngle, 360);
	MATRIX rotate = MGetRotY((angle)-DX_PI_F / 2);//�{���̓J�������s��Ő��䂵�A���̍s���Y����]

	//���x������ł���̂ňړ��x�N�g���ɔ��f
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
	//�_���[�W�A�j���[�V�����̂�
	m_playerUpdate = &Player::NeutralUpdate;
	
	
}


/***************************************************************/

//#include "Player.h"
//#include"Physic.h"
//#include<list>
//#include <functional>
//#include"NameTag.h"
//#include"Pad.h"
//#include"Vec2.h"
//
//#include<math.h>
//

//Player::Player(int modelhandle) :
//	m_modelHandle(MV1DuplicateModel(modelhandle)),
//	m_radius(kNetralRadius),
//	m_playerUpdate(&Player::IdleUpdate),
//	m_velocity(VGet(0.0f,0.0f,0.0f)),
//	m_cameraAngle(0),
//	m_Hp(50)
//{
//	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);
//	MATRIX scaleMtx = MGetScale(VGet(0.3f, 0.3f, 0.3f));//XYZ���ꂼ��1/5�X�P�[��
//	mtx = MMult(mtx, scaleMtx);
//	MV1SetMatrix(m_modelHandle, mtx);
//	m_anim_nutral = Loader::GetAnimationIdle();
//	m_attach_nutral=MV1AttachAnim(m_modelHandle,0,m_anim_nutral),
//	m_anim_move = Loader::GetAnimationRun();
//	m_anim_hit = Loader::GetAnimationHit();
//	m_attach_move = MV1AttachAnim(m_modelHandle, 1, m_anim_move);
//	m_attach_hit = MV1AttachAnim(m_modelHandle, 2, m_anim_hit);
//}
//
//Player::~Player()
//{
//	//�����Ȃ�
//}
//
//void Player::Init()
//{
//	//�����Ȃ�
//}
//
//void Player::Update()
//{
//
//	(this->*m_playerUpdate)();
//	Pad::Update();
//}
//
//void Player::Draw()
//{
//	MV1DrawModel(m_modelHandle);
//	DrawSphere3D(m_pos,m_radius, 10, 0x000000, 0x00ffff, false);
//	MakeShadowMap(50, 50);
//}
//
//void Player::WantCameraToPlayer(VECTOR cameraToPlayer)
//{
//	m_cameraToPlayer = cameraToPlayer;
//}
//
//VECTOR Player::GetCameraToPlayer() const
//{
//	return m_cameraToPlayer;
//}
//
//void Player::Hit()
//{
//	printfDx("PlayerIsHit");
//	m_Hp -= 10;
//	ChangeAnim(m_attach_hit);
//	m_playerUpdate = &Player::OnDamageUpdate;
//}
//
//void Player::SetCameraAngle(float cameraAngle)
//{
//	m_cameraAngle = cameraAngle;
//}
//
//void Player::StartUpdate()
//{
//}
//
//void Player::IdleUpdate()
//{
//	int m_inputX = 0;
//	int m_inputY = 0;
//	GetJoypadAnalogInput(&m_inputX, &m_inputY, DX_INPUT_PAD1);
//	Vec2 stickInput((float)m_inputX, -(float)m_inputY);
//	/*if (stickInput.Length() >= 1)
//	{
//		ChangeAnim(m_anim_move);
//		m_playerUpdate = &Player::WalkingUpdate;
//	}*/
//
//	//if (Pad::IsTrigger(PAD_INPUT_1))
//	//{
//	//	ChangeAnim(m_anim_jump);
//	//	m_velocity.y += 50;
//	//	m_playerUpdate = &Player::JumpingUpdate;
//	//}
//
//
//	MATRIX Mtx = MGetTranslate(VGet(1, 0, 0));
//	MATRIX scaleMtx = MGetScale(VGet(0.3f, 0.3f, 0.3f));//XYZ���ꂼ��1/5�X�P�[��
//	Mtx = MMult(Mtx, scaleMtx);
//	m_playerRotateY = atan2((float)m_velocity.x, (float)m_velocity.z);
//
//	MATRIX rotateMtx = MGetRotAxis(m_velocity, m_playerRotateY);
//	Mtx = MMult(Mtx, rotateMtx);
//	
//	MV1SetMatrix(m_modelHandle, Mtx);
//	
//	
//	//MV1SetRotationXYZ(m_modelHandle, VGet(0, m_playerRotateY, 0));
//
//	
//	CollisonSetRadius(m_radius);
//	CollisionSetPos(m_pos);
//
//	UpdateAnim(m_attach_nutral);
//}
//
//void Player::WalkingUpdate()
//{
//	UpdateAnim(m_attach_move);
//
//	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//	if (pad & PAD_INPUT_1)
//	{
//		//�ҋ@�A�j���[�V�������폜���Ă��K�v������
//		//MV1DetachAnim(m_modelHandle, m_currentAnimNo);
//		//m_isAttack = true;
//		//m_currentAnimNo = MV1AttachAnim(m_modelHandle, kAttackAnimIndex, -1, false);
//
//		ChangeAnim(kAttackAnimIndex);
//	}
//	else

//
//}
//
//void Player::JumpingUpdate()
//{
//	m_velocity.y -= 5;
//	MV1SetPosition(m_modelHandle, m_pos);
//	if (m_pos.y < 0)
//	{
//		ChangeAnim(m_anim_nutral);
//		m_pos.y = 0;
//		m_playerUpdate = &Player::IdleUpdate;
//	}
//
//	CollisionSetPos(m_pos);
//	UpdateAnim(m_anim_jump);
//}
//
//void Player::OnDamageUpdate()
//{
//	UpdateAnim(m_attach_hit);
//}
//
//bool Player::UpdateAnim(int attachNo)
//{
//}
//
//void Player::ChangeAnim(int animIndex)
//{
//}
//

