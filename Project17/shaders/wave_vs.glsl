#version 430
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec4 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform float Time;
uniform float K = 2.5;
uniform float Velocity = 2.5;
uniform float Amp = 0.6;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main()
{	
	vec4 pos = vec4(vPosition, 1.0);
	
	float u = K*(pos.x - Velocity * Time);
	pos.y = Amp * sin(u);

	vec3 n = vec3(0.0);
	n.xy = normalize(vec2(-K*Amp*cos(u), 1.0));

	Position = mv_matrix * pos;
	Normal = mat3(mv_matrix)*n;
	
	gl_Position = proj_matrix*mv_matrix*pos;
}
