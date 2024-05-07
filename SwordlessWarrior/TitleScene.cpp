#include <DxLib.h>
#include <cassert>
#include"Camera.h"
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include"GamePlayingScene.h"
#include"Game.h"
#include"Pad.h"

namespace
{
	constexpr int kFadeFrameMax = 60;
	constexpr int kStandByFrame = 120;

	constexpr int kLightningFrameMax = 200;
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager),
	m_titleHandle(LoadGraph("Title/Title.png")),
	m_modelHandle(MV1LoadModel("model/knight.mv1")),
	m_model_sit(MV1LoadModel("model/Sitting.mv1")),
	m_stageBgm(LoadSoundMem("BGM/title.mp3")),
	m_camera(std::make_shared<Camera>())
{
	PlaySoundMem(m_stageBgm, DX_PLAYTYPE_LOOP);
	m_updateFunc = &TitleScene::FadeInUpdate;
	m_drawFunc = &TitleScene::FadeDraw;
	
	m_attach_move = MV1AttachAnim(m_modelHandle, 0, m_model_sit);
	m_modelHandle = MV1DuplicateModel(m_modelHandle);
	m_attach_move = MV1AttachAnim(m_modelHandle, 0, m_model_sit);
}

TitleScene::~TitleScene()
{
	MV1DeleteModel(m_modelHandle);
	MV1DeleteModel(m_model_sit);
	DeleteSoundMem(m_stageBgm);
	DeleteGraph(m_titleHandle);
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

	m_frame--;
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
	if (m_playAnimTime > 565)m_back = true;
	if (m_playAnimTime < 0)m_back = false;

	MV1SetPosition(m_modelHandle, VGet(800,400,-650));

	MV1SetAttachAnimTime(m_modelHandle, m_attach_move, m_playAnimTime);
		
	

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_updateFunc = &TitleScene::FadeOutUpdate;
		m_drawFunc = &TitleScene::FadeDraw;
	}

	m_btnFrame++;

}

void TitleScene::FadeOutUpdate()
{

	m_fps = GetFPS();
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
	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / kFadeFrameMax));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawFormatString(0, 0, 0xffffff, "TitleScene");



	MV1DrawModel(m_modelHandle);
	
	DrawRotaGraph(800, 450, 1, 0, m_titleHandle, true);

	//DrawString(10, 100, "TitleScene", 0xffffff);
	DrawFormatString(730, 650, 0xffffff, "Push Z to Start");
}
