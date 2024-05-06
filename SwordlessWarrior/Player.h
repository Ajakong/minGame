#pragma once
#include"Object.h"



class Player : public Object
{
public:
	Player(int& modelhandle);
	~Player();

	void Init();

	void Update();
	void Draw();

	VECTOR GetPos()const { return m_pos; }

	void Hit();

	//�����o�֐��|�C���^
	using playerState_t = void(Player::*)();
	playerState_t m_playerUpdate;

private:
	//��ԕʊ֐�(�|�C���^�ŌĂяo��)
	void StartUpdate();
	void IdleUpdate();
	void WalkingUpdate();
	void NeutralUpdate();
	void FaceDownUpdate();
	void JumpingUpdate();


private:
	VECTOR m_velocity;
};

