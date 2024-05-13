#pragma once
class SkyDome
{
public:
	SkyDome();
	~SkyDome();

	void Update();
	void Draw();
private:
	int m_model = 0;
	float m_rotate = 0;
};

