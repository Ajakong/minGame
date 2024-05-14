#pragma once
#include"DxLib.h"
namespace Loader
{
	//3Dmodel�n���h��
	int GetPlayerHandle();
	int GetEnemyHandle();
	int GetStageHandle();

	//3Danimation�n���h��
	int GetAnimationSitting();

	//Sound�n���h��
	int GetBGM_title();
	int GetBGM_battle();
	int GetBGM_ending();

	//2Dtexture�n���h��
	int GetTextureTitle();

	void TitleLoad();//�^�C�g���Ŏg�p������̂̓ǂݍ���
	void TitleDelete();//�폜
	void GameSceneLoad();//�Q�[���V�[���Ŏg�p������̂̓ǂݍ���
	void GameSceneDelete();//�폜
	void GameOverSceneLoad();//�Q�[���I�[�o�[�V�[���Ŏg�p������̂̓ǂݍ���
	void GameOverSceneDelete();//�폜

	void Load();//�펞�ǂݍ���ł����������m
	void Delete();//�폜
};

