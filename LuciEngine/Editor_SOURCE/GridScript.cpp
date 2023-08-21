#include "GridScript.h"
#include "..\\Engine_SOURCE\\LConstantBuffer.h"
#include "..\\Engine_SOURCE\\LCamera.h"
#include "..\\Engine_SOURCE\\LTransform.h"
#include "..\\Engine_SOURCE\\LApplication.h"
#include "..\\Engine_SOURCE\\LGameObject.h"
#include "..\\Engine_SOURCE\\LRenderer.h"
#include "..\\Engine_SOURCE\\LTime.h"
#include "..\\Engine_SOURCE\\LObject.h"

extern lu::Application application;
namespace gui
{

	GridScript::GridScript()
		: mCamera(nullptr)
	{
	}
	GridScript::~GridScript()
	{
	}
	void GridScript::Initialize()
	{
	}
	void GridScript::Update()
	{

		if (mCamera == nullptr)
			return;


		lu::GameObject* gameObj = mCamera->Owner();

		lu::Transform* tr = gameObj->GetComponent<lu::Transform>();
		Vector3 pos = tr->GetPosition();

		float scale = mCamera->GetSize();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		///cs buffer
		lu::graphics::ConstantBuffer* cb
			= lu::renderer::constantBuffer[(int)lu::graphics::eCBType::Grid];

		lu::renderer::GridCB data;
		data.cameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.resolution = resolution;
		data.cameraScale = Vector2(scale, scale);

		cb->SetData(&data);
		cb->Bind(lu::graphics::eShaderStage::VS);
		cb->Bind(lu::graphics::eShaderStage::PS);
	}


	void GridScript::LateUpdate()
	{
	}
	void GridScript::Render()
	{
	}
}