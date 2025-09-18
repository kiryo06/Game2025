#pragma once
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
private:
	VECTOR m_pos;
	VECTOR m_dir;
};

