#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include<iostream>
#include<vector>
#include"Game.h"
#include <DxLib.h>
#include <cassert>

#include"WorldTimer.h"
#include"Loader.h"
#include"Pad.h"

namespace
{
    constexpr int kScreenWidth = 1600;
    constexpr int kScreenHeight = 900;

    constexpr int kColorbitDepth = 32;
    constexpr int kIconID = 573;
}

using namespace std;

int MyLoadGraph(const TCHAR* path)
{
    int handle = LoadGraph(path);
    assert(handle != -1);
    return handle;
}

Application::Application()
{
    m_windowSize = Size{ kScreenWidth, kScreenHeight };
}

void Application::Terminate()
{

    Loader::Delete();

    DxLib_End();
}

int Application::GetScreenHandle()
{
    return m_screenHandle;
}

float Application::GetGravity() const
{
    return 0.5f;
}

bool Application::Init()
{
    ChangeWindowMode(true); // ウィンドウモードにします
    //SetGraphMode(m_windowSize.w, m_windowSize.h, 1);
    SetWindowSizeChangeEnableFlag(TRUE, TRUE);
    SetChangeScreenModeGraphicsSystemResetFlag(false);


    SetGraphMode(kScreenWidth, kScreenHeight, kColorbitDepth);
    SetWindowSize(kScreenWidth, kScreenHeight);

    void* CallBack();


    DxLib_Init();

    SetWindowIconID(kIconID);

    SetUseASyncChangeWindowModeFunction(TRUE, NULL, NULL);

    SetUseZBuffer3D(true);
    SetWriteZBuffer3D(true);
    SetUseBackCulling(true);

    SetWindowText("DieEasy");
    Loader::Load();
    Loader::TitleLoad();
    if (DxLib_Init() == -1)
    {
        return false;
    }


    SetDrawScreen(DX_SCREEN_BACK);
    return true;

   
}

void Application::Run()
{
    {// スコープを強制的に作っている

        SceneManager sceneManager;
        sceneManager.ChangeScene(std::make_shared<TitleScene>(sceneManager));


        m_screenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

        LONGLONG time;

        bool stop = false;
        bool addFrame = false;//コマ送り処理
        int FrameCount = 0;

        

        while (ProcessMessage() != -1)
        {
            // FPSの固定ように開始時の時間を取得
            time = GetNowHiPerformanceCount();

            ClearDrawScreen();
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                ChangeWindowMode(true);
            }



            if (!stop)
            {
                
                FrameCount++;
                sceneManager.Update();
                if (Pad::IsTrigger(PAD_INPUT_8))
                {
                    stop = true;
                }
                if (addFrame)
                {
                    addFrame = false;
                    stop = true;
                }
            }
            else
            {

                if (Pad::IsTrigger(PAD_INPUT_8))
                {
                    stop = false;
                }
                if (Pad::IsTrigger(PAD_INPUT_12))
                {
                    addFrame = true;
                    stop = false;
                }
            }

            sceneManager.Draw();

            ScreenFlip();
           

            // 60FPSに固定
            while (16667 > GetNowHiPerformanceCount() - time) {};
        }
    }
    Terminate();
    std::vector<VECTOR> num;

}



const Size& Application::GetWindowSize() const
{
    return m_windowSize;
}
