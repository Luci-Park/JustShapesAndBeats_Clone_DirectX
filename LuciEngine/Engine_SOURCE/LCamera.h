#pragma once
#include "LComponent.h"
#include "LGraphics.h"

namespace lu
{
	class Transform;
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perspective, 
			OrthoGraphic,
			None,
		};

		static Matrix& GetGpuViewMatrix() { return View; }
		static void SetGpuViewMatrix(Matrix view) { View = view; }
		static Matrix& GetGpuProjectionMatrix() { return Projection; }
		static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZDepthSortTransparentGameObjects();
		void CategorizeAlphaBlendGameObjects(const std::vector<GameObject*> gameObjects);
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();

		float GetSize() { return mSize; }
		void SetSize(float size) { mSize = size; }

		Matrix& GetViewMatrix() { return view; }
		Matrix& GetProjectionMatrix() { return projection; }

		RECT GetBoundary() { return mBoundary; }
	private:
		void Debug();
		void CalculateBoundary();
	private:
		static Matrix View;
		static Matrix Projection;

		Matrix view;
		Matrix projection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;
		RECT mBoundary;

		Transform* mTr;

		std::vector<GameObject*> mRenderTargets;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

		graphics::DebugMesh mBoundaryMesh;
	};
}

