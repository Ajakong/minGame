#include "Player.h"
#include"Physic.h"
#include<list>
#include <functional>


Player::Player()
{
	std::function<void()> hitFunc=Hit;
	Physic::Entry(m_SphereCol,hitFunc ,NameTag::Player);
}

Player::~Player()
{
	Physic::Exit(NameTag::Player);
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

