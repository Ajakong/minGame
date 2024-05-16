#pragma once
#include"DxLib.h"
class Shadow
{
public:
	Shadow();

	~Shadow();

	void SetLight();

	void Draw();

	void DrawEnd();
	void UseShadowMap();

	void Fin();
private:
	int m_shadowMapHandle;

	VECTOR m_lightDir;
};

