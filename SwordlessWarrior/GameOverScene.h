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






    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = std::function< void() >(GameOverScene::*)();
    using DrawFunc_t = std::function< void() >(GameOverScene::*)();
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

