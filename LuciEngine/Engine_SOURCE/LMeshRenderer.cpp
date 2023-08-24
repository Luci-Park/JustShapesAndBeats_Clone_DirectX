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
		, flipX(false)
		, flipY(false)
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
		Transform* tr = Owner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		mMesh->BindBuffer();
		mMaterial->Binds();

		renderer::MeshRendererCB mCB = {};
		mCB.tint = mMaterial->GetTint();
		mCB.color = mColor;
		mCB.interpolation = mInterpolation;
		Vector2 flip;
		flip.x = flipX ? 0.8 : 0.2;
		flip.y = flipY ? 0.8 : 0.2;
		mCB.Flip = flip;
		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::MeshRenderer];
		cb->SetData(&mCB);
		cb->Bind(eShaderStage::PS);
				
		mMesh->Render();
		
		mMaterial->clear();

	}
}