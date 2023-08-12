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
		void Clear();

		std::shared_ptr<Shader> GetShader() { return mShader; }
		std::shared_ptr<Texture> GetTexture() { return mTexture; }
		Color GetTint() { return mTint; }
		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetTint(Color color) { mTint = color; }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode GetRenderingMode() { return mMode; }


	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;

		eRenderingMode mMode;
		Color mTint;
	};
}

