#include "Loader.h"
#include<cassert>

namespace
{
	//3Dmodelハンドル
	int playerHandle = -1;
	int enemyHandle = -1;
	int stageHandle = -1;

	int skydomeHandle = -1;

	//3Danimationハンドル
	int anim_idle = -1;
	int anim_sitting = -1;
	int anim_jump = -1;
	int anim_run = -1;
	int anim_hit = -1;
	int anim_falling = -1;

	//Soundハンドル
	int BGM_Title = -1;
	int BGM_Battle = -1;
	int BGM_Ending = -1;

	//2Dtextureハンドル
	int titleHandle = -1;
	int gameOverHandle = -1;
}

namespace Loader
{
	int GetPlayerHandle()
	{
		return playerHandle;
	}
	int GetEnemyHandle()
	{
		return enemyHandle;
	}
	int GetStageHandle()
	{
		return stageHandle;
	}
	int GetSkyDomeHandle()
	{
		return skydomeHandle;
	}
	int GetAnimationIdle()
	{
		return anim_idle;
	}
	int GetAnimationSitting()
	{
		return anim_sitting;
	}
	int GetAnimationJump()
	{
		return anim_jump;
	}
	int GetAnimationRun()
	{
		return anim_run;
	}
	int GetAnimationHit()
	{
		return anim_hit;
	}
	int GetAnimationFalling()
	{
		return anim_falling;
	}
	int GetBGM_title()
	{
		return BGM_Title;
	}
	int GetBGM_battle()
	{
		return BGM_Battle;
	}
	int GetBGM_ending()
	{
		return BGM_Ending;
	}
	int GetTextureTitle()
	{
		return titleHandle;
	}
	int GetTextureGameOver()
	{
		return gameOverHandle;
	}
	void TitleLoad()
	{
		//3Danimationハンドル
		anim_sitting = MV1LoadModel("Player/Sitting.mv1");

		//Soundハンドル
		BGM_Title = LoadSoundMem("BGM/title.mp3");

		//2Dtextureハンドル
		titleHandle = LoadGraph("Title/title.png");
	}
	void TitleDelete()
	{
		//3Danimationハンドル
		MV1DeleteModel(anim_sitting);

		//Soundハンドル
		DeleteSoundMem(BGM_Title);

		//2Dtextureハンドル
		DeleteGraph(titleHandle);
	}
	void GameSceneLoad()
	{
		//3Dmodelハンドル
		enemyHandle = MV1LoadModel("enemy/idle.mv1");
		stageHandle = MV1LoadModel("obj/Stage.mv1");

		//3Danimationハンドル
		anim_run = MV1LoadModel("Player/Run.mv1");
		anim_hit = MV1LoadModel("Player/Hit.mv1");
		anim_idle= MV1LoadModel("Player/Idle.mv1");
		anim_falling = MV1LoadModel("Enemy/Falling.mv1");
		anim_jump = MV1LoadModel("Enemy/Jump.mv1");

		//Soundハンドル
		BGM_Battle = LoadSoundMem("BGM/battle.mp3");
		BGM_Ending = LoadSoundMem("BGM/ending.mp3");
	}
	void GameSceneDelete()
	{
		//3Dmodelハンドル
		MV1DeleteModel(enemyHandle);
		MV1DeleteModel(stageHandle);

		//3Danimationハンドル
		MV1DeleteModel(anim_run);
		MV1DeleteModel(anim_hit);
		MV1DeleteModel(anim_idle);
		MV1DeleteModel(anim_falling);
		MV1DeleteModel(anim_jump);

		//Soundハンドル
		DeleteSoundMem(BGM_Battle);
		DeleteSoundMem(BGM_Ending);
	}

	void GameOverSceneLoad()
	{
		gameOverHandle = LoadGraph("GameOver.png");
	}

	void GameOverSceneDelete()
	{
		DeleteGraph(gameOverHandle);
	}
	
	void Loader::Load()
	{
		//3Dmodelハンドル
		playerHandle = MV1LoadModel("Player/knight.mv1");
		
		skydomeHandle = MV1LoadModel("skydome/Dome.mv1");
	}

	void Delete()
	{
		//3Dmodelハンドル
		MV1DeleteModel(playerHandle);
		
		//3Danimationハンドル
		MV1DeleteModel(anim_sitting);
	}

}
