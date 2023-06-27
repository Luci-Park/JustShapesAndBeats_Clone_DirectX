#include "LRenderer.h"
#include "LResources.h"
#include "LTexture.h"
#include "LMaterial.h"
#include "JSABRenderer.h"

namespace lu::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	void SetupState()
	{
#pragma region Input Layout
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"TriangleShader");
		GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressOf());
		
		shader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressOf());
#pragma endregion
#pragma region Sampler State
		D3D11_SAMPLER_DESC sd = {};
		sd.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&sd, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		sd.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&sd, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rd = {};
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rd, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rd, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rd, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rd, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsd = {};
		dsd.DepthEnable = true; //깊이 테스트를 하는 가?
		dsd.DepthFunc = D3D11_COMPARISON_LESS; //같은 위치에 있는 픽셀들 중 깊이가 가장 작은 것으로 그린다.
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsd, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsd.DepthEnable = true;
		dsd.DepthFunc = D3D11_COMPARISON_GREATER;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsd, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsd.DepthEnable = true;
		dsd.DepthFunc = D3D11_COMPARISON_LESS;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsd.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsd, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsd.DepthEnable = false;
		dsd.DepthFunc = D3D11_COMPARISON_LESS;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsd.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsd, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC bd = {};
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		bd.AlphaToCoverageEnable = false;
		bd.IndependentBlendEnable = false;
		bd.RenderTarget[0].BlendEnable = true;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bd, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		bd.AlphaToCoverageEnable = false;
		bd.IndependentBlendEnable = false;

		bd.RenderTarget[0].BlendEnable = true;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&bd, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion
	}

	void LoadBuffer()
	{
		// Vertex Buffer
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Resources::Insert(L"SpriteShader", spriteShader);

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial", spriteMateiral);
		}

		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial02", spriteMateiral);
		}

	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();

		lu::JSAB::InitializeGraphics();

		//std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		//texture = Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		//texture->BindShader(eShaderStage::PS, 0);
	}
	void Release()
	{
		for (int i = 0; i < (UINT)eCBType::End; ++i)
		{
			if (constantBuffer[i] != nullptr)
			{
				delete constantBuffer[i];
				constantBuffer[i] = nullptr;
			}
		}
	}
}