#include "LRenderer.h"
#include "LResources.h"
#include "LTexture.h"
#include "LMaterial.h"
#include "LParticleShader.h"

namespace lu::renderer
{
	ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<lu::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshes;

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

		shader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		shader = Resources::Find<Shader>(L"ParticleShader");
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
	void LoadMesh()
	{
		std::vector<Vertex> verticies = {};
		std::vector<UINT> indicies = {};

		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		verticies.push_back(v);
		indicies.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(verticies.data(), verticies.size());
		mesh->CreateIndexBuffer(indicies.data(), indicies.size());
		Resources::Insert(L"PointMesh", mesh);

		//RECT
		verticies.resize(4);
		verticies[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		verticies[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		verticies[0].uv = Vector2(0.0f, 0.0f);

		verticies[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		verticies[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		verticies[1].uv = Vector2(1.0f, 0.0f);

		verticies[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		verticies[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		verticies[2].uv = Vector2(1.0f, 1.0f);

		verticies[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		verticies[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		verticies[3].uv = Vector2(0.0f, 1.0f);

		// Vertex Buffer
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(verticies.data(), verticies.size());

		indicies.push_back(0);
		indicies.push_back(1);
		indicies.push_back(2);

		indicies.push_back(0);
		indicies.push_back(2);
		indicies.push_back(3);
		mesh->CreateIndexBuffer(indicies.data(), indicies.size());



		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(verticies.data(), verticies.size());
		rectDebug->CreateIndexBuffer(indicies.data(), indicies.size());

		// Circle Debug Mesh
		verticies.clear();
		indicies.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		verticies.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			verticies.push_back(center);
		}
		for (int i = 0; i < verticies.size() - 2; ++i)
		{
			indicies.push_back(i + 1);
		}
		indicies.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(verticies.data(), verticies.size());
		circleDebug->CreateIndexBuffer(indicies.data(), indicies.size());
	}


	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		//Meshrenderer Buffer
		constantBuffer[(UINT)eCBType::MeshRenderer] = new ConstantBuffer(eCBType::MeshRenderer);
		constantBuffer[(UINT)eCBType::MeshRenderer]->Create(sizeof(MeshRendererCB));

		//Particle Buffer
		constantBuffer[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffer[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		//Noise Buffer
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));
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

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		Resources::Insert(L"DebugShader", debugShader);

		//particleSystem compute shader
		std::shared_ptr<ParticleShader> psShader = std::make_shared<ParticleShader>();
		psShader->Create(L"ParticleCS.hlsl", "main");
		Resources::Insert(L"ParticleSystemShader", psShader);

		//particel shader
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert(L"ParticleShader", particleShader);
	}

	void LoadTexture()
	{
		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");

		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");


		std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"SpriteMaterial", material);

		texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", material);

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");

		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		std::shared_ptr<Shader> debugShader	= Resources::Find<Shader>(L"DebugShader");

		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		material = std::make_shared<Material>();
		material->SetShader(particleShader);
		Resources::Insert(L"ParticleMaterial", material);
		material->SetTexture(Resources::Find<Texture>(L"CartoonSmoke"));
	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshes.push_back(mesh);
	}

	void Render()
	{
		for (int i =0; i < cameras.size(); i++)
		{
			if (cameras[i] == nullptr)
				continue;

			cameras[i]->Render();
		}
		mainCamera = cameras.size() > 0 ? cameras[0] : nullptr;
		cameras.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}
}