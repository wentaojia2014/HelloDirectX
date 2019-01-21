cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectMatrix;
};
struct VertexInput
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
PixelInput VShader(VertexInput vertex)
{
    PixelInput output;
    
    vertex.position.w = 1.0f;

    output.position = mul(vertex.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectMatrix);

    output.color = vertex.color;

	return output;
}
float4 PShader(PixelInput pixel) : SV_TARGET
{
    return pixel.color;
}
