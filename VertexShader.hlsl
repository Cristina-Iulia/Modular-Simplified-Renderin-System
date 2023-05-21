
struct VS_INPUT
{
	float4 position: POSITION;
	float4 position_after: POSITION1;
	float3 color: COLOR;
	float3 color_after: COLOR1;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color_after: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float m_angle;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//output.position = lerp(input.position, input.position_after, (sin(m_angle) + 1.0f) / 2.0f);
	// World space
	output.position = mul(input.position, m_world);
	// View space
	output.position = mul(output.position, m_view);
	// Screen space
	output.position = mul(output.position, m_proj);
	output.color = input.color;
	output.color_after = input.color_after;

	return output;
}