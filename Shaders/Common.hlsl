cbuffer VS_W : register(b0)
{
    matrix World;
}
cbuffer VS_VP : register(b1)
{
    matrix ViewProj;
}
//스켈레톤
#define MAX_BONE 256
cbuffer VS_Bones : register(b2)
{
    matrix Bones[MAX_BONE];
}

cbuffer VS_V : register(b3)
{
    matrix View;
}
cbuffer VS_P : register(b4)
{
    matrix Proj;
}

cbuffer GS_VP : register(b0)
{
    matrix GSViewProj;
}
cbuffer GS_View : register(b1)
{
    float4 GSViewPos;
}
cbuffer GS_View : register(b2)
{
    float4 GSViewUp;
}
cbuffer GS_View : register(b3)
{
    float4 GSViewForward;
}

cbuffer GS_CubeMap : register(b4)
{
    int CubeRenderType;
    float CubeSlider;
    float WaterIndex;
    float CubeMapPadding;
    
    matrix CubeViews[6];
    matrix CubeProjection;
    matrix CubeRotation;
};




cbuffer PS_ViewPos : register(b0)
{
    float4 ViewPos;
}

cbuffer PS_Material : register(b1)
{
    float4 Ka;
    float4 Kd;
    float4 Ks;
    float4 Ke;
    float Shininess;
    float Opacity;
    float environment;
    float MaterialPadding;
}

cbuffer PS_DirLight : register(b2)
{
    float4 DirLight;
    float4 DirColor;
}

#define MAX_LIGHT 16
struct Light
{
    //4
    int isActive;
    int Type;
    float Inner;
    float Outer;
	//
    int Size;
    float3 Direction;
    //4
    float3 Position;
    float Range;
    //4
    float4 Color;
};
cbuffer PS_Lights : register(b3)
{
    Light lights[MAX_LIGHT];
}

cbuffer PS_CubeMap : register(b4)
{
    int PS_CubeRenderType;
    float PS_CubeSlider;
    float PS_WaterIndex;
    float PS_CubeMapPadding;
    
    matrix PS_CubeViews[6];
    matrix PS_CubeProjection;
    matrix PS_CubeRotation;
};
//Texture3D a;

SamplerState DefalutSampler;

Texture2D TextureN : register(t0);
SamplerState SamplerN : register(s0);

Texture2D TextureD : register(t1);
SamplerState SamplerD : register(s1);

Texture2D TextureS : register(t2);
SamplerState SamplerS : register(s2);

Texture2D TextureE : register(t3);
SamplerState SamplerE : register(s3);

TextureCube TextureSky : register(t4);
SamplerState SamplerSky : register(s4);

TextureCube EnvironmentMap : register(t5);

TextureCube WaterMap : register(t6);
SamplerState SamplerWaterMap : register(s6);


matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0; //영행렬
    transform += mul(weights.x, Bones[(uint) indices.x]);
    transform += mul(weights.y, Bones[(uint) indices.y]);
    transform += mul(weights.z, Bones[(uint) indices.z]);
    transform += mul(weights.w, Bones[(uint) indices.w]);
    return transform;
}



//Pixel Function
float3 NormalMapping(float3 T, float3 B, float3 N, float2 Uv)
{
    T = normalize(T);
    B = normalize(B);
    N = normalize(N);
    
    [flatten]
    if (Ka.a)
    {
        
        // 130,130,255 (기본값) -> 0,0,1
        // 0.5,0.5,1.0
        float3 normal = TextureN.Sample(SamplerN, Uv).rgb;
        //float3 normal = float3(0.5, 0.5, 1.0);
        
        //세개의 법선으로 회전행렬을 만듦
        float3x3 TBN = float3x3(T, B, N);
        
        // rgb (0~1,0~1,0~1) *2
        // rgb (0~2,0~2,0~2) -1
        // rgb (-1~1,-1~1,-1~1)
        N = normal * 2.0f - 1.0f;
        //매핑한 법선을 회전시키기  normal * Matrix
        N = normalize(mul(N, TBN));
    }
    
    return N;
}


float4 DiffuseMapping(float2 Uv)
{
    [flatten]
    if (Kd.a)
        return TextureD.Sample(SamplerD, Uv);
    
    return float4(1, 1, 1, 1);
}
float3 SpecularMapping(float2 Uv)
{
    [flatten]
    if (Ks.a)
        return TextureS.Sample(SamplerS, Uv).rgb;
    
    return float3(1, 1, 1);
}

float3 EnvironmentMapping(float3 Normal, float3 wPosition)
{
    [flatten]
    if (environment != 0.0f)
    {
        if (PS_CubeRenderType == 0)
        {
            float3 ViewDir = normalize(wPosition - ViewPos.xyz);
            float3 Reflect = reflect(ViewDir, Normal);
            return EnvironmentMap.Sample(DefalutSampler, Reflect) * environment;
        }
        else if (PS_CubeRenderType == 1)
        {
            float3 ViewDir = normalize(wPosition - ViewPos.xyz);
            float3 Refract = refract(ViewDir, Normal, PS_CubeSlider);
            return EnvironmentMap.Sample(DefalutSampler, Refract) * environment;
        }
        else if (PS_CubeRenderType == 2)
        {
            float3 ViewDir = normalize(wPosition - ViewPos.xyz);
            float3 Refract = refract(ViewDir, Normal, PS_CubeSlider);
            float3 UV = mul(Refract, (float3x3) PS_CubeRotation);
            float3 WaterRGB = WaterMap.Sample(SamplerWaterMap, UV).rgb;
            
             //return float4(WaterRGB, 1);
            WaterRGB = WaterRGB * 2.0f - 1.0f;
            Refract += WaterRGB * PS_WaterIndex;
            
            return EnvironmentMap.Sample(DefalutSampler, Refract) * environment;
        }
    }
    return float3(0, 0, 0);
}

float3 EmissiveMapping(float3 BaseColor, float2 Uv, float3 Normal, float3 wPosition)
{
    //Emissive
    float3 Emissive = 0;
    float3 EmissiveMap = BaseColor;
    float3 ViewDir = normalize(ViewPos.xyz - wPosition);
    //반사색이 있을때만 Emissive 값을 계산한다.
    [flatten]
    //rgb중에 값이 하나라도 0 이 아니면
    if (any(Ke.rgb))
    {
        //계수
        float emissive = 1.0f - saturate(dot(Normal, ViewDir));
        emissive = smoothstep(0.0f, 1.0f, emissive);
        Emissive = emissive * Ke.rgb;
    }
    //EmissiveMap이 존재할때 텍스쳐 색상을 입혀준다.
    [flatten]
    if (Ke.a)
    {
        EmissiveMap = TextureE.Sample(SamplerE, Uv).rgb;
    }
    Emissive *= EmissiveMap;
    return saturate(Emissive);
}


float3 DirLighting(float3 BaseColor, float3 SpecularMap, float3 Normal, float3 wPostion)
{
    float3 DirectionLight = normalize(DirLight.xyz);
    float Diffuse = saturate(dot(-DirectionLight, Normal));
    
    float3 RecflectLight = reflect(DirectionLight, Normal);
    float3 ViewDir = normalize(ViewPos.xyz - wPostion);
    float Specular = saturate(dot(ViewDir, RecflectLight));
    Specular = pow(Specular, Shininess);
    
    //         계수 * 머터리얼 *  DiffuseMap
    float3 D = Diffuse * Kd.rgb * BaseColor;
    float3 S = Specular * Ks.rgb * SpecularMap;
    return saturate((D + S) * DirColor.rgb);
    //return S;
}

float3 PointLighting(float3 BaseColor, float3 SpecularMap, float3 Normal, float3 wPosition, int idx)
{
    //return float3(1, 1, 1);
    float3 DirectionLight = lights[idx].Position - wPosition;
    float distanceToLight = length(DirectionLight);
    DirectionLight /= distanceToLight;
    
    float distanceToLightNormal = 1.0f - saturate(distanceToLight / lights[idx].Range);
    float attention = distanceToLightNormal * distanceToLightNormal;
    
    //빛의계수
    float Diffuse = saturate(dot(DirectionLight, Normal)) * attention;
  
    
    float3 RecflectLight = reflect(DirectionLight, Normal);
    float3 ViewDir = normalize(ViewPos.xyz - wPosition);
    float Specular = saturate(dot(ViewDir, RecflectLight)) * attention;
    Specular = pow(Specular, Shininess);
    
    float3 D = Diffuse * Kd.rgb * BaseColor;
    float3 S = Specular * Ks.rgb * SpecularMap;
    
    return saturate((D + S) * lights[idx].Color.rgb);
}

float3 SpotLighting(float3 BaseColor, float3 SpecularMap, float3 Normal, float3 wPosition, int idx)
{
    //픽셀에서 라이트향하는 방향
    float3 DirectionLight = lights[idx].Position - wPosition;
    float distanceToLight = length(DirectionLight);
    DirectionLight /= distanceToLight;
    
    float distanceToLightNormal = 1.0f - saturate(distanceToLight / lights[idx].Range);
    float attention = distanceToLightNormal * distanceToLightNormal;
    
    float cosAngle = saturate(dot(normalize(-lights[idx].Direction),
    DirectionLight));
    
    //예시용
    ////84도 -> 코사인값
    //float inner = cos(radians(lights[idx].Inner));
    ////Inner 이하인값만
    //if (cosAngle > inner)
    //{
    //    attention = 1.0f;
    //}
    
    // 0 ~ 90 -> 1 ~ 0 
    float outer = cos(radians(lights[idx].Outer));
    // 0 ~ 90   -> 1 ~ 무한
    float inner = 1.0f / cos(radians(lights[idx].Inner));
    
    cosAngle = saturate((cosAngle - outer) * inner);
    attention *= cosAngle;
    
    //빛의계수
    float Diffuse = saturate(dot(DirectionLight, Normal)) * attention;
  
    
    float3 RecflectLight = reflect(DirectionLight, Normal);
    float3 ViewDir = normalize(ViewPos.xyz - wPosition);
    float Specular = saturate(dot(ViewDir, RecflectLight)) * attention;
    Specular = pow(Specular, Shininess);
    
    float3 D = Diffuse * Kd.rgb * BaseColor;
    float3 S = Specular * Ks.rgb * SpecularMap;
    
    return saturate((D + S) * lights[idx].Color.rgb);
}

float4 Lighting(float4 BaseColor, float2 Uv, float3 Normal, float3 wPosition)
{
    float3 SpecularMap = SpecularMapping(Uv);
    
    
    // 디퓨즈 + 스펙큘러
    float4 Result = float4(DirLighting(BaseColor.rgb, SpecularMap,
    Normal, wPosition),
    BaseColor.a);
    
    if (Result.a > Opacity)
        Result.a = Opacity;
    
    //광원 수만큼 반복
    for (int i = 0; i < lights[0].Size; i++)
    {
        //[flatten]
        if (!lights[i].isActive)
            continue;
        
        ////[flatten]
        if (lights[i].Type == 0)
        {
            Result.rgb += PointLighting(BaseColor.rgb, SpecularMap,
            Normal, wPosition, i);
        }
        else if (lights[i].Type == 1)
        {
            Result.rgb += SpotLighting(BaseColor.rgb, SpecularMap,
            Normal, wPosition, i);
        }
    }
    
    
    //발광
    //Ambient
    Result.rgb += Ka.rgb * BaseColor.rgb;
    //Emissive
    Result.rgb += EmissiveMapping(BaseColor.rgb, Uv, Normal, wPosition);
    
    Result.rgb += EnvironmentMapping(Normal, wPosition);
    
    // 0 ~ 1 가두기
    return saturate(Result);
}