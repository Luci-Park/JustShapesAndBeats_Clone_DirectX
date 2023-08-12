#include "LMaterial.h"
#include "LRenderer.h"
#include "LConstantBuffer.h"
namespace lu::graphics
{
	Material::Material()
		: Resource(lu::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mMode(eRenderingMode::Opaque)
	{
	}
	Material::~Material()
	{
	}
	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	void Material::Binds()
	{
		if(mTexture)	
			mTexture->BindShader(eShaderStage::PS, 0);
		if(mShader)
			mShader->Binds();

		renderer::MaterialCB mCB = {};
		mCB.Color = mColor;

		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Material];
		cb->SetData(&mCB);
		cb->Bind(eShaderStage::PS);
	}
	void Material::Clear()
	{
		mTexture->Clear();
	}
}