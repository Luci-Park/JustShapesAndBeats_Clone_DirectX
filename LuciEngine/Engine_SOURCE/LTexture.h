#pragma once
#include "LResource.h"
#include "LGraphics.h"

#include "../Extern/DirectXTex/include/DirectXTex.h"
#include "../Extern/DirectXTex/include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\Extern\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\Extern\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

namespace lu::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);

	private:
		ScratchImage mImage; // original image
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}

