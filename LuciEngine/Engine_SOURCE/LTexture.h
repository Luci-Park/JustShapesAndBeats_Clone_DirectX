#pragma once
#include "LResource.h"
#include "LGraphics.h"

#include "../Extern/DirectXTex/include/DirectXTex.h"
#include "../Extern/DirectXTex/include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\Extern\\DirectXTex\\lib\\DebugLib\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\Extern\\DirectXTex\\lib\\ReleaseLib\\DirectXTex.lib")
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
		void Clear();

		size_t GetWidth() { return mWidth; }
		size_t GetHeight() { return mHeight; }

	private:
		ScratchImage mImage; // original image
		size_t mWidth, mHeight;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}

