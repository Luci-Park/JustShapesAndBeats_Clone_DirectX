#pragma once
#include "LResource.h"
#include "LShader.h"
#include "LTexture.h"

namespace lu::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();
		
		void SetShader(Shader* shader) { mShader = shader; }
		void SetTexture(Texture* texture) { mTexture = texture; }

	private:
		Shader* mShader;
		Texture* mTexture;
	};
}

