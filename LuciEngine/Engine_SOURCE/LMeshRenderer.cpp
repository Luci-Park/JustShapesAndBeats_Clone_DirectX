#include "LMeshRenderer.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LRenderer.h"

namespace lu
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
		, mColor(Color::white)
		, mInterpolation(0)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		mMesh->BindBuffer();
		mMaterial->Binds();

		renderer::MeshRendererCB mCB = {};
		mCB.tint = mMaterial->GetTint();
		mCB.color = mColor;
		mCB.interpolation = mInterpolation;
		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::MeshRenderer];
		cb->SetData(&mCB);
		cb->Bind(eShaderStage::PS);
				
		mMesh->Render();
		
		mMaterial->Clear();

	}
}