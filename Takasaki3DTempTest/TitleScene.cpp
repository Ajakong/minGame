#include <DxLib.h>
#include <cassert>
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
	m_model_dance(MV1LoadModel("Title/dance.mv1")),
	m_stageBgm(LoadSoundMem("Title/Title.mp3"))
{
	PlaySoundMem(m_stageBgm, DX_PLAYTYPE_LOOP);
	m_updateFunc = &TitleScene::FadeInUpdate;
	m_drawFunc = &TitleScene::FadeDraw;
	m_modelHandle[0] = MV1LoadModel("player/Idle.mv1");
	m_attach_move[0] = MV1AttachAnim(m_modelHandle[0], 0, m_model_dance);
	for (int i = 1; i < 10; i++)
	{
		m_modelHandle[i] = MV1DuplicateModel(m_modelHandle[0]);
		m_attach_move[i] = MV1AttachAnim(m_modelHandle[i], 0, m_model_dance);
	}
}

TitleScene::~TitleScene()
{
	for (int i = 0; i < 10; i++)
	{
		MV1DeleteModel(m_modelHandle[i]);
	}
	MV1DeleteModel(m_model_dance);
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

	VECTOR center[10] = { 0 };
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

	for (int i = 0; i < 10; i++)
	{
		center[i] = VGet(330 + i * 100, 300, -260);
		MV1SetPosition(m_modelHandle[i], center[i]);

		MV1SetAttachAnimTime(m_modelHandle[i], m_attach_move[i], m_playAnimTime);
		//
	}

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



	for (int i = 0; i < 10; i++)
	{
		MV1DrawModel(m_modelHandle[i]);
	}
	DrawRotaGraph(800, 450, 1, 0, m_titleHandle, true);

	//DrawString(10, 100, "TitleScene", 0xffffff);
	DrawFormatString(730, 650, 0xffffff, "Push Z to Start");
}
