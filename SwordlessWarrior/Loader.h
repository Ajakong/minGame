#pragma once
#include"DxLib.h"
namespace Loader
{
	//3Dmodelハンドル
	int GetPlayerHandle();
	int GetEnemyHandle();
	int GetStageHandle();
	int GetSkyDomeHandle();

	//3Danimationハンドル
	int GetAnimationIdle();
	int GetAnimationSitting();
	int GetAnimationRun();
	int GetAnimationHit();

	//Soundハンドル
	int GetBGM_title();
	int GetBGM_battle();
	int GetBGM_ending();

	//2Dtextureハンドル
	int GetTextureTitle();
	int GetTextureGameOver();

	void TitleLoad();//タイトルで使用するものの読み込み
	void TitleDelete();//削除
	void GameSceneLoad();//ゲームシーンで使用するものの読み込み
	void GameSceneDelete();//削除
	void GameOverSceneLoad();//ゲームオーバーシーンで使用するものの読み込み
	void GameOverSceneDelete();//削除

	void Load();//常時読み込んでおきたいモノ
	void Delete();//削除
};

