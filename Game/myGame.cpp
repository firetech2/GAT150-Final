#include "myGame.h"
#include "engine.h"

void myGame::Initialize()
{
	m_scene = std::make_unique<tech::Scene>();

	// load from json file to scene
	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scenes/prefabs.txt", "Scenes/tilemap.txt", "Scenes/level.txt" };

	for (auto sceneName : sceneNames)
	{
		bool sucess = tech::json::Load(sceneName, document);
		if (!sucess) { LOG("Error loading scene %s", sceneName.c_str()); continue; }

		m_scene->Read(document);
	}


	m_scene->Initialize();

	m_scene->Update();
	
}

void myGame::Shutdown()
{
	m_scene->RemoveAll();
}

void myGame::Update()
{
	m_scene->Update();

	spawntimer -= tech::g_time.deltaTime;
	if (spawntimer <= 0)
	{
		spawntimer = 5;
		int enemyrandomizer = tech::random(1, 10);
		for (int i = 0; i < enemyrandomizer; i++)
		{
			auto actor = tech::Factory::Instance().Create<tech::Actor>("enemy");
			actor->GetTransform().position = { tech::randomf(200, 1100), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
	}

}

void myGame::Draw(tech::Renderer& renderer)
{
	m_scene->Draw(tech::g_renderer);
}

