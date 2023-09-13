#pragma once
#include "LuciEngine.h"
#include <LMath.h>
using namespace lu::math;
namespace lu::graphics
{
	class Texture;
}
namespace lu
{
	struct KeyFrame
	{
		KeyFrame() {}
		KeyFrame(double time) : timestamp(time) {}
		virtual ~KeyFrame() {}
		double timestamp;
		bool operator<(const KeyFrame& other) const
		{
			return timestamp < other.timestamp;
		}
	};

	struct FuncKey : KeyFrame
	{
		FuncKey() :value(nullptr) {}
		FuncKey(double time, std::function<void()> val) : KeyFrame(time), value(val) {}
		std::function<void()>value;
	};
	struct TextureKey : KeyFrame
	{
		TextureKey() :value(nullptr) {}
		TextureKey(double time, std::shared_ptr<graphics::Texture> val) : KeyFrame(time), value(val) {}
		std::shared_ptr<graphics::Texture> value;
	};
	struct ColorKey : KeyFrame {
		ColorKey() {}
		ColorKey(double time, Color val) :KeyFrame(time), value(val) {}
		Color value;
	};
	struct QuaternionKey : KeyFrame {
		QuaternionKey() {}
		QuaternionKey(double time, Quaternion val) :KeyFrame(time), value(val) {}
		Quaternion value;
	};
	struct Vector3Key : KeyFrame { 
		Vector3Key() {}
		Vector3Key(double time, Vector3 val) :KeyFrame(time), value(val) {}
		Vector3 value; 
	};
	struct Vector2Key : KeyFrame { 
		Vector2Key() {}
		Vector2Key(double time, Vector2 val) :KeyFrame(time), value(val) {}
		Vector2 value; 
	};
	struct FloatKey : KeyFrame {
		FloatKey() {}
		FloatKey(double time, float val) :KeyFrame(time), value(val) {}
		float value; 
	};
	struct BoolKey : KeyFrame { 
		BoolKey() {}
		BoolKey(double time, bool val) :KeyFrame(time), value(val) {}
		bool value; 
	};

	struct Timeline
	{
		~Timeline()
		{
			for (int i = 0; i < keyframes.size(); i++)
				if (keyframes[i])
				{
					delete keyframes[i];
					keyframes[i] = nullptr;
				}
		}
		int currIndex = 0;
		std::vector<KeyFrame*> keyframes;
		bool IsComplete() { return currIndex >= keyframes.size(); }
		void Reset() { currIndex = 0; }
		void AddFunctionKey(double timestamp, std::function<void()> val);
		void AddTextureKey(double timestamp, std::shared_ptr<graphics::Texture> val);
		void AddQuaternionKey(double timestamp, Quaternion val);
		void AddColorKey(double timestamp, Color val);
		void AddVector3Key(double timestamp, Vector3 val);
		void AddVector2Key(double timestamp, Vector2 val);
		void AddFloatKey(double timestamp, float val);
		void AddBoolKey(double timestamp, bool val);

		void SortKeyframes() { std::sort(keyframes.begin(), keyframes.end()); }
	};
}

