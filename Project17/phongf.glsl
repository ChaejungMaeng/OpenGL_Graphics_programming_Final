#version 430

out vec4 color;
in vec4 eyeP;
in vec3 eyeN;

struct LightInfo{
	vec4 Position;  // Light Position in Eye Coords.
	vec3 Intensity; // RGB intensity for all ambient, diffuse, specular
};
uniform LightInfo lights[10];

struct MaterialInfo{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform MaterialInfo Material;

vec3 phongModel(int j, vec4 P, vec3 N)
{
	// view-space light
	vec3 S = normalize((lights[j].Position - P).xyz);
	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-S, N);

	float sDotN = max (dot (S, N), 0.0);

	vec3 ambient = lights[j].Intensity * Material.Ka;
	vec3 diffuse = lights[j].Intensity* Material.Kd * sDotN;
	vec3 spec = vec3(0.0);
	if (sDotN >0.0)
		spec = lights[j].Intensity * Material.Ks * pow(max (dot(R,V), 0.0), Material.Shininess);

	return ambient+diffuse+spec;
}

void main(void)
{
	vec3 LightIntensity = vec3(0.0);
	for(int i=0; i<10; i++)
		LightIntensity += phongModel(i, eyeP, eyeN);

	color = vec4(LightIntensity, 1.0);
}