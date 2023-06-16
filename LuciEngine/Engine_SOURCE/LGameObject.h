#pragma once
#include "LEntity.h"
#include "LComponent.h"

namespace lu
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
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
			return nullptr;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = GetComponent<T>();
			if (comp != nullptr) return comp;
			
			comp = new T();
			Component* buff = dynamic_cast<Component*>(comp); //upcast
			if (buff == nullptr)
				return nullptr;
			mComponents.push_back(buff);
			comp->SetOwner(this);

			return comp;
		}

	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}

