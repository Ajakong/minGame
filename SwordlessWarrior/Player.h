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

	VECTOR GetPos()const { return m_pos; }
	void WantCameraToPlayer(VECTOR cameraToPlayer);
	
	void Hit();

	void SetCameraAngle(float cameraAngle);

	//�����o�֐��|�C���^
	using playerState_t = void(Player::*)();
	playerState_t m_playerUpdate;

private:
	//��ԕʊ֐�(�|�C���^�ŌĂяo��)
	void StartUpdate();
	void IdleUpdate();
	void WalkingUpdate();
	void JumpingUpdate();

	VECTOR GetCameraToPlayer()const;

private:
	VECTOR m_velocity;
	VECTOR m_cameraToPlayer;


	//�A�j���[�V�����ϐ�
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_jump = 0;
	int m_attach_move = 0;
	int m_attach_jump = 0;
	int m_attach_idle = 0;

	float m_playAnimTime = 0.0f;
	float m_animTime_move = 0.0f;
	

	float m_playerRotateY = 0;

	float m_cameraAngle = 0;

};

