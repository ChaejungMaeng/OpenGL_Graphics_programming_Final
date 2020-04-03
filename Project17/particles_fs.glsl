#version 430

in float Transp;
uniform sampler2D ParticleTex;

layout (location = 0) out vec4 color;

void main()
{
	color = texture(ParticleTex, gl_PointCoord);
	color.a *= Transp;
}
