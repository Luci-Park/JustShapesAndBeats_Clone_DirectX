#pragma once

#include "LLayer.h"
#include "LGameObject.h"
#include "LScene.h"
#include "LSceneManager.h"
#include "LTransform.h"


namespace lu::object
{
	template <typename T>
	static __forceinline T* Instantiate(lu::enums::eLayerType layer)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);
		
		gameObj->Initialize();
		
		return gameObj;
	}

	
	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		tr->SetPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		gameObj->Initialize();

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Quaternion rotate, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		tr->SetPosition(pos);
		tr->SetRotation(rotate);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		gameObj->Initialize();

		return gameObj;
	}
	
	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Quaternion rotate, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		tr->SetPosition(pos);
		tr->SetRotation(rotate);
		tr->SetScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		gameObj->Initialize();

		return gameObj;
	}
	template <typename T>
	static __forceinline T* Instantiate(Transform* parent, lu::enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);
		tr->SetParent(parent);

		gameObj->Initialize();

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Transform* parent, enums::eLayerType layer, bool InstantiateInWorldSpace = false)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		tr->SetPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);
		tr->SetParent(parent);
		if (InstantiateInWorldSpace)
			tr->SetPosition(pos);
		else
			tr->SetLocalPosition(pos);

		gameObj->Initialize();

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Quaternion rotate, Transform* parent, enums::eLayerType layer, bool InstantiateInWorldSpace = false)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		tr->SetPosition(pos);
		tr->SetRotation(rotate);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		tr->SetParent(parent);
		if (InstantiateInWorldSpace)
		{
			tr->SetPosition(pos);
			tr->SetRotation(rotate);
		}
		else
		{
			tr->SetLocalPosition(pos);
			tr->SetLocalRotation(rotate);
		}

		gameObj->Initialize();

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Quaternion rotate, Vector3 scale, Transform* parent, enums::eLayerType layer, bool InstantiateInWorldSpace = false)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->mTransform;
		tr->SetParent(parent);
		tr->SetPosition(pos);
		tr->SetRotation(rotate);
		tr->SetScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		tr->SetParent(parent);
		if (InstantiateInWorldSpace)
		{
			tr->SetPosition(pos);
			tr->SetRotation(rotate);
			tr->SetScale(scale);
		}
		else
		{
			tr->SetLocalPosition(pos);
			tr->SetLocalRotation(rotate);
			tr->SetLocalScale(scale);
		}

		gameObj->Initialize();

		return gameObj;
	}
	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(lu::GameObject::eState::Destory);
	}
}