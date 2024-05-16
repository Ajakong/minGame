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
	// ���C�g�̕����x�N�g���̎Z�o
	m_lightDir.x =1;
	m_lightDir.z = 1;
	m_lightDir.y = -1.0f;

	// ���C�g�̕�����ݒ�
	SetLightDirection(m_lightDir);

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(m_shadowMapHandle, m_lightDir);
}

void Shadow::Draw()
{
	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(m_shadowMapHandle);


}

void Shadow::DrawEnd()
{
	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();


}

void Shadow::UseShadowMap()
{
	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0,m_shadowMapHandle);

}

void Shadow::Fin()
{
	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(0, -1);
}
