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
	constexpr int kNetralRadius = 50;//�ʏ펞�̓����蔼�a

	//�A�j���[�V�����ԍ�
	constexpr int kIdleAnimIndex = 1;
	//constexpr int kIdleAnimIndex = 2;//�ҋ@�e�X�g
	constexpr int kAttackAnimIndex = 30;

	constexpr float kAnimFrameSpeed = 30.0f;//�A�j���[�V�����i�s���x

	//�A�j���[�V�����̐؂�ւ��ɂ�����t���[����
	constexpr float kAnimChangeFrame = 8.0f;
	constexpr float kAnimChangeRateSpeed = 1.0f / kAnimChangeFrame;

	//�A�i���O�X�e�B�b�N�ɂ��ړ��֘A
	constexpr float kMaxSpeed = 0.05f;//�v���C���[�̍ő呬�x
	constexpr float kAnalogRangeMin = 0.1f;//�A�i���O�X�e�B�b�N�̓��͔���͈�
	constexpr float kAnalogRangeMax = 0.8f;
	constexpr float kAnalogInputMax = 1000.0f;//�A�i���O�X�e�B�b�N������͂����x�N�g���̍ő�l

	constexpr float frameParSecond = 60.0f;
}

Player::Player(int modelhandle) :
	m_modelHandle(MV1DuplicateModel(modelhandle)),
	m_radius(kNetralRadius),
	m_playerUpdate(&Player::IdleUpdate),
	m_velocity(VGet(0.0f,0.0f,0.0f)),
	m_cameraAngle(0),
	m_Hp(50)
{
	MV1SetPosition(m_modelHandle, VGet(0, 0, 0));
	m_anim_nutral = Loader::GetAnimationIdle();
	m_anim_move = Loader::GetAnimationRun();
	m_anim_hit = Loader::GetAnimationHit();
	m_attach_move = MV1AttachAnim(m_modelHandle, 0, m_anim_move);
	m_attach_hit = MV1AttachAnim(m_modelHandle, 0, m_anim_hit);
}

Player::~Player()
{
	//�����Ȃ�
}

void Player::Init()
{
	//�����Ȃ�
}

void Player::Update()
{

	(this->*m_playerUpdate)();

}

void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
	DrawSphere3D(m_pos,m_radius, 10, 0x000000, 0x00ffff, false);
	MakeShadowMap(50, 50);
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
	printfDx("PlayerIsHit");
	m_Hp -= 10;
	ChangeAnim(m_attach_hit);
	m_playerUpdate = &Player::OnDamageUpdate;
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
		ChangeAnim(m_anim_move);
		m_playerUpdate = &Player::WalkingUpdate;
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		ChangeAnim(m_anim_jump);
		m_velocity.y += 50;
		m_playerUpdate = &Player::JumpingUpdate;
	}

	MATRIX scaleMtx = MGetScale(VGet(0.3f, 0.3f, 0.3f));//XYZ���ꂼ��1/5�X�P�[��
	MV1SetMatrix(m_modelHandle, scaleMtx);

	MV1SetPosition(m_modelHandle, m_pos);
	m_playerRotateY = atan2f((float)m_velocity.x,(float)m_velocity.z);
	MV1SetRotationXYZ(m_modelHandle, VGet(0, m_playerRotateY, 0));

	CollisonSetRadius(m_radius);
	CollisionSetPos(m_pos);

	UpdateAnim(m_anim_nutral);
}

void Player::WalkingUpdate()
{
	int m_inputX = 0;
	int m_inputY = 0;
	GetJoypadAnalogInput(&m_inputX, &m_inputY, DX_INPUT_PAD1);

	Vec2 stickInput((float)m_inputX, -(float)m_inputY);
	
	stickInput.Normalize();

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		ChangeAnim(m_anim_jump);
		m_velocity.y += 50;
		m_playerUpdate = &Player::JumpingUpdate;
	}

	//�x�N�g������
	m_velocity.x = stickInput.x;
	m_velocity.z = stickInput.y;//����͂ŉ��Ɉړ�
	
	m_playerRotateY = -atan2f((float)m_velocity.z, (float)m_velocity.x )-DX_PI_F/2;

	float total = MV1GetAttachAnimTotalTime(m_modelHandle,m_attach_move);
	
	UpdateAnim(m_anim_move);

	//���f���̃T�C�Y����S
	MATRIX scaleMtx = MGetScale(VGet(0.2f, 0.2f, 0.2f));//XYZ���ꂼ��1/5�X�P�[��
	//�p�xR
	MATRIX mtx = MGetRotY(-m_cameraAngle - DX_PI_F / 2);//�{���̓J�������s��Ő��䂵�A���̍s���Y����]
	m_velocity = VTransform(m_velocity, mtx);
	//�ړ�T
	MATRIX moveMtx = MGetTranslate(VGet(m_velocity.x,m_velocity.y,m_velocity.z));
	MATRIX modelMtx = MMult(scaleMtx, moveMtx);
	MV1SetMatrix(m_modelHandle, scaleMtx);

	CollisonSetRadius(m_radius);
	CollisionSetPos(m_pos);

	
}

void Player::JumpingUpdate()
{
	m_velocity.y -= 5;
	MV1SetPosition(m_modelHandle, m_pos);
	if (m_pos.y < 0)
	{
		ChangeAnim(m_anim_nutral);
		m_pos.y = 0;
		m_playerUpdate = &Player::IdleUpdate;
	}

	CollisionSetPos(m_pos);
	UpdateAnim(m_anim_jump);
}

void Player::OnDamageUpdate()
{
	UpdateAnim(m_attach_hit);
	
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

