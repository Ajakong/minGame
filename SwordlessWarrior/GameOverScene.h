#pragma once
#include "Scene.h"

class GamePlayingScene;

class GameOverScene : public Scene
{
public:
    GameOverScene(SceneManager& mgr);

    ~GameOverScene();
    virtual std::function<void() > Update();
    virtual std::function<void() > Draw();

private:

    int m_btnFrame = 0;
    int m_frame;
    int m_fadeSoundFrame = 0;

    int m_selectNumber = 0;






    // メンバ関数ポインタの宣言
    using UpdateFunc_t = std::function< void() >(GameOverScene::*)();
    using DrawFunc_t = std::function< void() >(GameOverScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // 更新状態を表す関数
    std::function<void() > FadeInUpdate();
    std::function<void() > NormalUpdate();
    std::function<void() > FadeOutUpdate();

    // 描画状態を表す関数
    std::function<void() > FadeDraw();
    std::function<void() > NormalDraw();
};

