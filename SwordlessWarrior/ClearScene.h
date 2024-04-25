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

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = std::function<void() >(ClearScene::*)();
    using DrawFunc_t = std::function<void() >(ClearScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // �X�V��Ԃ�\���֐�
    std::function<void() > FadeInUpdate();
    std::function<void() > NormalUpdate();
    std::function<void() > FadeOutUpdate();

    // �`���Ԃ�\���֐�
    std::function<void() > FadeDraw();
    std::function<void() > NormalDraw();

};

