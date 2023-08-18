#pragma once
#include "LGraphics.h"
namespace lu::graphics
{
	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();

		bool Create(UINT size, UINT stride, eResourceViewType type, void* data, bool cpuAccess = false);
		bool CreateRWBuffer();
		void SetData(void* data, UINT stride);
		void GetData(void* data, UINT size);
		void BindSRV(eShaderStage stage, UINT slot);
		void BindUAV(UINT slot);
		void Clear();

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mWriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		eResourceViewType mType;

		UINT mSize;
		UINT mStride;

		UINT mSRVSlot;
		UINT mUAVSlot;
	};
}

