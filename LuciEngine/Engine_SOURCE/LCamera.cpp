#include "LCamera.h"
#include "LTransform.h"
#include "LGameObject.h"
#include "LApplication.h"
#include "LRenderer.h"
#include "LSceneManager.h"
#include "LScene.h"
#include "LMeshRenderer.h"
extern lu::Application application;

namespace lu
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			> b->GetComponent<Transform>()->GetPosition().z)
			return true;
		return false;
	}

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(100.0f)
		, mSize(1000.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
		, view(Matrix::Identity)
		, projection(Matrix::Identity)
	{
		EnableLayerMasks();
	} 
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		mTr = Owner()->mTransform;
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		CalculateBoundary();
	}
	void Camera::Update()
	{
	}
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		CalculateBoundary();
		RegisterCameraInRenderer();
		//Debug();
	}
	void Camera::Render()
	{
		View = view;
		Projection = projection;

		AlphaSortGameObjects();
		ZDepthSortTransparentGameObjects();

		RenderOpaque();

		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}
	bool Camera::CreateViewMatrix()
	{
		Vector3 pos = mTr->GetPosition();

		//Translate
		view = Matrix::Identity;
		view *= Matrix::CreateTranslation(-pos);

		//Rotation
		Vector3 up = mTr->Up();
		Vector3 right = mTr->Right();
		Vector3 foward = mTr->Forward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z; viewRotate._33 = foward.z;
		view *= viewRotate;
		return true;
	}
	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;

		if (width == 0 || height == 0) return false;
		if (type == eProjectionType::OrthoGraphic)
		{
			float orthorgraphicratio = mSize / 1000.0f;
			width *= orthorgraphicratio;
			height *= orthorgraphicratio;

			//LH = left handed
			projection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			projection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}
		return true;
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}
	void Camera::AlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (int i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> gameObjs = layer.GetGameObjects();
				CategorizeAlphaBlendGameObjects(gameObjs);
			}
		}
	}
	void Camera::ZDepthSortTransparentGameObjects()
	{
		std::sort(mCutOutGameObjects.begin()
			, mCutOutGameObjects.end()
			, CompareZSort);
		std::sort(mTransparentGameObjects.begin()
			, mTransparentGameObjects.end()
			, CompareZSort);
	}
	void Camera::CategorizeAlphaBlendGameObjects(const std::vector<GameObject*> gameObjects)
	{
		for (int i =0; i < gameObjects.size(); i++)
		{
			if (!gameObjects[i]->IsActive())
				continue;

			MeshRenderer* mr
				= gameObjects[i]->GetComponent<MeshRenderer>();
			if (mr == nullptr || !mr->IsActive())
				continue;

			std::shared_ptr<Material> mat = mr->GetMaterial();
			eRenderingMode mode = mat->GetRenderingMode();
			switch (mode)
			{
			case lu::graphics::eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back(gameObjects[i]);
				break;
			case lu::graphics::eRenderingMode::CutOut:
				mCutOutGameObjects.push_back(gameObjects[i]);
				break;
			case lu::graphics::eRenderingMode::Transparent:
				mTransparentGameObjects.push_back(gameObjects[i]);
				break;
			default:
				break;
			}
		}
	}
	void Camera::RenderOpaque()
	{
		for (int i = 0; i < mOpaqueGameObjects.size(); ++i)
		{
			if (mOpaqueGameObjects[i] != nullptr)
				mOpaqueGameObjects[i]->Render();
		}
	}
	void Camera::RenderCutOut()
	{
		for (int i = 0; i < mCutOutGameObjects.size(); ++i)
		{
			if (mCutOutGameObjects[i] != nullptr)
				mCutOutGameObjects[i]->Render();
		}
	}
	void Camera::RenderTransparent()
	{
		for (int i = 0; i < mTransparentGameObjects.size(); ++i)
		{
			if (mTransparentGameObjects[i] != nullptr)
				mTransparentGameObjects[i]->Render();
		}
	}
	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>dsState
			= renderer::depthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
	void Camera::Debug()
	{
		RECT rect = GetBoundary();

		mBoundaryMesh.position.x = (rect.left + rect.right) * 0.5;
		mBoundaryMesh.position.y = (rect.bottom + rect.top) * 0.5;
		mBoundaryMesh.scale.x = rect.right - rect.left;
		mBoundaryMesh.scale.y = rect.bottom - rect.top;
		mBoundaryMesh.rotation = Quaternion::Identity;
		mBoundaryMesh.color = Color::yellow;


		renderer::PushDebugMeshAttribute(mBoundaryMesh);
	}
	void Camera::CalculateBoundary()
	{
		Matrix ViewProjection = view * projection;
		Matrix InvertVP = ViewProjection.Invert();
		Vector4 frustumCorners[8];
		frustumCorners[0] = Vector4(-1.0f, -1.0f, 0.0f, 1.0f);
		frustumCorners[1] = Vector4(1.0f, -1.0f, 0.0f, 1.0f);
		frustumCorners[2] = Vector4(-1.0f, 1.0f, 0.0f, 1.0f);
		frustumCorners[3] = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		frustumCorners[4] = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
		frustumCorners[5] = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
		frustumCorners[6] = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
		frustumCorners[7] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		for (int i = 0; i < 8; ++i) {
			frustumCorners[i] = Vector4::Transform(frustumCorners[i], InvertVP);
			frustumCorners[i] /= frustumCorners[i].w;
		}
		float minX = FLT_MAX;
		float minY = FLT_MAX;
		float maxX = -FLT_MAX;
		float maxY = -FLT_MAX;

		for (int i = 0; i < 4; ++i) {
			minX = std::min(minX, frustumCorners[i].x);
			minY = std::min(minY, frustumCorners[i].y);
			maxX = std::max(maxX, frustumCorners[i].x);
			maxY = std::max(maxY, frustumCorners[i].y);
		}
		mBoundary = { (long)minX, (long)minY, (long)maxX, (long)maxY };
	}
}