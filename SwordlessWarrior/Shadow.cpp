#include "Shadow.h"

Shadow::Shadow():
	m_shadowMapHandle(MakeShadowMap(1024, 1024))
{
	SetShadowMapDrawArea(m_shadowMapHandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));

}

Shadow::~Shadow()
{
}

void Shadow::SetLight()
{
	// ライトの方向ベクトルの算出
	m_lightDir.x =1;
	m_lightDir.z = 1;
	m_lightDir.y = -1.0f;

	// ライトの方向を設定
	SetLightDirection(m_lightDir);

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(m_shadowMapHandle, m_lightDir);
}

void Shadow::Draw()
{
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(m_shadowMapHandle);


}

void Shadow::DrawEnd()
{
	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();


}

void Shadow::UseShadowMap()
{
	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0,m_shadowMapHandle);

}

void Shadow::Fin()
{
	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, -1);
}
