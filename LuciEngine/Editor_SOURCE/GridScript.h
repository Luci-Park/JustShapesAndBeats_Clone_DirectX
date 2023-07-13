#pragma once
#include "..\\Engine_SOURCE\\\LScript.h"
#include "..\\Engine_SOURCE\\LCamera.h"

namespace gui
{
	class GridScript : public lu::Script
	{
	public:
		GridScript();
		~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(lu::Camera* camera) { mCamera = camera; }

	private:
		lu::Camera* mCamera;
	};
}

