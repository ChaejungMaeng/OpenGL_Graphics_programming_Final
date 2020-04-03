#version 430

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D Tex1;

struct LightInfo{
	vec4 Position;  
	vec3 Intensity;
};
uniform LightInfo Light;

struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform MaterialInfo Material;

out vec4 color;

vec3 phongModel(vec4 P, vec3 N, out vec3 ambAndDiff, out vec3 spec)
{
	vec3 L; 
	if (Light.Position.w == 0.0) 
		L = normalize(Light.Position.xyz);
	else 
		L = normalize((Light.Position - P).xyz);
	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L, N);
	float lDotN = max (dot (L, N), 0.0);
	vec3 ambient = Light.Intensity * Material.Ka;
	vec3 diffuse = Light.Intensity * Material.Kd * lDotN;
	ambAndDiff = ambient + diffuse;
	spec = vec3(0.0);
	if (lDotN >0.0)
		spec = Light.Intensity * Material.Ks * pow(max (dot(R,V), 0.0), Material.Shininess);
	
	return ambient+diffuse+spec;
}

void main(void)
{
	vec3 ambAndDiff, spec;
	vec3 LightIntensity = phongModel(vec4(Position, 1.0), Normal, ambAndDiff, spec);
	
	vec4 texColor = texture(Tex1, TexCoord);
	color = vec4(ambAndDiff, 1.0)*texColor + vec4(spec, 1.0);
}