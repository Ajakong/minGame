#pragma once
#include"DxLib.h"
namespace Loader
{
	int playerHandle=MV1LoadModel("knight.mv1");
	int enemyHandle=0;
	
	int BGM_title = LoadSoundMem("title.mp3");
	int BGM_battle = LoadSoundMem("battle.mp3");
	int BGM_ending = LoadSoundMem("ending.mp3");

}

