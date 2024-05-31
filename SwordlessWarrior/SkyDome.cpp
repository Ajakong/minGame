#include"Dxlib.h"
#include "SkyDome.h"

#include"Loader.h"

SkyDome::SkyDome():
	m_model(MV1DuplicateModel(Loader::GetSkyDomeHandle()))
{
	MV1SetPosition(m_model, VGet(0, 0, 0));
	MATRIX scaleMtx = MGetScale(VGet(30.0f, 30.0f, 5.0f));//XYZÇªÇÍÇºÇÍ1/5ÉXÉPÅ[Éã
	MV1SetMatrix(m_model, scaleMtx);

}

SkyDome::~SkyDome()
{
	MV1DeleteModel(m_model);
}

void SkyDome::Update()
{
	m_rotate+=0.5f;
	MV1SetRotationXYZ(m_model, VGet(0, m_rotate*100, 0));
}

void SkyDome::Draw()
{
	MV1DrawModel(m_model);
}
