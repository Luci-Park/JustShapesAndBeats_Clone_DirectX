#pragma once
#include "LEntity.h"
#include "LComponent.h"
#include "LScript.h"
#include "LTransform.h"
namespace lu
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			InActive,
			Destory,
		};

		GameObject();
		GameObject(Transform* parent);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (int i = 0; i < mComponents.size(); i++)
			{
				component = dynamic_cast<T*>(mComponents[i]);
				if (component != nullptr)
					return component;
			}
			for (int i = 0; i < mScripts.size(); i++)
			{
				component = dynamic_cast<T*>(mScripts[i]);
				if (component != nullptr)
					return component;
			}
			return nullptr;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = GetComponent<T>();
			if (comp != nullptr) return comp;
			
			comp = new T();
			Component* buff = dynamic_cast<Component*>(comp); //upcast
			Script* script = dynamic_cast<Script*>(buff);
			if (buff == nullptr)
				return nullptr;
			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);
			comp->SetOwner(this);

			return comp;
		}

		eState GetState() { return mState; }
		void SetState(eState state);

		const std::vector<Script*>& GetScripts() { return mScripts; }
	public:
		Transform* mTransform;
	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
	};
}

