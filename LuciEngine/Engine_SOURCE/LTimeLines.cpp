#include "LTimeLines.h"
namespace lu
{
	void Timeline::AddFunctionKey(double timestamp, std::function<void()> val)
	{
		FuncKey* key = new FuncKey(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddTextureKey(double timestamp, std::shared_ptr<graphics::Texture> val)
	{
		TextureKey* key = new TextureKey(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddQuaternionKey(double timestamp, Quaternion val)
	{
		QuaternionKey* key = new QuaternionKey(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddColorKey(double timestamp, Color val)
	{
		ColorKey* key = new ColorKey(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddVector3Key(double timestamp, Vector3 val)
	{
		Vector3Key* key = new Vector3Key(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddVector2Key(double timestamp, Vector2 val)
	{
		Vector2Key* key = new Vector2Key(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddFloatKey(double timestamp, float val)
	{
		FloatKey* key = new FloatKey(timestamp, val);
		keyframes.push_back(key);
	}
	void Timeline::AddBoolKey(double timestamp, bool val)
	{
		BoolKey* key = new BoolKey(timestamp, val);
		keyframes.push_back(key);
	}
}