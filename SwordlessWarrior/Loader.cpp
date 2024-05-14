#include "Loader.h"
#include<cassert>

namespace
{
	//3Dmodelハンドル
	int playerHandle = 0;
	int enemyHandle = 0;
	int stageHandle = 0;

	//3Danimationハンドル
	int anim_sitting = 0;

	//Soundハンドル
	int BGM_Title = 0;
	int BGM_Battle = 0;
	int BGM_Ending = 0;

	//2Dtextureハンドル
	int titleHandle = 0;
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
	int GetAnimationSitting()
	{
		return anim_sitting;
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
	void TitleLoad()
	{
		//Soundハンドル
		BGM_Title = LoadSoundMem("BGM/title.mp3");

		//2Dtextureハンドル
		titleHandle = LoadGraph("Title/Title.png");
	}
	void TitleDelete()
	{
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

		//Soundハンドル
		BGM_Battle = LoadSoundMem("BGM/battle.mp3");
		BGM_Ending = LoadSoundMem("BGM/ending.mp3");
	}
	void GameSceneDelete()
	{
		//3Dmodelハンドル
		MV1DeleteModel(enemyHandle);
		MV1DeleteModel(stageHandle);

		//Soundハンドル
		DeleteSoundMem(BGM_Battle);
		DeleteSoundMem(BGM_Ending);
	}

	void GameOverSceneLoad()
	{
	}

	void GameOverSceneDelete()
	{
	}
	
	void Loader::Load()
	{
		//3Dmodelハンドル
		playerHandle = MV1LoadModel("model/knight.mv1");
		//3Danimationハンドル
		anim_sitting = MV1LoadModel("model/Sitting.mv1");
	}

	void Delete()
	{
		//3Dmodelハンドル
		MV1DeleteModel(playerHandle);
		
		//3Danimationハンドル
		MV1DeleteModel(anim_sitting);
	}

}
