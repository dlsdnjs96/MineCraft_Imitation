#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
    float3 wPostion : POSITION0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Uv = input.Uv;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.wPostion = output.Position.xyz;
    output.Position = mul(output.Position, ViewProj);
    input.Normal.w = 0.0f;
    output.Normal = mul(input.Normal, World);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    
    float4 BaseColor = TextureD.Sample(SamplerD, input.Uv);
    BaseColor.a = 0.5f;

    return BaseColor;
    
    
    input.Uv.x = input.Uv.x + (sin(input.Uv.x * 5) * 0.03);
    input.Uv.y = input.Uv.y + (sin(input.Uv.y * 5) * 0.03);
    
    return TextureD.Sample(SamplerD, input.Uv);
}


