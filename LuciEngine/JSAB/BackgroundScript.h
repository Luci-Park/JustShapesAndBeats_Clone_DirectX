#pragma once
#include "LScript.h"
#include "LMeshRenderer.h"
namespace lu::JSAB
{
	class BackgroundScript : public Script
	{
	public:
		enum class Backgrounds {
			TITLE,
			TITLEGREEN,
			BLACK,
			DARKBLUE,
			GREEN,
			GREY,
			TURQUOISE,
			PINK,
			PURPLE,
			SKYBLUE,
			WHITE,
			ANNIHILATE,
			END
		};
	private:
		static std::vector<std::shared_ptr<Texture>> _backgrounds;

	public:
		BackgroundScript();
		virtual ~BackgroundScript();

		virtual void Initialize() override;
		void SetBackground(Backgrounds type);
		void SetBackground(int type);
	private:
		lu::MeshRenderer* mMeshRenderer;
	};
}

