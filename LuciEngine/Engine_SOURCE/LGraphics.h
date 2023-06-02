#pragma once

enum class eShaderStage
{
	VS, //Vertex Shader
	HS, //Hull Shader
	DS, //Domain Shader
	GS, //Geometry shader
	PS, //Pixel Shader
	CS, //Compute Shader
	None
};

enum class eCBType
{
	Transform,
	None
};