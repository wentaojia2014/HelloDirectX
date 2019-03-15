Texture2D shaderTexture;
SamplerState SampleType;
cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float4 specularColor;
    float3 lightDirection;
    float specularPower;
    float padding;
};
struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal: NORMAL;
    float3 viewDirection: TEXCOORD1;
};

float4 PShader(PixelInput pixel) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;

    color = ambientColor;
    textureColor = shaderTexture.Sample(SampleType, pixel.tex);
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    lightDir = -lightDirection;
    lightIntensity = saturate(dot(pixel.normal, lightDir));
    if (lightIntensity > 0.0f) 
    {
        color += (diffuseColor * lightIntensity);
        color = saturate(color);

        reflection = normalize(2 * lightIntensity * pixel.normal - lightDir);
        specular = pow (saturate(dot(reflection, pixel.viewDirection)), specularPower);
     
    }
    
    color = color * textureColor;
    color = saturate(color + specular);
    return color;
}
