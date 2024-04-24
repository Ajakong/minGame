#include "Player.h"
#include"Physic.h"
#include<list>
#include <functional>


Player::Player()
{
	Physic::Entry(m_SphereCol, Hit(),NameTag::Player);
}

Player::~Player()
{
	Physic::Exit()
}

void Player::Update()
{
}

void Player::Draw()
{
}

std::function<void(void)> Player::Hit()
{
	return std::function<void(void)>();
}

