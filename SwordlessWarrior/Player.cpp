#include "Player.h"
#include"Physic.h"
#include<list>
#include <functional>
#include"NameTag.h"


Player::Player(int& modelhandle) :Object(modelhandle)
{
	
	
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
	
}

void Player::Draw()
{
	
}

void Player::Hit()
{
	
}

void Player::IdleUpdate()
{
}

void Player::WalkingUpdate()
{
	int m_inputX = 0;
	int m_inputY = 0;
	GetJoypadAnalogInput(&m_inputX, &m_inputY, DX_INPUT_PAD1);
	if (m_velocity.x != 0)
	{
		m_velocity.x = m_inputX;

	}

	m_velocity.z = m_inputY;
	
	

}

