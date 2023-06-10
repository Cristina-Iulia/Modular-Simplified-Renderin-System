
Texture2D EarthTex: register(t0);
sampler EarthTexSampler: register(s0);

Texture2D EarthSpec: register(t1);
sampler EarthSpecSampler: register(s1);

Texture2D EarthClouds: register(t2);
sampler EarthCloudsSampler: register(s2);

Texture2D EarthNight: register(t3);
sampler EarthNightSampler: register(s3);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 textcoord: TEXTCOORD0;
	float3 normal: NORMAL0;
	float3 direction_to_camera: TEXTCOORD1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	float4 camera_pos;
	float time_cloud;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float4 earth_tex = EarthTex.Sample(EarthTexSampler, input.textcoord);
	float4 earth_spec = EarthSpec.Sample(EarthSpecSampler, input.textcoord).r;
	float4 earth_clouds = EarthClouds.Sample(EarthCloudsSampler, input.textcoord + float2(time_cloud/100.0, 0)).r;
	float4 earth_night = EarthNight.Sample(EarthNightSampler, input.textcoord);

	//AMBIENT LIGHT
	float ka = 1.5; // ambient reflection constatnt
	float3 ia = float3(0.09, 0.082, 0.082);
	ia *= (earth_tex.rgb);
	float3 ambient_light = ka * ia;

	//DIFFUSE LIGHT
	float kd = 0.7;
	float3 id_day = float3(1.0, 1.0, 1.0);
	id_day *= (earth_tex.rgb + earth_clouds);

	float3 id_night = float3(1.0, 1.0, 1.0);
	id_night *= (earth_night.rgb + earth_clouds*0.3);

	float amount_diffuse_light = dot(m_light_direction.xyz, input.normal);

	float3 id = lerp(id_night, id_day, (amount_diffuse_light + 1.0) / 2.0);

	float3 diffuse_light = kd * id;


	//SPECULAR LIGHT
	float ks = earth_spec;
	float3 is = float3(1.0, 1.0, 1.0);
	float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
	float shininess = 30.0;
	float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);

	float3 specular_light = ks * amount_specular_light * is;

	float3 final_light = ambient_light + diffuse_light + specular_light;

	return float4(final_light, 1.0);
}