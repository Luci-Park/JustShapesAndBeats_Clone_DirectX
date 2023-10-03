#include "LApplication.h"
#include "LInput.h"
#include "LTime.h"
#include "LRenderer.h"
#include "LSceneManager.h"
#include "LResources.h"
#include "LCollisionManager.h"
#include "LFmod.h"
#include "LFontWrapper.h"
namespace lu
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		Destroy();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();
		Fmod::Initialize();
		FontWrapper::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		Fmod::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();

		Time::Render();
		
		renderer::Render();
		SceneManager::Render();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Release()
	{
		renderer::Release();
		SceneManager::Release();		
		Fmod::Release();
		FontWrapper::Release();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<lu::graphics::GraphicDevice_Dx11>();
			lu::graphics::GetDevice() = graphicDevice.get();
		}
		float startY = 900;
		//float startY = 0;
		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, startY, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}
