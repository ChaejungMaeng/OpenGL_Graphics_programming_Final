#version 430

layout (location = 0) in vec3 VertexInitPos;
layout (location = 1) in vec3 VertexInitVel;
layout (location = 2) in float StartTime;

out float Transp;

uniform float Time;
uniform vec3 Gravity = vec3(0.0, -0.2, 0.0); // world coord.
uniform float ParticleLifetime = 5.0; 

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main()
{	
	vec3 pos = vec3(0.0);
	Transp = 0.0;

	if (Time > StartTime) {
		float t = Time - StartTime;

		if (t < ParticleLifetime) {
			pos = VertexInitPos + VertexInitVel * t + Gravity * t * t;
			Transp = 1.0 - t / ParticleLifetime;
		}
	}

	gl_Position = proj_matrix*mv_matrix*vec4(pos, 1.0);
}

