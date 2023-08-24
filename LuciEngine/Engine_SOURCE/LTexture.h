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

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT Load(const std::wstring& path) override;
		void BindShaderResource(eShaderStage stage, UINT startSlot);
		void BindUnorderedAccessViews(UINT slot);
		void ClearUnorderedAccessViews(UINT slot);
		void clear();

		size_t GetWidth() { return mSize.x; }
		size_t GetHeight() { return mSize.y; }
		math::Vector3 GetSize() { return mSize; }
		double GetRatioHeight(float width) { return width / mRatio; }
		double GetRatioWidth(float height) { return height * mRatio; }
		
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    GetRTV() { return  mRTV; }
		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { mRTV = rtv; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    GetDSV() { return  mDSV; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { mDSV = dsv; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  GetSRV() { return  mSRV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return  mUAV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { mTexture = texture; }

	private:
		ScratchImage mImage; // original image
		math::Vector3 mSize;
		double mRatio;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;

		D3D11_TEXTURE2D_DESC mDesc;
	};
}

