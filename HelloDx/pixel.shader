struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

Texture2D shaderTexture;
SamplerState SampleType;
float4 PShader(PixelInput pixel) : SV_TARGET
{
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, pixel.tex);
    return textureColor;
}
