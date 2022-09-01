#include "engine.h"
#include "myGame.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	// the actual code
	tech::InitializeMemory();
	tech::SetFilePath("../Build/Assets");

	// initialize engine
	tech::g_renderer.Initialize();
	tech::g_inputSystem.Initialize();
	tech::g_audioSystem.Initialize();
	tech::g_resourceManager.Initialize();
	tech::g_physicsSystem.Initialize();

	tech::Engine::Instance().Register();

	// create window
	tech::g_renderer.CreateWindow("Gaming", 1200, 800);
	tech::g_renderer.setClearColor(tech::Color{ 0, 0, 0, 255 });

	std::unique_ptr<myGame> game = std::make_unique<myGame>();
	game->Initialize();

	{
		bool quit = false;
		while (!quit)
		{
			// update
			tech::g_time.Tick();
			tech::g_inputSystem.Update();
			tech::g_audioSystem.Update();
			tech::g_physicsSystem.Update();

			if (tech::g_inputSystem.GetKeyDown(tech::key_escape)) quit = true;

			game->Update();

			//render
			tech::g_renderer.BeginFrame();
			
			game->Draw(tech::g_renderer);

			tech::g_renderer.EndFrame();
		}
	}
	game->Shutdown();
	game.reset(); // essentially the same as calling delete on a normal pointer

	tech::Factory::Instance().Shutdown();
	// technically these should also be singletons but i am to lazy to fix it
	tech::g_inputSystem.Shutdown();
	tech::g_renderer.Shutodwn();
	tech::g_audioSystem.Shutdown();
	tech::g_resourceManager.Shutodwn();
	tech::g_physicsSystem.Shutdown();
}