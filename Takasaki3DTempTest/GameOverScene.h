#pragma once
#include "Scene.h"

class GamePlayingScene;

class GameOverScene : public Scene
{
public:
    GameOverScene(SceneManager& mgr);

    ~GameOverScene();
    virtual void Update();
    virtual void Draw();

private:

    int m_btnFrame = 0;
    int m_frame;
    int m_fadeSoundFrame = 0;

    int m_selectNumber = 0;






    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (GameOverScene::*)();
    using DrawFunc_t = void (GameOverScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // 更新状態を表す関数
    void FadeInUpdate();
    void NormalUpdate();
    void FadeOutUpdate();

    // 描画状態を表す関数
    void FadeDraw();
    void NormalDraw();
};

