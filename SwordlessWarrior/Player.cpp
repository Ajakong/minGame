#include "Player.h"
#include"Physic.h"
#include<list>
#include <functional>


Player::Player()
{
	Physic::Entry(m_SphereCol, Hit);
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
}

