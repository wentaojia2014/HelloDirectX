Texture2D shaderTexture;
SamplerState SampleType;
cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float padding;
};
struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal: NORMAL;
};

float4 PShader(PixelInput pixel) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    color = ambientColor;
    textureColor = shaderTexture.Sample(SampleType, pixel.tex);

    lightDir = -lightDirection;
    lightIntensity = saturate(dot(pixel.normal, lightDir));
    if (lightIntensity > 0.0f) 
    {
        color += (diffuseColor * lightIntensity);
    }
    color = saturate(color);

    color = color * textureColor;
    return color;
}
