#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

PixelInput VS(VertexUV input)// : SV_POSITION//SV->RS
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
    
    return output;
}

cbuffer OutLineBuffer : register(b11)
{
    float2 imageSize;
}

static const float2 edges[9] =
{
    float2(-1, -1), float2(0, -1), float2(1, -1),
	float2(-1, 0), float2(0, 0), float2(1, 0),
	float2(-1, 1), float2(0, 1), float2(1, 1),
};

float4 PS(PixelInput input) : SV_TARGET //->SV->OM
{
    float minAlpha = 1.0f;
    float maxAlpha = 0.0f;
    float4 baseColor = diffuseMap.Sample(samp, input.uv);
	
    float2 div = 1 / imageSize;
	
    for (int i = 0; i < 9; i++)
    {
        float2 uvOffset = input.uv + div * edges[i];
        uvOffset = clamp(uvOffset, 0.0f, 1.0f);
        
        float4 sampleColor = diffuseMap.Sample(samp, uvOffset);
        minAlpha = min(minAlpha, sampleColor.a);
        maxAlpha = max(maxAlpha, sampleColor.a);
    }
	
    if (maxAlpha - minAlpha > 0.1)
    {
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    return baseColor;
}