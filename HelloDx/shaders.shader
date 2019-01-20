cbuffer MatrixBuffer 
{
    matrix worldMat;
    matrix viewMat;
    matrix projectMat;
};
struct VertexIn
{
    float4 position : POSITION;
    float4 color : COLOR;
};
struct PixelIn
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
PixelIn VShader(VertexIn vertex)
{
    PixelIn output;
    
    vertex.position.w = 1.0f;

    output.position = mul(vertex.position, worldMat);
    output.position = mul(output.position, viewMat);
    output.position = mul(output.position, projectMat);

    output.color = vertex.color;

	return output;
}
float4 PShader(PixelIn pixel) : SV_TARGET
{
    return pixel.color;
}