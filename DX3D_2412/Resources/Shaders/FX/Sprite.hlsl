#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

PixelInput VS(VertexUV input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
	
    output.uv = input.uv;
	
    return output;
}

cbuffer FrameBuffer : register(b10)
{
    float2 maxFrame;
    float2 curFrame;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float2 uv = (input.uv / maxFrame) + (curFrame / maxFrame);
	
    return diffuseMap.Sample(samp, uv) * mDiffuse;
}