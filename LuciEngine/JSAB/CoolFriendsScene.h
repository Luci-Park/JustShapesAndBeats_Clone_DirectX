#pragma once
#include "LScene.h"

namespace lu::JSAB
{
	class CoolFriendsScene : public Scene
	{
	public:
		CoolFriendsScene();
		virtual ~CoolFriendsScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

