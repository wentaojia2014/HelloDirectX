cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectMatrix;
};
cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
}
struct VertexInput
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal: NORMAL;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal: NORMAL;
    float3 viewDirection: TEXCOORD1;
};
PixelInput VShader(VertexInput vertex)
{
    PixelInput output;
    float4 worldPosition;
    
    vertex.position.w = 1.0f;

    output.position = mul(vertex.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectMatrix);

    output.tex = vertex.tex;

    output.normal = mul(vertex.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);
    worldPosition = mul(vertex.position, worldMatrix);
    output.viewDirection = normalize(cameraPosition.xyz - worldPosition.xyz);

	return output;
}
