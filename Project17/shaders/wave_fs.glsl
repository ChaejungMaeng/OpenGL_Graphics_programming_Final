#version 430

in vec4 Position;
in vec3 Normal;

struct LightInfo
{
	vec4 Position;
	vec3 Intensity;
};
uniform LightInfo Light;

struct MaterialInfo
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform MaterialInfo Material;

out vec4 color;

vec3 phongModel()
{
	vec3 N = Normal;
	vec3 S = normalize(Light.Position.xyz - Position.xyz);
	vec3 V = normalize(-Position.xyz);
	vec3 R = reflect(-S,N);

	float sDotN = max(dot(S,N),0.0);

	vec3 ambient = Light.Intensity*Material.Ka;
	vec3 diffuse = Light.Intensity*Material.Kd*sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN > 0.0)
	  spec = Light.Intensity*Material.Ks*pow(max(dot(R,V),0.0),Material.Shininess);

	return ambient+diffuse+spec;
}

void main()
{
	color = vec4(phongModel(),1.0);
}
