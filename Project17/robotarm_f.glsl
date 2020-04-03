#version 430

uniform vec3 color;
out vec4 fcolor;

void main()
{
	fcolor = vec4(color, 1.0);
}

