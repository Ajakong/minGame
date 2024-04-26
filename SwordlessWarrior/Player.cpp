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

