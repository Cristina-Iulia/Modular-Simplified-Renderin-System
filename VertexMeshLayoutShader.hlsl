struct VS_INPUT
{
	float4 position: POSITION0;
	float2 textcoord: TEXTCOORD0;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 textcoord: TEXTCOORD0;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	return output;
}