#include "vbotrianglebar.h"
#include "diging.h"

#include <cstdio>

VBOTriangleBar::VBOTriangleBar()
{
	float side = 1.0f;
	float side2 = side / 2.0f;

	float v[(6+12)* 3] = {
		// Front
		-side2, -side2, side2,
		side2, -side2, side2,
		0    ,	side2, side2,
		// Right
		side2, -side2, side2,
		side2, -side2, -side2,
		0,  side2, -side2,
		0,  side2, side2,
		// Back
		-side2, -side2, -side2,
		0,  side2, -side2,
		side2, -side2, -side2,
		// Left
		-side2, -side2, side2,
		0,  side2, side2,
		0,  side2, -side2,
		-side2, -side2, -side2,
		// Bottom
		-side2, -side2, side2,
		-side2, -side2, -side2,
		side2, -side2, -side2,
		side2, -side2, side2
	};

	float n[(6 + 12) * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Right
		0.8660f, 0.5f, 0.0f,
		0.8660f, 0.5f, 0.0f,
		0.8660f, 0.5f, 0.0f,
		0.8660f, 0.5f, 0.0f,
		// Back
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		// Left
		-0.8660f, 0.5f, 0.0f,
		-0.8660f, 0.5f, 0.0f,
		-0.8660f, 0.5f, 0.0f,
		-0.8660f, 0.5f, 0.0f,
		// Bottom
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	};

	float tex[(6 + 12) * 2] = {0,};

	GLuint el[] = {
		0,1,2,
		3,4,5,3,5,6,
		7,8,9,
		10,11,12,10,12,13,
		14,15,16,14,16,17
	};

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	unsigned int handle[4];
	glGenBuffers(4, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(float), v, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(float), n, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ARRAY_BUFFER, 18 * 2 * sizeof(float), tex, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(2);  // texture coords

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 27 * sizeof(GLuint), el, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void VBOTriangleBar::render() {
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
