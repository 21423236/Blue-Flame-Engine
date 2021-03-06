#include <BF/BlueFlame.h>
//#include <BF/Engine.h>
//#include <BF/Application/Window.h>
//#include <BF/Application/SceneManager.h>
//#include <BF/Platform/API/Vulkan/VKContext.h>

#include "_2DScene.h"
//#include "_3DScene.h"
//#include "_3DScene2.h"
//#include "InputTests.h"

//#include <windows.h>
//#include <string>
//#include <iostream>

//using namespace std;

//#include <BF/Network/Server.h>
//#include <BF/Network/Client.h>

int main()
{
	/*BF::Network::Server server;

	server.Initialize();
	server.Listen();
	server.Accept();*/

	
	/*BF::Network::Client client;

	client.Initialize();
	client.Connect();

	system("PAUSE");*/

	//BF::Platform::API::Vulkan::VKContext vKContext;

	//BF_LOG_INFO("MAIN FUNCTION");

	BF::Engine engine(BF::Application::Window("Blue Flame Engine", BF::Math::Rectangle(800, 250, 800, 600), BF::Application::WindowStyle::ResizableWindow), BF::Graphics::API::RenderAPI::OpenGL);

	//BF::Application::SceneManager::AddNewScene(new AndroidTestScene());
	//BF::Application::SceneManager::AddNewScene(new test());
	//BF::Application::SceneManager::AddNewScene(new _2DScene::_2DScene());
	//BF::Application::SceneManager::AddNewScene(new _3DScene::_3DScene());
	//BF::Application::SceneManager::AddNewScene(new InputTests());
	
	//BF::Application::SceneManager::AddNewScene(new _3DScene2::_3DScene2());
	_2DScene::_2DScene _2d;

	engine.Run(_2d);
	//engine.Run(_3DScene::_3DScene());

	/*
		TCHAR  buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);

		for (size_t i = 0; i < MAX_PATH; i++)
		{
			cout << (char)buffer[i];
		}
		*/
		/*
			BF::Audio::SoundManager soundManager;
			BF::Audio::Sound sound;

			sound.Load("Assets/Audio/16test.wav");
			sound.Play(true);


	system("PAUSE");
	*/
	return 0;
}