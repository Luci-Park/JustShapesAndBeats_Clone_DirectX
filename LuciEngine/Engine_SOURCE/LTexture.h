#pragma once
#include "LResource.h"
#include "LGraphics.h"

#include "../Extern/DirectXTex/include/DirectXTex.h"
#include "../Extern/DirectXTex/include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\Extern\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\Extern\\DirectXTex\\lib\\Release \\DirectXTex.lib")
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

		size_t GetWidth() { return mSize.x; }
		size_t GetHeight() { return mSize.y; }
		math::Vector3 GetSize() { return mSize; }
		double GetRatioHeight(float width) { return width / mRatio; }
		double GetRatioWidth(float height) { return height * mRatio; }

	private:
		ScratchImage mImage; // original image
		math::Vector3 mSize;
		double mRatio;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}

