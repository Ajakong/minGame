#include <DxLib.h>
#include <cassert>
#include"Camera.h"
#include"SkyDome.h"
#include"Shadow.h"
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include"GamePlayingScene.h"
#include"Game.h"
#include"Pad.h"
#include"Quaternion.h"

#include"Loader.h"

namespace
{
	constexpr int kFadeFrameMax = 60;
	constexpr int kStandByFrame = 120;

	constexpr int kLightningFrameMax = 200;
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager),
	m_titleHandle(Loader::GetTextureTitle()),
	m_model_sit(Loader::GetAnimationSitting()),
	m_stageBgm(Loader::GetBGM_title()),
	m_camera(std::make_shared<Camera>()),
	m_skyDome(std::make_shared<SkyDome>()),
	m_shadow(std::make_shared<Shadow>()),
	m_frame(60)
{
	SetCameraPositionAndTargetAndUpVec(VGet(0, 0, -500), VGet(0, 0, 0), VGet(0, 1, 0));
	PlaySoundMem(m_stageBgm, DX_PLAYTYPE_LOOP);
	m_updateFunc = &TitleScene::FadeInUpdate;
	m_drawFunc = &TitleScene::FadeDraw;
	
	m_attach_move = MV1AttachAnim(m_modelHandle, 0, m_model_sit);
	m_modelHandle = MV1DuplicateModel(Loader::GetPlayerHandle());
	m_attach_move = MV1AttachAnim(m_modelHandle, 0, m_model_sit);

	SetFogEnable(TRUE);					// フォグを有効にする
	SetFogColor(200, 120, 0);			// フォグの色にする
	SetFogStartEnd(10.0f, 4000.0f);	// フォグの開始距離
	m_shadow->SetLight();
	pos = Vec3(0, 1, 0);
	angle = 0;
}

TitleScene::~TitleScene()
{
	MV1DeleteModel(m_modelHandle);
	Loader::TitleDelete();
}

void TitleScene::Update()
{

	(this->*m_updateFunc)();

	Pad::Update();

}

void TitleScene::Draw()
{

	(this->*m_drawFunc)();

	if (m_isGamePlaying)
	{
		ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}

}

void TitleScene::FadeInUpdate()
{

	m_fps = GetFPS();

	m_shadow->Draw();
	m_shadow->DrawEnd();
	

	if (!CheckHandleASyncLoad(m_modelHandle))
	{
		m_frame--;
	}
	
	//アニメーション
	if (!m_back)
	{
		m_playAnimTime += 0.7f;

	}
	else
	{
		m_playAnimTime -= 0.7f;
	}
	if (m_playAnimTime > 326)m_playAnimTime = 0;

	m_skyDome->Update();

	MV1SetPosition(m_modelHandle, VGet(0, 0, 0));

	MV1SetAttachAnimTime(m_modelHandle, m_attach_move, m_playAnimTime);

	if (m_frame <= 0)
	{
		m_updateFunc = &TitleScene::NormalUpdate;
		m_drawFunc = &TitleScene::NormalDraw;
	}

}

void TitleScene::NormalUpdate()
{
	m_fps = GetFPS();

	//アニメーション
	if (!m_back)
	{
		m_playAnimTime += 0.7f;

	}
	else
	{
		m_playAnimTime -= 0.7f;
	}
	if (m_playAnimTime > 326)m_playAnimTime = 0;
	
	m_skyDome->Update();

	MV1SetAttachAnimTime(m_modelHandle, m_attach_move, m_playAnimTime);

	Vec3 zero = { 0,0,0 };

	Vec3 offSetVec = GetCameraRightVector();
	offSetVec -= GetCameraUpVector();
	offSetVec *= 9;
	Quaternion myQ;
	angle += 0.05f;

	Vec3 front = GetCameraFrontVector();
	myQ.RotationQuaternion(angle, Vec3(0, 0, 1));
	MATRIX mat = myQ.ToMat();
	/*MATRIX mat = MMult(mat, MGetScale(VGet(2, 2, 2)));
	*/mat = MMult(mat, MGetTranslate(VGet(0, angle, 0)));
	MV1SetMatrix(m_modelHandle, mat);

	if (Pad::IsTrigger(PAD_INPUT_1))
	{

		Loader::GameSceneLoad();

		m_updateFunc = &TitleScene::FadeOutUpdate;
		m_drawFunc = &TitleScene::FadeDraw;
	}

}

void TitleScene::FadeOutUpdate()
{

	m_fps = GetFPS();

	//アニメーション
	if (!m_back)
	{
		m_playAnimTime += 0.7f;

	}
	else
	{
		m_playAnimTime -= 0.7f;
	}
	if (m_playAnimTime > 326)m_playAnimTime = 0;

	m_skyDome->Update();

	MV1SetPosition(m_modelHandle, VGet(800, 400, -650));

	MV1SetAttachAnimTime(m_modelHandle, m_attach_move, m_playAnimTime);



	m_frame++;
	if (m_frame >= 60) {
		m_isGamePlaying = true;
	}

}

void TitleScene::ChangeScene(std::shared_ptr<Scene> next)
{
	StopSoundMem(m_stageBgm);
	m_manager.ChangeScene(next);

}

void TitleScene::FadeDraw()
{
	DrawFormatString(0, 0, 0xffffff, "TitleScene");

	m_skyDome->Draw();

	MV1DrawModel(m_modelHandle);

	DrawRotaGraph(1200, 200, 1, 0, m_titleHandle, true);

	//DrawString(10, 100, "TitleScene", 0xffffff);
	DrawFormatString(730, 650, 0xffffff, "Push Z to Start");

	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / kFadeFrameMax));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	m_shadow->UseShadowMap();
	

	DrawFormatString(0, 0, 0xffffff, "TitleScene");

	m_skyDome->Draw();

	MV1DrawModel(m_modelHandle);

	DrawRotaGraph(1200, 200, 1, 0, m_titleHandle, true);

	//DrawString(10, 100, "TitleScene", 0xffffff);
	DrawFormatString(730, 650, 0xffffff, "Push Z to Start");

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	m_shadow->Fin();
}

void TitleScene::NormalDraw()
{
	DrawFormatString(0, 0, 0xffffff, "TitleScene");

	m_skyDome->Draw();

	MV1DrawModel(m_modelHandle);

	DrawRotaGraph(1200, 200, 1, 0, m_titleHandle, true);

	//DrawString(10, 100, "TitleScene", 0xffffff);
	DrawFormatString(730, 650, 0xffffff, "Push Z to Start");

	m_shadow->UseShadowMap();


	DrawFormatString(0, 0, 0xffffff, "TitleScene");

	m_skyDome->Draw();

	MV1DrawModel(m_modelHandle);
	
	DrawRotaGraph(1200, 200, 1, 0, m_titleHandle, true);

	//DrawString(10, 100, "TitleScene", 0xffffff);
	DrawFormatString(730, 650, 0xffffff, "Push Z to Start");

	m_shadow->Fin();
}
