#include "LMaterial.h"
#include "LRenderer.h"
#include "LConstantBuffer.h"
#include "LResources.h"
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
		SetShader(Resources::Find<Shader>(L"SpriteShader"));
		SetTexture(Resources::Find<Texture>(path));
		return S_OK;
	}
	void Material::Binds()
	{
		if(mTexture)	
			mTexture->BindShaderResource(eShaderStage::PS, 0);
		if(mShader)
			mShader->Binds();

		
	}
	void Material::clear()
	{
		mTexture->clear();
	}
}