#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

void getEyeSpace(out vec3 norm, out vec3 position)
{
	position = vec3(mv_matrix*vec4(vPosition, 1.0));
	norm = normalize(mat3(mv_matrix)*vNormal);
}

void main()
{
	getEyeSpace(Normal, Position);
	TexCoord = vTexCoord;
	gl_Position = proj_matrix*mv_matrix*vec4(vPosition,1.0);
}