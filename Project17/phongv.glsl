#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 eyeP;
out vec3 eyeN;

void getEyeSpace(out vec3 norm, out vec4 position)
{
	position = mv_matrix * vec4(vPosition, 1.0);
	norm = normalize(mat3(mv_matrix)*vNormal);
}


void main()
{
	getEyeSpace(eyeN, eyeP);

	gl_Position = proj_matrix* mv_matrix * vec4(vPosition,1.0);
}