#pragma once
#include "..\\Engine_SOURCE\\LObject.h"
#include "..\\Engine_SOURCE\\LGameObject.h"

namespace lu::JSAB
{
	template<typename T>
	class BulletPool
	{
	public:
		BulletPool(int size)
		{
			for (int i = 0; i < size; i++)
			{
				GameObject* obj = object::Instantiate<GameObject>(enums::eLayerType::Bullet);
				T* t = obj->AddComponent<T>();
				_objects.push_back(t);
			}
			_idx = 0;
		}
		~BulletPool() {}

		T* GetNext()
		{
			_idx = (_idx + 1) % _objects.size();
			T* obj = _objects[_idx];			
			obj->DeActivate();
			return obj;
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

