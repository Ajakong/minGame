#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	// 末尾のみ実行
	m_scenes.back()->Update();
}

void SceneManager::Draw()
{
	// 先頭から順に描画(最後に積んだものが最後に描画される)
	for (auto& scene : m_scenes)
	{
		scene->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (m_scenes.empty()) {	// リストが空っぽだったら入れ替えるのではなく
		m_scenes.push_back(nextScene);	// 末尾に追加する
	}
	else {
		m_scenes.back() = nextScene;	// 素手に一つ以上あったら末尾のものを入れ替える
	}
}

void SceneManager::InsertScene(std::shared_ptr<Scene> nextScene)
{
	int b = 0;
	m_scenes.insert(m_scenes.begin(), nextScene);
}



void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	m_scenes.push_back(scene);
}

void SceneManager::PopScene()
{
	m_scenes.pop_back();
}

std::shared_ptr<Scene> SceneManager::LookBack()
{
	return m_scenes.back();
}
