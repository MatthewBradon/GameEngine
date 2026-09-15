// simple.slang

struct VSInput {
    float3 Pos;
    float3 Color;
};

struct VSOutput {
    float4 Pos : SV_POSITION;
    float3 Color : COLOR;
};

[shader("vertex")]
VSOutput vertexMain(VSInput inputPosition)
{
    VSOutput output;
    
    // Convert the 3D input position to a 4D homogeneous coordinate (X, Y, Z, 1.0)
    output.Pos = float4(inputPosition.Pos, 1.0f);
    output.Color = inputPosition.Color;
    
    return output;
}

[shader("fragment")]
float4 fragmentMain(VSOutput input) : SV_Target
{
    return float4(input.Color, 1.0f);
}
