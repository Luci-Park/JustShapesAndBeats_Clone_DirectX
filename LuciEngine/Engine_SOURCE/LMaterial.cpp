#include "LMaterial.h"
#include "LRenderer.h"
#include "LConstantBuffer.h"
namespace lu::graphics
{
	Material::Material()
		: Resource(lu::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mTint(Color::white)
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

		
	}
	void Material::Clear()
	{
		mTexture->Clear();
	}
}