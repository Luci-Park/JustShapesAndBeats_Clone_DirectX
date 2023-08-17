#pragma once
#include "LResource.h"
#include "LGraphics.h"
namespace lu::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader(int x, int y, int z);
		ComputeShader();
		virtual ~ComputeShader();

		bool Create(const std::wstring& name, const std::string& methodName);
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }
		void OnExecute();

		virtual void Binds();
		virtual void Clear();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;//code

		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;

		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;
	};
}

