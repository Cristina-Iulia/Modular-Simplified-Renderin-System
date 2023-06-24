
struct VS_INPUT
{
	float4 position: POSITION0;
	float2 textcoord: TEXTCOORD0;
	float3 normal: NORMAL0;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 textcoord: TEXTCOORD0;
	float3 normal: NORMAL0;
	float3 direction_to_camera: TEXTCOORD1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 world_matrix;
	row_major float4x4 view_matrix;
	row_major float4x4 projection_matrix;
	float4 light_direction;
	float4 camera_pos;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//output.position = lerp(input.position, input.position_after, (sin(m_angle) + 1.0f) / 2.0f);
	// World space
	output.position = mul(input.position, world_matrix);
	output.direction_to_camera = normalize(output.position.xyz - camera_pos.xyz);
	// View space
	output.position = mul(output.position, view_matrix);
	// Screen space
	output.position = mul(output.position, projection_matrix);


	output.textcoord = input.textcoord;
	output.normal = input.normal;

	return output;
}