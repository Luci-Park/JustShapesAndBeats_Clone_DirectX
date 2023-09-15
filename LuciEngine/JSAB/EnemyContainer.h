#pragma once
#include "LObject.h"
#include "LGameObject.h"

namespace lu::JSAB
{
	template<typename T>
	class EnemyContainer
	{
	public:
		EnemyContainer(int size)
		{
			for (int i = 0; i < size; i++)
			{
				GameObject* obj = object::Instantiate<GameObject>(enums::eLayerType::Bullet);
				T* t = obj->AddComponent<T>();
				_objects.push_back(t);
			}
			_idx = 0;
		}
		~EnemyContainer() {}

		T* GetNext()
		{
			_idx %= _objects.size();
			T* ob = _objects[_idx++];
			ob->DeActivate();
			return ob;
		}
		void Reset()
		{
			for (int i = 0; i < _objects.size(); i++)
			{
				_objects[i]->DeActivate();
			}
			_idx = 0;
		}
	private:
		std::vector<T*> _objects;
		int _maxSize;
		int _idx;
	};
}

