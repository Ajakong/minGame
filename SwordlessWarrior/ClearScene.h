#pragma once
#include "Scene.h"

class ClearScene : public Scene
{
public:
    ClearScene(SceneManager& mgr);
    ~ClearScene();

    virtual std::function<void() > Update();
    virtual std::function<void() > Draw();

private:

    int m_btnFrame = 0;
    int m_frame;

    // メンバ関数ポインタの宣言
    using UpdateFunc_t = std::function<void() >(ClearScene::*)();
    using DrawFunc_t = std::function<void() >(ClearScene::*)();
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

