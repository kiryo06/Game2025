#include "Player.h"
#include "Pad.h"

namespace
{
	
}

Player::Player() :
	m_pos(0.0f, 20.2f,0.0f),
	m_vec(0.0f,0.0f,0.0f)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	
}

void Player::Draw()
{
	DrawFormatString(10, 30, 0xffffff, "%.1f", m_pos.y);
}
