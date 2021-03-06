#include "WINEngineEntryPoint.h"
#include "BF/Application/SceneManager.h"
#include "BF/System/Log.h"

namespace BF
{
	namespace Platform
	{
		namespace Windows
		{
			using namespace BF::Graphics::API;
			using namespace BF::Application;

			WINEngineEntryPoint::WINEngineEntryPoint(const WINWindow& winWindow, Graphics::API::RenderAPI renderAPI) :
				winWindow(winWindow), context(renderAPI), frameRateTarget(0.0f), frameTimeTarget(0.0f)
			{
				LimitFrameRate(60.0f);
			}

			WINEngineEntryPoint::~WINEngineEntryPoint()
			{
			}

			void WINEngineEntryPoint::Run(Scene& mainScene)
			{
				BF_LOG_INFO("Engine Run");
				while (state != State::Exit)
				{
					switch (state)
					{
						case State::Initialize:
						{
							winWindow.Initialize();
							context.Initialize();
							SceneManager::AddNewScene(&mainScene);
							SceneManager::GetScene(0).Run();
							state = State::Render;
							break;
						}

						case State::Render:
						{
							for (int i = 0; i < SceneManager::GetScenes().size(); i++)
							{
								if (SceneManager::GetScene(i).IsRunning())
								{
									if (!SceneManager::GetScene(i).initialized)
									{
										SceneManager::GetScene(i).Initialize();
										SceneManager::GetScene(i).initialized = true;
									}

									if (!SceneManager::GetScene(i).loaded)
									{
										SceneManager::GetScene(i).Load();
										SceneManager::GetScene(i).loaded = true;
									}

									winWindow.Update();

									if (frameTimeTarget != 0.0f)
									{
										if (SceneManager::GetScene(i).frameTimer.GetElapsedTimeInMilliseconds() >= frameTimeTarget)
										{
											deltaTime = SceneManager::GetScene(i).frameTimer.GetElapsedTimeInMilliseconds();
											SceneManager::GetScene(i).frameTimer.Reset();
											SceneManager::GetScene(i).Update();
											SceneManager::GetScene(i).Render();
											FPS++;
										}
									}
									else
									{
										deltaTime = SceneManager::GetScene(i).frameTimer.GetElapsedTimeInMilliseconds();
										SceneManager::GetScene(i).frameTimer.Reset();
										SceneManager::GetScene(i).Update();
										SceneManager::GetScene(i).Render();
										FPS++;
									}

									if (SceneManager::GetScene(i).frameRateTimer.GetElapsedTimeInMilliseconds() >= 1000.0f)
									{
										BF_LOG_INFO("Frames: %d, LastFrameTime: %f", FPS, deltaTime);
										SceneManager::GetScene(i).frameRateTimer.Reset();
										FPS = 0;
									}
								}
							}
							break;
						}

						default:
							break;
					}
				}
			}

			void WINEngineEntryPoint::LimitFrameRate(double limit)
			{
				if (limit != 0.0f)
				{
					frameRateTarget = limit;
					frameTimeTarget = 1000.0f / frameRateTarget;
				}
				else
					frameTimeTarget = 0.0f;
			}
		}
	}
}