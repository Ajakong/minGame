#pragma once
#include"Object.h"



class Player : public Object
{
public:
	Player(int modelhandle);
	~Player();

	void Init();

	void Update();
	void Draw();

	
	void WantCameraToPlayer(VECTOR cameraToPlayer);
	
	void Hit();
	int WatchHp()const { return m_Hp; }

	void SetCameraAngle(float cameraAngle);

	int GetPlayerModelhandle() { return m_modelHandle; }

	//�����o�֐��|�C���^
	using playerState_t = void(Player::*)();
	playerState_t m_playerUpdate;

private:
	//�A�j���[�V�����̐i�s
   //���[�v�������ǂ�����Ԃ�
	bool UpdateAnim(int attachNo);
	//�A�j���[�V�����̕ύX
	void ChangeAnim(int animIndex);

	//��ԕʊ֐�(�|�C���^�ŌĂяo��)
	void StartUpdate();
	void IdleUpdate();
	void WalkingUpdate();
	void JumpingUpdate();
	void OnDamageUpdate();

	VECTOR GetCameraToPlayer()const;

private:
	int m_Hp;
	int m_modelHandle = 0;
	float m_radius = 0;

	VECTOR m_velocity;
	VECTOR m_cameraToPlayer;

	int m_currentAnimNo;//���݂̃A�j���[�V����
	int m_prevAnimNo;//�ύX�O�̃A�j���[�V����
	float m_animBlendRate;//�A�j���[�V�����̍�������
	//0.0f:prev���Đ�
	//1.0:current���Đ�

	//�A�j���[�V�����ϐ�
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_hit = 0;
	int m_anim_jump = 0;
	int m_attach_move = 0;
	int m_attach_hit = 0;
	int m_attach_jump = 0;
	int m_attach_idle = 0;

	float m_playAnimTime = 0.0f;
	float m_animTime_move = 0.0f;
	
	float m_playerRotateY = 0;
	float m_cameraAngle = 0;

};

