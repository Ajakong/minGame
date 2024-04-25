#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

class SceneMain;

class TitleScene : public Scene
{
public:
    TitleScene(SceneManager& manager);
    ~TitleScene();
    virtual std::function<void() > Update();
    virtual std::function<void() > Draw();

    std::function<void() > getSlectNumber(int a) { m_selectNum = a; }

private:

    int m_titleHandle = 0;
    int m_modelHandle[10] = { 0 };
    int m_model_dance = 0;
    int m_attach_move[10] = { 0 };

    int m_btnFrame = 0;
    int m_frame = 0;

    bool m_back = false;


    int m_stageBgm = 0;

    int m_backBlack = 0;


    float m_fps = 0.0f;

    int m_selectNum = 0;
    bool m_soundFlag = false;

    bool m_isGamePlaying = false;


    float m_playAnimTime = 0.0f;
    float m_animTime_move = 0.0f;

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = std::function< void() >(TitleScene::*)();
    using DrawFunc_t = std::function< void() >(TitleScene::*)();
    UpdateFunc_t m_updateFunc = nullptr;
    DrawFunc_t m_drawFunc = nullptr;



    // �X�V�֐�
    std::function<void() >FadeInUpdate();
    std::function<void() > NormalUpdate();
    std::function<void() > FadeOutUpdate();

    std::function<void() > ChangeScene(std::shared_ptr<Scene> next);


    // �`��֐�
    std::function<void() > FadeDraw();
    std::function<void() > NormalDraw();

};



