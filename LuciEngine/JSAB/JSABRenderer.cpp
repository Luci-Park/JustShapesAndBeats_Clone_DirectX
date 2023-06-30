#include "JSABRenderer.h"
#include "LResources.h"
#include "LTexture.h"
#include "LMaterial.h"
#include "LShader.h"
namespace lu::JSAB
{
	void LoadBackground()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};
		#pragma region  inputlayout
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
#pragma endregion
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"BackgroundPS.hlsl", "main");
		Resources::Insert(L"BackgroundShader", shader);
		GetDevice()->CreateInputLayout(arrLayout, 3, shader->GetVSCode(), shader->GetInputLayoutAddressOf());

		std::wstring folderPath = L"..\\..\\Assets\\Texture\\Background\\";
		std::vector<std::wstring> imgs = {
			L"black_background",
			L"darkblue_background",
			L"green_background",
			L"grey_background",
			L"turquoise_background",
			L"pink_background",
			L"purple_background",
			L"skyblue_background",
			L"white_background",
			L"annihilate_background"
		};

		for (int i = 0; i < imgs.size(); i++)
		{
			std::wstring filepath = folderPath + imgs[i] + L".png";
			std::wstring matName = imgs[i] + L"_mat";
			std::shared_ptr<Texture> tex = Resources::Load<Texture>(imgs[i], filepath);

			std::shared_ptr<Material> mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(tex);
			Resources::Insert(matName, mat);
		}
	}
	void InitializeGraphics()
	{
		LoadBackground();
	}
}