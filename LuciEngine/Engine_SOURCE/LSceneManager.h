#pragma once
#include "LScene.h"

namespace lu
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetScene(std::wstring name);
		static Scene* LoadScene(std::wstring name);

		static void AddCamera(Camera* camera);
		static Camera* MainCamera();

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();
			auto it = mScenes.find(name);

			if (it != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();
			return true;
		}

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};
}

