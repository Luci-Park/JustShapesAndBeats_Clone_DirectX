#include "guiEditor.h"
#include "..\\Engine_SOURCE\\LMesh.h"
#include "..\\Engine_SOURCE\\LResources.h"
#include "..\\Engine_SOURCE\\LTransform.h"
#include "..\\Engine_SOURCE\\LMeshRenderer.h"
#include "..\\Engine_SOURCE\\LMaterial.h"
#include "..\\Engine_SOURCE\\LRenderer.h"

#include "GridScript.h"

namespace gui
{

	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)lu::enums::eColliderType::End);

		std::shared_ptr<lu::Mesh> mesh
			= lu::Resources::Find<lu::Mesh>(L"DebugRect");
		std::shared_ptr<lu::Material> material
			= lu::Resources::Find<lu::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)lu::enums::eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)lu::enums::eColliderType::Rect]->AddComponent<lu::Transform>();
		lu::MeshRenderer* mr
			= mDebugObjects[(UINT)lu::enums::eColliderType::Rect]->AddComponent<lu::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");
		grid->mTransform->SetPosition(0.0f, 0.0f, -5.0);

		mr = grid->AddComponent<lu::MeshRenderer>();
		mr->SetMesh(lu::Resources::Find<lu::Mesh>(L"RectMesh"));
		mr->SetMaterial(lu::Resources::Find<lu::Material>(L"GridMaterial"));
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(lu::renderer::cameras[0]);

		mEditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{


		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
			= lu::renderer::depthStencilStates[(UINT)lu::graphics::eDSType::Less];
		lu::graphics::GetDevice()->BindDepthStencilState(ds.Get());

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const lu::graphics::DebugMesh& mesh
			: lu::renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
		lu::renderer::debugMeshes.clear();
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}

	}

	void Editor::DebugRender(const lu::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		lu::Transform* tr = debugObj->GetComponent<lu::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*ya::MeshRenderer * mr
			= debugObj->GetComponent<ya::MeshRenderer>();*/
			// main camera
		lu::Camera* mainCamara = lu::renderer::mainCamera;

		lu::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		lu::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}