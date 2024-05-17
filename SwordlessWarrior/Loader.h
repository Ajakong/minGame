#pragma once
#include"DxLib.h"
namespace Loader
{
	//3Dmodel�n���h��
	int GetPlayerHandle();
	int GetEnemyHandle();
	int GetStageHandle();
	int GetSkyDomeHandle();

	//3Danimation�n���h��
	int GetAnimationIdle();
	int GetAnimationSitting();
	int GetAnimationRun();
	int GetAnimationHit();

	//Sound�n���h��
	int GetBGM_title();
	int GetBGM_battle();
	int GetBGM_ending();

	//2Dtexture�n���h��
	int GetTextureTitle();
	int GetTextureGameOver();

	void TitleLoad();//�^�C�g���Ŏg�p������̂̓ǂݍ���
	void TitleDelete();//�폜
	void GameSceneLoad();//�Q�[���V�[���Ŏg�p������̂̓ǂݍ���
	void GameSceneDelete();//�폜
	void GameOverSceneLoad();//�Q�[���I�[�o�[�V�[���Ŏg�p������̂̓ǂݍ���
	void GameOverSceneDelete();//�폜

	void Load();//�펞�ǂݍ���ł����������m
	void Delete();//�폜
};

