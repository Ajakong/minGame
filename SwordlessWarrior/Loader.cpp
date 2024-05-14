#include "Loader.h"
#include<cassert>

namespace
{
	//3Dmodel�n���h��
	int playerHandle = 0;
	int enemyHandle = 0;
	int stageHandle = 0;

	//3Danimation�n���h��
	int anim_sitting = 0;

	//Sound�n���h��
	int BGM_Title = 0;
	int BGM_Battle = 0;
	int BGM_Ending = 0;

	//2Dtexture�n���h��
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
		//Sound�n���h��
		BGM_Title = LoadSoundMem("BGM/title.mp3");

		//2Dtexture�n���h��
		titleHandle = LoadGraph("Title/Title.png");
	}
	void TitleDelete()
	{
		//Sound�n���h��
		DeleteSoundMem(BGM_Title);

		//2Dtexture�n���h��
		DeleteGraph(titleHandle);
	}
	void GameSceneLoad()
	{
		//3Dmodel�n���h��
		enemyHandle = MV1LoadModel("enemy/idle.mv1");
		stageHandle = MV1LoadModel("obj/Stage.mv1");

		//Sound�n���h��
		BGM_Battle = LoadSoundMem("BGM/battle.mp3");
		BGM_Ending = LoadSoundMem("BGM/ending.mp3");
	}
	void GameSceneDelete()
	{
		//3Dmodel�n���h��
		MV1DeleteModel(enemyHandle);
		MV1DeleteModel(stageHandle);

		//Sound�n���h��
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
		//3Dmodel�n���h��
		playerHandle = MV1LoadModel("model/knight.mv1");
		//3Danimation�n���h��
		anim_sitting = MV1LoadModel("model/Sitting.mv1");
	}

	void Delete()
	{
		//3Dmodel�n���h��
		MV1DeleteModel(playerHandle);
		
		//3Danimation�n���h��
		MV1DeleteModel(anim_sitting);
	}

}
