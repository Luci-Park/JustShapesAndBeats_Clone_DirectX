#pragma once
#include "LuciEngine.h"
#include "LGraphics.h"


namespace lu::graphics
{
	class GraphicDevice_Dx11
	{
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		//Ready Device
		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDesc, UINT elementNum, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CompileFromFile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);

		bool CreateVertexShader(const void* pShaderByteCode, SIZE_T bytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11GeometryShader** ppGeometryShader);
		bool CreatePixelShader(const void* pShaderByteCode, SIZE_T bytecodeLength, ID3D11PixelShader** ppPixelShader);
		bool CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader);

		bool CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		bool CreateRasterizeState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState);
		bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState);
		bool CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState);

		bool CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
		bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);
		bool CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);
		bool CreateUnordedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);

		// after creation, you need to bind it to the rendering pipeline
		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		void BindVertexBuffer(ID3D11Buffer* const* ppVertexBuffers, UINT StartSlot, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT offset);
		void BindVertexShader(ID3D11VertexShader* pVertexShader);
		void BindHullShader(ID3D11HullShader* pHullShader);
		void BindDomainShader(ID3D11DomainShader* pDomainShader);
		void BindGeometryShader(ID3D11GeometryShader* pGeometryShader);
		void BindPixelShader(ID3D11PixelShader* pPixelShader);
		void BindComputeShader(ID3D11ComputeShader* pComputeShader);
		void Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);

		void BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		void BindUnorderedAccess(UINT slot, ID3D11UnorderedAccessView** ppUnorderedAccessViews, const UINT* pUAVInitialCounts);

		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindBuffer(ID3D11Buffer* buffer, void* data, UINT size);

		void BindSampler(eShaderStage stage, UINT startSlot, ID3D11SamplerState** ppSamplers);
		void BindViewPort(D3D11_VIEWPORT* viewPort);
		void BindRasterizeState(ID3D11RasterizerState* pRasterizerState);
		void BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState);
		void BindBlendState(ID3D11BlendState* pBlendState);

		void CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource);

		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();

		ID3D11Device* GetID3D11Device() { return mDevice.Get(); }

	private:
		// ���� �׷���ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice; 
		

		//  dx11���� ���������� ����̽���ü ���������ʰ�
		// �̰�ü�� �̿��Ͽ� ����� ������.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext; 
		
		// ���������� �׷��� �ؽ�ó(��ȭ��)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// ����Ÿ�ٿ� ������������ �ʰ� ����Ÿ�ٺ並 ���ؼ� �����Ѵ�.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// ���̹���
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// ���̹��ۿ� �����Ҽ� �ִ� ��
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// ������۸� �۾��� �������ִ� swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;
	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}