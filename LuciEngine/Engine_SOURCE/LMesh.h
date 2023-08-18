#pragma once
#include "LResource.h"
#include "LGraphicDevice_Dx11.h"

namespace lu
{
	using namespace graphics;
	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT count);
		bool CreateIndexBuffer(void* data, UINT count);

		void BindBuffer();
		void Render();
		void RenderInstanced(UINT startIndexLocation);

		UINT GetIndexCount() { return mIndexCount; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;
	};
}

