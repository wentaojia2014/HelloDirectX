Texture2D shaderTexture;
SamplerState sampleType;
cbuffer PixelBuffer 
{
    float4 pixelColor;
};
struct PixelInputType
{
	float4 position: SV_POSITION;
	float2 tex: TEXCOORD0;
};

float4 main(PixelInputType input):SV_TARGET
{
    float4 color;
	color = shaderTexture.Sample(sampleType, input.tex);
    if (color.r == 0.0f)
    {
        color.a = 0.0f;
    }
    else 
	{
        color.a = 1.0f;
        color = color * pixelColor;
	}
    return color;
}
