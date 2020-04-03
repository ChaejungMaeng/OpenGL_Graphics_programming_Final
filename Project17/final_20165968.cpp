//#include "bmpreader.h"
//#include "cg.h"
//#include "vboplane.h"
//#include "vbomesh.h"
//#include "vbosphere.h"
//#include "vboteapot.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <GL/gl.h>
//#include <mmsystem.h>    
//#pragma comment(lib,"winmm.lib") 
//#include "Digitalv.h"
///////////////////////////////////////////////////////
//#pragma comment(lib,"winmm")
//
//extern GLuint compile_shaders(const char*  vsource, const char*  fsource);
//GLuint rendering_program1;
//GLuint rendering_program2;
//GLuint rendering_program3;
//GLint mv_location;
//GLint proj_location;
//GLuint tex_object[3];
//
//void startup();
//void render();
//void shutdown();
//extern void version();
//extern GLuint compile_shaders(const char*  vsource, const char*  fsource);
//
//GLuint rendering_program;
//
//float t;
//
//const int WIDTH = 800; const int HEIGHT = 600;
//VBOPlane* plane;
//GLuint initPos, initVel, startTime, particles2;
//GLuint nParticles;
//
//inline float randFloat() { return ((float)rand() / RAND_MAX); }
//inline float mix(float x, float y, float a) { return ((1.0 - a)*x + a * y); }
//void initBuffers();
//
//
//void generate_texture(GLubyte * data, int width, int height)
//{
//	int x, y;
//	for (y = 0; y < height; y++)
//	{
//		for (x = 0; x < width; x++)
//		{
//			GLubyte c = (((x & 0x8) == 0) ^ ((y & 0x8) == 0))*255.0;
//			data[(y * width + x) * 4 + 0] = c;
//			data[(y * width + x) * 4 + 1] = c;
//			data[(y * width + x) * 4 + 2] = c;
//			data[(y * width + x) * 4 + 3] = 1.0f;
//		}
//	}
//}
//
//
//int HalfShapeAnimationTick = 0;
//int BigteapotAnimationTick = 0;
//int BigAnimationTick = 0;
//int StarAnimationTick = 0;
//int TreeAnimationTick = 0;
//int StarAnimationTick2 = 0;
//
//bool HalfShapeAnimationFlag = false;
//bool HandleAnimationFlag = false;
//bool BigAnimationFlag = false;
//bool StarAnimationFlag = false;
//bool TreeAnimationFlag = false;
//bool StarAnimationFlag2 = false;
//
//#define MAX_PARTICLES 2000
//#define WCX		640
//#define WCY		480
//#define RAIN	1
//#define SNOW	0
//#define	HAIL	2
//
//float slowdown = 2.0;
//float velocity = 0.0;
//float zoom = -40.0;
//float pan = 0.0;
//float tilt = 0.0;
//float hailsize = 0.1;
//int loop;
//int fall;
//
////floor colors
//float r = 0.0;
//float g = 0.0;
//float b = 0.0;
//float ground_points[21][21][3];
//float ground_colors[21][21][4];
//float accum = -10.0;
/////////////////////////////////////////////
//typedef struct {
//	// Life
//	bool alive;	// is the particle alive?
//	float life;	// particle lifespan
//	float fade; // decay
//	// color
//	float red;
//	float green;
//	float blue;
//	// Position/direction
//	float xpos;
//	float ypos;
//	float zpos;
//	// Velocity/Direction, only goes down in y dir
//	float vel;
//	// Gravity
//	float gravity;
//}particles;
//
//// Paticle System
//particles par_sys[MAX_PARTICLES];
///////////////////////////////////////////////////////
//typedef vec4  color4;
//typedef vec4  point4;
//#define GL_PI 3.14
//#define ParticleNum 1000
//
//typedef struct {
//	float position[3];
//	float oldPos[3];
//	float velocity[3];
//	float color[3];
//	float energy;
//	float size;
//} Attrib_Particle, *pAttrib_Particle;
//
//Attrib_Particle Particle[ParticleNum];
//
//void Draw_And_Update_Particle()
//{
//	for (int i = 0; i < ParticleNum; i++)
//	{
//		glPointSize(Particle[i].size);
//		glBegin(GL_POINTS);
//		glColor4f(Particle[i].color[0], Particle[i].color[1], Particle[i].color[2], Particle[i].energy);
//		glVertex3f(Particle[i].position[0], Particle[i].position[1], Particle[i].position[2]);
//		glEnd();
//
//		Particle[i].position[0] = Particle[i].oldPos[0] + Particle[i].velocity[0];
//		Particle[i].position[1] = Particle[i].oldPos[1] + Particle[i].velocity[1];
//		Particle[i].position[2] = Particle[i].oldPos[2] + Particle[i].velocity[2];
//
//		Particle[i].oldPos[0] = Particle[i].position[0];
//		Particle[i].oldPos[1] = Particle[i].position[1];
//		Particle[i].oldPos[2] = Particle[i].position[2];
//		Particle[i].energy -= 0.01f;
//	}
//}
///////////////////////////////////////////////////////
///*
//void createHalfSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int color)
//{
//	// function createHalfSphere()
//	//구의 중심 x, y, z 좌표를 받아 반구를 만드는 함수
//	//x : 반구의 중심 x 좌표
//	//y : 반구의 중심 y 좌표
//	//z : 반구의 중심 z 좌표
//	//raidus : 반구의 반지름
//	
//	GLfloat angley;     //y축 값을 구하기 위한 각도
//	GLfloat nexty;      //다음 y축 값을 구하기 위한 각도
//	GLfloat anglex;     //x, y축 값을 구하기 위한 각도
//
//	glColor3ub(87, 130, 169 + color);      //반구의 색 지정
//	glBegin(GL_QUAD_STRIP);
//	for (angley = 0.0f; angley <= (0.5f*GL_PI); angley += ((0.5f*GL_PI) / 8.0f))        //반구만 그려야 하므로 0.5곱함
//	{
//		y = radius * sin(angley);                 //y축 값 계산
//		nexty = angley + ((0.5f*GL_PI) / 8.0f);     //다음 angley값 저장
//		for (anglex = 0.0f; anglex < (2.0f*GL_PI); anglex += (GL_PI / 8.0f))
//		{
//			x = radius * cos(angley)*sin(anglex);
//			z = radius * cos(angley)*cos(anglex);
//			glNormal3f(-cos(angley)*sin(anglex), -sin(angley), -cos(angley)*cos(anglex));   //반구의 안쪽으로 normal 벡터 생성
//			glVertex3f(x, y, z);
//
//			x = radius * cos(nexty)*sin(anglex);
//			z = radius * cos(nexty)*cos(anglex);
//			glNormal3f(-cos(nexty)*sin(anglex), -sin(nexty), -cos(nexty)*cos(anglex));
//			glVertex3f(x, radius*sin(nexty), z);
//		}
//	}
//	glEnd();
//}
//*/
//
//void calcNormal(float v[3][3], float out[3])
//{
//	/* function calcNormal()
//	 : 점 3개를 받아 해당 삼각형의 normal vector를 구하는 함수
//	v[3][3] : (x, y, z) 점 좌표 3개
//	out[3] : normal 벡터를 반환받을 벡터 3개
//	※ glut함수를 쓰면 느리므로 직접 제작
//	*/
//	float v1[3], v2[3], length;
//	static const int x = 0;
//	static const int y = 1;
//	static const int z = 2;
//
//	v1[x] = v[0][x] - v[1][x]; v1[y] = v[0][y] - v[1][y]; v1[z] = v[0][z] - v[1][z];
//	v2[x] = v[2][x] - v[1][x]; v2[y] = v[2][y] - v[1][y]; v2[z] = v[2][z] - v[1][z];
//
//	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
//	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
//	out[z] = v1[x] * v2[y] - v1[y] * v2[x];
//
//	length = (float)sqrt(out[x] * out[x] + out[y] * out[y] + out[z] * out[z]);
//	if (length == 0.0f)
//		length = 1.0f;
//
//	out[x] /= length;
//	out[y] /= length;
//	out[z] /= length;
//}
//
//
////--------------------------------------------------------------------------------------------------------------------------------------------------
////
// //  DRAWING
////
////--------------------------------------------------------------------------------------------------------------------------------------------------
//
//void initParticles(int i) {
//	par_sys[i].alive = true;
//	par_sys[i].life = 1.0;
//	par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
//
//	par_sys[i].xpos = (float)(rand() % 21) - 10;
//	par_sys[i].ypos = 10.0;
//	par_sys[i].zpos = (float)(rand() % 21) - 10;
//
//	par_sys[i].red = 1.0;
//	par_sys[i].green = 1.0;
//	par_sys[i].blue = 1.0;
//
//	par_sys[i].vel = velocity;
//	par_sys[i].gravity = -0.8;//-0.8;
//
//}
//
///*
//void drawRain() {
//	float x, y, z;
//	for (loop = 0; loop < MAX_PARTICLES; loop = loop + 2) {
//		if (par_sys[loop].alive == true) {
//			x = par_sys[loop].xpos;
//			y = par_sys[loop].ypos;
//			z = par_sys[loop].zpos + zoom;
//
//			// Draw particles
//			glColor3f(0.8, 0.8, 0.8);
//			glBegin(GL_LINES);
//			glVertex3f(x, y + 15, z + 40);
//			glVertex3f(x, y + 15.5, z + 40);
//			glEnd();
//
//			// Update values
//			//Move
//			// Adjust slowdown for speed!
//			par_sys[loop].ypos += par_sys[loop].vel / (slowdown * 1000);
//			par_sys[loop].vel += par_sys[loop].gravity;
//			// Decay
//			par_sys[loop].life -= par_sys[loop].fade;
//
//			if (par_sys[loop].ypos <= -20) {
//				par_sys[loop].life = -1.0;
//			}
//			//Revive
//			if (par_sys[loop].life < 0.0) {
//				initParticles(loop);
//			}
//		}
//	}
//}
//*/
//
//// For Snow
//void drawSnow() {
//
//	float x, y, z;
//	for (loop = 0; loop < MAX_PARTICLES; loop = loop + 2) {
//		if (par_sys[loop].alive == true) {
//			x = par_sys[loop].xpos;
//			y = par_sys[loop].ypos;
//			z = par_sys[loop].zpos + zoom;
//
//			// Draw particles
//			glColor3f(1.0, 1.0, 1.0);
//			glBegin(GL_POLYGON);
//			glColor3f(1.0, 1.0, 1.0);
//			glVertex3f(x, y + 15, z + 40);
//			glVertex3f(x, y + 15.1, z + 40);
//			glVertex3f(x - 0.1, y + 15.1, z + 40);
//			glVertex3f(x - 0.1, y + 15, z + 40);
//			glEnd();
//
//			// Update values
//			//Move
//			par_sys[loop].ypos += par_sys[loop].vel / (slowdown * 1000);
//			par_sys[loop].vel += par_sys[loop].gravity;
//			//// Decay
//			par_sys[loop].life -= par_sys[loop].fade;
//
//			if (par_sys[loop].ypos <= -10) {
//				int zi = z - zoom + 10;
//				int xi = x + 10;
//				ground_colors[zi][xi][0] = 1.0;
//				ground_colors[zi][xi][2] = 1.0;
//				ground_colors[zi][xi][3] += 1.0;
//				if (ground_colors[zi][xi][3] > 1.0) {
//					ground_points[xi][zi][1] += 0.1;
//				}
//				par_sys[loop].life = -1.0;
//			}
//
//			//Revive
//			if (par_sys[loop].life < 0.0) {
//				initParticles(loop);
//			}
//		}
//	}
//}
//
//void startup();
//void render();
//extern void version();
//extern GLuint compile_shaders(const char*  vsource, const char*  fsource);
//
//struct scene {
//	int width = 1400, height = 800;
//
//	// modeling 변수
//	//	VBOCube *cube;
//	VBOPlane *plane;
//	VBOMesh *mesh_island, *mesh_fox, *mesh_bunny, *mesh_toyarmy, *mesh_street_light, *mesh_car, *mesh_deer, *mesh_tree_under, *mesh_tree, *mesh_star, *mesh_stack, *mesh_gift, *mesh_bench, *mesh_lamp, *mesh_ornament, *mesh_ornament2, *mesh_land;
//	VBOTeapot *teapot, *teapot_small;																									   //torus = new VBOTorus(0.7f, 0.3f, 50, 50)
//	//VBOTeapot *teapot;
//	//VBOSphere *sphere;
//
//	// view  변수
//	mat4 look, model, view, projection;
//	vec3 mousepos;  // mouse 위치
//	vec3 camerapos; // camera 위치
//	int uimode; // 마우스 버튼 선택
//	float angle;
//
//	//  vao 변수
//	GLuint rendering_program;
//	GLuint vertex_array_object;
//	GLint mv_location;
//	GLint proj_location;
//	GLint color_loc;
//};
//scene sc;
//
//void startup()
//{
//	/******* OpenGL Initialization */
//	/******* OpenGL Initialization */
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL); //Passes if the incoming depth value is less than or
//	/**** Shaders as variables */
//	sc.rendering_program = compile_shaders("phongmlv.glsl", "phongmlf.glsl");
//	glUseProgram(sc.rendering_program);
//	sc.camerapos = vec3(-100.0f, 50.0f, 50.0f);
//	// modeling
//	sc.plane = new VBOPlane(10.0f, 10.0f, 100, 100);
//	sc.mesh_deer = new VBOMesh("deer.obj", true);//성 - 실행시간 조금
//
//	sc.mesh_tree_under = new VBOMesh("smoke_detector.obj", true);
//	sc.mesh_tree = new VBOMesh("LowPolyTree.obj", true);
//	sc.mesh_stack = new VBOMesh("stackP.obj", true);
//	sc.mesh_star = new VBOMesh("star.obj", true);
//
//
//	sc.mesh_gift = new VBOMesh("gift_box.obj", true);
//	sc.mesh_car = new VBOMesh("car.obj", true);
//	sc.mesh_bunny = new VBOMesh("bunny.obj", true);
//	sc.mesh_fox = new VBOMesh("foxdoll.obj", true);
//
//	sc.mesh_bench = new VBOMesh("Bench_LowRes.obj", true);
//
//	//sc.mesh_lamp = new VBOMesh("street lamp.obj", true);
//	sc.mesh_toyarmy = new VBOMesh("toyarmy.obj", true);
//
//	sc.mesh_ornament = new VBOMesh("Metal.obj", true);
//	sc.mesh_ornament2 = new VBOMesh("Wooden.obj", true);
//
//	sc.mesh_land = new VBOMesh("round table.obj", true);
//
//	sc.mesh_island = new VBOMesh("island2.obj", true);
//
//
//	sc.teapot = new VBOTeapot(25, mat4(1.2f));
//	sc.teapot_small = new VBOTeapot(25, mat4(1.0f));
//
//
//
//
//
//
//	//sc.sphere = new VBOSphere();
//	// viewing
//	sc.angle = 0.957283f;
//	sc.model = mat4(1.0);
//	sc.view = LookAt(vec3(1.5f, 1.2f, 1.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	sc.projection = Perspective(70.0f, (float)sc.width / sc.height, 0.1f, 10.0f);
//
//	sc.mv_location = glGetUniformLocation(sc.rendering_program, "mv_matrix");
//	sc.proj_location = glGetUniformLocation(sc.rendering_program, "proj_matrix");
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//
//	// Lighting
//
//
//	glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[0].Position"), //맨 앞 : diffuse정도
//		5, sc.view*vec4(5.0, 1.2, 0.0, 1.0));
//	//glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[1].Position"),
//	//	5, sc.view*vec4(0.0, 1.2, -5.0, 1.0));
//	//glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[2].Position"),
//	//	5, sc.view*vec4(-5.0, 1.2, 0.0, 1.0));
//	//glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[3].Position"),
//	//	5, sc.view*vec4(0.0, 1.2, 5.0, 1.0));
//	//glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[5].Position"),
//	//	5, sc.view*vec4(-1.0, 1.2, -1.0, 1.0));
//	glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[4].Position"),
//		1, sc.view*vec4(4.0, 1.2, 4.0, 1.0));
//	/*glUniform4fv(glGetUniformLocation(sc.rendering_program, "lights[6].Position"),
//		1, sc.view*vec4(-4.0, 1.2, 4.0, 1.0));
//*/
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[0].Intensity"), 0.1, 0.1, 0.0);
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[1].Intensity"), 0.0, 0.0, 0.8);
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[2].Intensity"), 0.8, 0.0, 0.0);
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[3].Intensity"), 0.0, 0.8, 0.0);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[4].Intensity"), 1.0, 0.768, 0.709);
//	/*glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[5].Intensity"), 0.8, 0.8, 0.0);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "lights[5].Intensity"), 0.0, 0.8, 0.0);*/
//
//	rendering_program1 = compile_shaders("mult_tex_v.glsl", "mult_tex_f.glsl");
//	glUseProgram(rendering_program1);
//	sc.teapot = new VBOTeapot(25, mat4(1.2f));
//	sc.teapot_small = new VBOTeapot(25, mat4(1.0f));
//
////	glActiveTexture(GL_TEXTURE0);
////	tex_object[0] = BMPReader::loadTex("brick1.bmp");
////	glActiveTexture(GL_TEXTURE1);
////	tex_object[1] = BMPReader::loadTex("fire.bmp");
////	glActiveTexture(GL_TEXTURE2);
////	tex_object[0] = BMPReader::loadTex("smoke.bmp"); //사방
//////	tex_object[0] = BMPReader::loadTex("back_grad.bmp");
////	glActiveTexture(GL_TEXTURE3);
////	tex_object[1] = BMPReader::loadTex("왼쪽_2.bmp");
////	glActiveTexture(GL_TEXTURE4);
////	tex_object[1] = BMPReader::loadTex("fire.bmp");
////	glActiveTexture(GL_TEXTURE5);
////	tex_object[1] = BMPReader::loadTex("fire.bmp"); //바닥
////
////	glActiveTexture(GL_TEXTURE6);
////	tex_object[1] = BMPReader::loadTex("rkdgus2.bmp");
////
////	glActiveTexture(GL_TEXTURE7);
////	tex_object[1] = BMPReader::loadTex("rkdgus3.bmp");
////
////	glActiveTexture(GL_TEXTURE8);
////	tex_object[1] = BMPReader::loadTex("8.bmp");
////
////	glActiveTexture(GL_TEXTURE9);
////	tex_object[1] = BMPReader::loadTex("9.bmp");
//
//	///////////////////////////////////////////////////////////////////////////
//
//	glActiveTexture(GL_TEXTURE0);
//	tex_object[0] = BMPReader::loadTex("brick1.bmp");
//	glActiveTexture(GL_TEXTURE1);
//	tex_object[1] = BMPReader::loadTex("dmswls2.bmp");
//	glActiveTexture(GL_TEXTURE2);
//	tex_object[0] = BMPReader::loadTex("back_grad.bmp");
//	glActiveTexture(GL_TEXTURE3);
//	tex_object[1] = BMPReader::loadTex("왼쪽_2.bmp");
//	glActiveTexture(GL_TEXTURE4);
//	tex_object[1] = BMPReader::loadTex("fire.bmp");
//	glActiveTexture(GL_TEXTURE5);
//	tex_object[1] = BMPReader::loadTex("rkdgus.bmp");
//
//	glActiveTexture(GL_TEXTURE6);
//	tex_object[1] = BMPReader::loadTex("rkdgus2.bmp");
//
//	glActiveTexture(GL_TEXTURE7);
//	tex_object[1] = BMPReader::loadTex("rkdgus3.bmp");
//
//	glActiveTexture(GL_TEXTURE8);
//	tex_object[1] = BMPReader::loadTex("8.bmp");
//
//	glActiveTexture(GL_TEXTURE9);
//	tex_object[1] = BMPReader::loadTex("9.bmp");
//
//	glActiveTexture(GL_TEXTURE10);
//	tex_object[1] = BMPReader::loadTex("smoke.bmp");
//
//	glActiveTexture(GL_TEXTURE11);
//	tex_object[1] = BMPReader::loadTex("star_2.bmp");
//
//	glActiveTexture(GL_TEXTURE12);
//	tex_object[1] = BMPReader::loadTex("light.bmp");
//
//	glActiveTexture(GL_TEXTURE13);
//	tex_object[1] = BMPReader::loadTex("fire_2.bmp");
//
//	//////////////////////////////////////////////////////////////////
//
//	t = 0.0;
//	/**** Shaders as variables */
//	rendering_program3 = compile_shaders("shaders/particles_vs.glsl", "shaders/particles_fs.glsl");
//	glUseProgram(rendering_program3);
//
//	// modeling
//	plane = new VBOPlane(13.0f, 10.0f, 200, 2);
//
//	// matrices
//	mat4 model = mat4(1.0);  t = 0.0f;
//	mat4 view = LookAt(vec3(3.0f, 1.5f, 3.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	mat4 projection = Perspective(60.0f, (float)WIDTH / HEIGHT, 0.3f, 100.0f);
//
//	mv_location = glGetUniformLocation(rendering_program3, "mv_matrix");
//	proj_location = glGetUniformLocation(rendering_program3, "proj_matrix");
//
//	glUniformMatrix4fv(mv_location, 1, GL_TRUE, view*model);
//	glUniformMatrix4fv(proj_location, 1, GL_TRUE, projection);
//
//	// Generate our vertex buffers
//	initBuffers();
//
//	// the particle texture
//	glActiveTexture(GL_TEXTURE0);
//	BMPReader::loadTex("fire.bmp");
//	glUniform1i(glGetUniformLocation(rendering_program3, "ParticleTex"), 0);
//}
//
//void initBuffers()
//{
//	nParticles = 120000;
//
//	glGenVertexArrays(1, &particles2);
//	glBindVertexArray(particles2);
//
//	// Generate the buffers 
//	glGenBuffers(1, &initPos);
//	glGenBuffers(1, &initVel);   // Initial velocity buffer 
//	glGenBuffers(1, &startTime); // Start time buffer 
//
//	// Allocate space for all buffers 
//	int size = nParticles * 3 * sizeof(float);
//	glBindBuffer(GL_ARRAY_BUFFER, initPos);
//	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, initVel);
//	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, startTime);
//	glBufferData(GL_ARRAY_BUFFER, nParticles * sizeof(float), NULL, GL_STATIC_DRAW);
//
//	// Fill the first position and velocity buffer with random velocities 
//	vec3 v(0.0f);
//	float velocity, theta, phi;
//	GLfloat *data0 = new GLfloat[nParticles * 3];
//	GLfloat *data = new GLfloat[nParticles * 3];
//
//	for (unsigned int i = 0; i < nParticles; i++) {
//		theta = mix(0.0, (float)M_PI / 6.0f, randFloat());
//		phi = mix(0.0f, (float)2 * M_PI, randFloat());
//		v.x = sinf(theta) * cosf(phi);
//		v.y = cosf(theta);
//		v.z = sinf(theta) * sinf(phi);
//		data0[3 * i] = 0.2*v.x; data0[3 * i + 1] = 0.0; data0[3 * i + 2] = 0.2*v.z;
//
//		velocity = mix(1.25f, 1.5f, randFloat());
//		v = normalize(v)*velocity * 2;
//		data[3 * i] = v.x;
//		data[3 * i + 1] = v.y;
//		data[3 * i + 2] = v.z;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, initPos);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, initVel);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	glEnableVertexAttribArray(1);
//
//
//	// Fill the start time buffer 
//	float *data1 = new GLfloat[nParticles];
//	float time = 0.0f;
//	float rate = 0.00075f;
//	for (unsigned int i = 0; i < nParticles; i++) {
//		data1[i] = time;
//		time += rate;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, startTime);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, nParticles * sizeof(float), data1);
//	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, NULL);
//	glEnableVertexAttribArray(2);
//
//
//
//	delete[] data;
//	delete[] data1;
//
//}
//
//void render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//glClearColor(0.1215, 0.0627, 0.1176, 1.0);
//	glClearColor(0.0215, 0.0627, 0.0176, 1.0);
//	glUseProgram(sc.rendering_program);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glLoadMatrixf((GLfloat*)sc.projection);
//
//	glMatrixMode(GL_MODELVIEW);
//
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1f, 0.1f, 0.1f); //색상
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f); //라이팅 정도
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f); //이게 퐁을 결정하는 정도
//	//glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 50.0f); //퐁의크기 (값이 작을수록 커짐)
//	
//
//	/******** Mesh_deer */
//	// Materials
//	/*
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.9f, 0.9f, 0.7f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.96f, 0.95f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.1f, 0.1f, 0.1f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model = RotateY(-180);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-1.5f, 0.0f, 1.5f));  //x양옆 //y위아래 //z앞뒤 
//	sc.model *= Scale(0.0015f);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//	*/
//
//	//////Mesh_deer  // Materials
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(1.8f, 0.0f, -2.0f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(150);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)* Translate(vec3(-1.8f, 0.0f, 2.0f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(330);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-2.8f, 0.0f, 0.2f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(270);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(2.8f, 0.0f, -0.2f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(90);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-2.0f, 0.0f, -1.7f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(240);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(2.0f, 0.0f, 1.7f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(60);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(0.0f, 0.0f, 2.7f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(360);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(0.0f, 0.0f, -2.7f));
//	sc.model *= Scale(0.0015f);
//	sc.model *= RotateY(180);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_deer->render();
//
//	////////////////////////////////////////////////////////////////////////////////
//
//	/******** Mesh_tree_under  */
//	/*
//	// Materials
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.306f, 0.188f, 0.3725f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.6f, 0.6f, 0.6f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= Translate(vec3(0.0f, 0.0f, 0.5f));
//	sc.model *= Scale(3.0f);
//
//	sc.model *= RotateY(-BigteapotAnimationTick * 0.3);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_tree_under->render();
//
//	/******** Mesh_tree  
//	// Materials
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.9725f, 0.7764f, 0.4823f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.6f, 0.6f, 0.6f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= Translate(vec3(0.0f, 2.5f, 0.5f));
//	sc.model *= Scale(2.3f);
//	sc.model *= RotateY(-BigteapotAnimationTick * 0.15);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_tree->render();
//
//	*/
//
//
//	/******** Mesh_star  */
//	// Materials
//	/*
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= Translate(vec3(0.0f, 5.1f, 0.5f));
//	sc.model *= Scale(0.005f);
//	sc.model *= RotateX(90);
//	sc.model *= RotateY(StarAnimationTick*0.6);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	////////////////////////////////////////////////////////////////////////////////////////////////
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.6) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.5) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.45) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//	
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.4) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.2) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//	
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.25) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.1686f, 0.3804f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.15) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//	*/
//	
//	/*
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.63) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.57) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.53) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.47) *Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.42) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.38) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.25) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.19) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.17) * Translate(vec3(0.0f, -7.4f, -1.5f));
//	sc.model *= Scale(0.0005f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.96f, 0.8589f, 0.498f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateZ(StarAnimationTick*0.15) * Translate(vec3(0.0f, -7.1f, -1.5f));
//	sc.model *= Scale(0.001f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	*/
//
//	/******** Mesh_stack  */ //Present
//	/////////////////////////////////////////////////////////////////////////
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= Translate(vec3(3.2f, 0.8f, -6.5f)); //x양옆 //y위아래 //z앞뒤
////	sc.model *= RotateZ(StarAnimationTick*0.17) * Translate(vec3(2.8f, 1.5f, -3.5f)); //x양옆 //y위아래 //z앞뒤 
//	sc.model *= Scale(0.023f);
//	sc.model *= RotateX(-90);
////	sc.model *= RotateZ(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_stack->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= Translate(vec3(-3.2f, 0.8f, -6.5f)); //x양옆 //y위아래 //z앞뒤 
//	sc.model *= Scale(0.023f);
//	sc.model *= RotateX(-90);
////	sc.model *= RotateZ(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_stack->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//    sc.model *= Translate(vec3(1.0f, 0.8f, -9.0f)); //x양옆 //y위아래 //z앞뒤 
//	sc.model *= Scale(0.023f);
//	sc.model *= RotateX(-90);
////	sc.model *= RotateZ(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_stack->render();
//
//	/////////////////////////////////////////////////////////////////////////
//
//	/*
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.1686f, 0.3804f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//	
//	
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(0.0f, -2.0f, 8.5f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.1686f, 0.3804f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(0.0f, -2.0f, -8.5f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.1686f, 0.3804f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(8.5f, -2.0f, 0.0f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.1686f, 0.3804f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(-8.5f, -2.0f, 0.0f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(-6.0f, -2.0f, -6.0f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(6.0f, -2.0f, -6.0f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(6.0f, -2.0f, 6.0f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0705f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick*0.17) * Translate(vec3(-6.0f, -2.0f, 6.0f));
//	sc.model *= Scale(0.003f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_star->render();
//	glUseProgram(rendering_program1);
//	*/
//
//
//	
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	/******** Mesh_toyarmy  */
//	// Materials
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.173f, 0.22f, 0.42f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-0.4f, -0.5f, 1.1f)); //x양옆 //y위아래 //z앞뒤 
//	sc.model *= Scale(0.12f);
//	sc.model *= RotateY(90);
//	sc.model *= RotateX(-90);
//	sc.model *= RotateZ(BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_toyarmy->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.173f, 0.22f, 0.42f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(1.5f, -0.5f, -0.6f));
//	sc.model *= Scale(0.12f);
//	sc.model *= RotateY(90);
//	sc.model *= RotateX(-90);
//	sc.model *= RotateZ(BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_toyarmy->render();
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.173f, 0.22f, 0.42f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-1.2f, -0.5f, -1.2f));
//	sc.model *= Scale(0.12f);
//	sc.model *= RotateY(90);
//	sc.model *= RotateX(-90);
//	sc.model *= RotateZ(BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_toyarmy->render();
//
//
//
//	//////// Mesh_bunny
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.125f, 0.184f, 0.259f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f); //라이팅 정도
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f); //이게 퐁을 결정하는 정도
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 20.0f); //퐁의크기 (값이 작을수록 커짐)
//	sc.model = mat4(1.0f); 
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(1.0f, -0.7f, 0.5f));
//	sc.model *= Scale(5.0f);
//	sc.model *= RotateY(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_bunny->render();
//
//	
//	////CAR///////////////////////////
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.725f, 0.478f, 0.341f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.7f, 0.7f, 0.7f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-1.2f, -0.8f, 0.0f));
//	sc.model *= Scale(0.3f);
//	sc.model *= RotateY(-120);
//	sc.model *= RotateY(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_car->render();
//
//	////FOX/////////////////////////
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.725f, 0.478f, 0.341f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.7f, 0.7f, 0.7f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(0.3f, 0.0f, -1.0f));
//	sc.model *= Scale(0.1f);
//	sc.model *= RotateY(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_fox->render();
//
//
//
//
//
//
//	///////////Mesh_ornament 
//	/* 
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.572f, 0.572f, 0.654f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= RotateY(StarAnimationTick2*0.03)* Translate(vec3(-2.0f, 0.2f, 1.3f));
//	sc.model *= Scale(0.15f);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_ornament->render();
//
//	///Mesh_ornament2  
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.572f, 0.592f, 0.6f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.8f, 0.8f, 0.8f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-1.8f, 0.15f, 1.7f));
//	sc.model *= Scale(0.16f);
//	sc.model *= RotateX(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_ornament2->render();
//
//	*/
//
//
//
//
//
//	//******** Mesh_land  */
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.2509f, 0.6823f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.3f, 0.3f, 0.3f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= Translate(vec3(0.0f, 0.0f, 0.0f));
//	sc.model *= Scale(3.3f);
//	sc.model *= RotateY(-BigAnimationTick * 0.3);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_island->render();
//
//	/*
//	//******** Mesh_land  
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3843f, 0.1686f, 0.3804f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.3f, 0.3f, 0.3f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= Translate(vec3(0.0f, -5.5f, 0.0f));
//	sc.model *= Scale(3.0f);
//	sc.model *= RotateY(BigAnimationTick * 0.3);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_land->render();
//	
//	//******** Mesh_land  
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1647f, 0.0666f, 0.1647f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.3f, 0.3f, 0.3f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f); 
//	sc.model *= Translate(vec3(0.0f, -4.0f, 0.0f));
//	sc.model *= Scale(2.7f);
//	sc.model *= RotateY(-BigAnimationTick * 0.3);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.mesh_land->render();
//	*/
//	//glUseProgram(rendering_program1);
//	
//
//	//******** Mesh_teapot_big  
//	/*******Object  
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 2);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 3); //만약 단색으로 하고 싶으면 여기에 넣고 싶은 색상, 위에는 1번
//
//	//******** Mesh_teapot_big  
//	/*
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.125f, 0.184f, 0.259f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f); //라이팅 정도
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f); //이게 퐁을 결정하는 정도
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 20.0f); //퐁의크기 (값이 작을수록 커짐)
//	// Models
//	sc.model = mat4(1.0f);
//	sc.model = mat4(1.0f); sc.model *= Translate(vec3(-0.1f, 0.0f, 0.45f));
//	sc.model *= RotateX(-90.0f);
//	sc.model *= RotateZ(BigteapotAnimationTick*0.3);
//	sc.model *= Scale(0.7f);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	// Draw
//	sc.teapot->render();
//	*/
//	/******** Mesh_teapot  
//
//	glUseProgram(rendering_program1);
//	*/
//	/********Object  */
//	/*
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 1);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 5); //만약 단색으로 하고 싶으면 여기에 넣고 싶은 색상, 위에는 1번
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 0.7f, 0.7f); //색상
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f); //라이팅 정도
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f); //이게 퐁을 결정하는 정도
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 20.0f); //퐁의크기 (값이 작을수록 커짐)
//
//	sc.model = mat4(1.0f);
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-0.5f, 0.0f, 2.7f));
//	sc.model *= RotateX(-90.0f);
//	sc.model *= RotateZ(30.0f);
//	sc.model *= Scale(0.1f);
//	sc.model *= RotateZ(-BigAnimationTick * 0.5);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	sc.teapot_small->render();
//
//
//
//	/******** Mesh_teapot  */
//	/*
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 1);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 6); //만약 단색으로 하고 싶으면 여기에 넣고 싶은 색상, 위에는 1번
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.76f, 0.48f, 0.055f); //색상
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.6f, 0.6f, 0.6f); //라이팅 정도
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.2f, 0.2f, 0.2f); //이게 퐁을 결정하는 정도
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 50.0f); //퐁의크기 (값이 작을수록 커짐)
//	// Models
//	sc.model = mat4(1.0f);
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(-0.2f, 0.0f, 2.7f));
//	sc.model *= RotateX(-90.0f);
//	sc.model *= RotateZ(40.0f);
//	sc.model *= RotateZ(BigAnimationTick*0.3);
//	sc.model *= Scale(0.07f);
//
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	// Draw
//	sc.teapot_small->render();
//
//	/******** Mesh_teapot  */
//	/*
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 1);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 7); //만약 단색으로 하고 싶으면 여기에 넣고 싶은 색상, 위에는 1번
//
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 0.5f, 0.5f); //색상
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.6f, 0.6f, 0.6f); //라이팅 정도
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f); //이게 퐁을 결정하는 정도
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 10.0f); //퐁의크기 (값이 작을수록 커짐)
//	// Models
//	sc.model = mat4(1.0f);
//	sc.model = mat4(1.0f); sc.model *= RotateY(StarAnimationTick2*0.03)*Translate(vec3(0.4f, 0.0f, 2.7f));
//	sc.model *= RotateX(-90.0f);
//	sc.model *= RotateZ(210.0f);
//	sc.model *= Scale(0.12f);
//
//	sc.model *= RotateZ(BigAnimationTick*0.3);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	// Draw
//	sc.teapot_small->render();
//
//	*/
//	
//	
//	/********* Plane */
//	//glUseProgram(rendering_program1);
//
//	/********Object  */
//	//glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 0);
//	//glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 1);
//
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.106f, 0.396f, 0.439f);
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.4f, 0.4f, 0.4f);
//	//glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	//glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//	//glUniform1i(glGetUniformLocation(rendering_program2, "Tex1"), 1);
//
//	//sc.model = mat4(1.0f);
//	//sc.model *= Translate(vec3(0.0f, -0.45f, 0.5f));
//	//sc.model *= Scale(0.8f);
//	//glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	//glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	//sc.plane->render();
//
//
//	/*
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 1.0f, 1.0f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material. Kd"), 0.4f, 0.4f, 0.4f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= Translate(vec3(0.0f, -0.46f, 0.0f));
//	sc.model *= Scale(0.7f);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.plane->render();
//	*/
//
//	/********Teapot  */
//	glUseProgram(rendering_program1);
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 2);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 1); 
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.125f, 0.184f, 0.259f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.9f, 0.9f, 0.9f); //라이팅 정도
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f); //이게 퐁을 결정하는 정도
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 20.0f); //퐁의크기 (값이 작을수록 커짐)
//
//	sc.model = mat4(1.0f);
//	sc.model = mat4(1.0f); sc.model *= Translate(vec3(-0.1f, 1.1f, -4.7f));
//	sc.model *= RotateX(-90.0f);
//	sc.model *= RotateX(StarAnimationTick2*0.25);
//	sc.model *= RotateY(StarAnimationTick2*0.25);
//	sc.model *= RotateZ(BigteapotAnimationTick*0.3);
//	sc.model *= Scale(0.50f);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	sc.teapot->render();
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	glUseProgram(rendering_program1);
//
//	//뒤쪽 벽
//	/********Object  */
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 10);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 10);
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 1.0f, 1.0f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.4f, 0.4f, 0.4f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= Translate(vec3(0.0f, -0.0f, -15.0f));
//	sc.model *= Scale(3.0f);
//	sc.model *= RotateX(90);
//	sc.model *= RotateY(180);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.plane->render();
//
//	//아래쪽 벽
//	/********Object  */
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 10);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 10);
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 1.0f, 1.0f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.4f, 0.4f, 0.4f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= Translate(vec3(0.0f, -10.7f, -0.0f));
//	sc.model *= Scale(3.0f);
//	sc.model *= RotateY(180);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.plane->render();
//
//	//왼쪽 벽
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 10);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 10);
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 1.0f, 1.0f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.4f, 0.4f, 0.4f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= Translate(vec3(-15.0f, 0.0f, -0.0f));
//	sc.model *= Scale(3.0f);
//	sc.model *= RotateZ(-90);
//	sc.model *= RotateY(270);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.plane->render();
//
//	//오른쪽 벽
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 10);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 10);
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 1.0f, 1.0f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.4f, 0.4f, 0.4f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= Translate(vec3(15.0f, 0.0f, -0.0f));
//	sc.model *= Scale(3.0f);
//	sc.model *= RotateZ(90);
//	sc.model *= RotateY(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.plane->render();
//
//	/////////////////////////////////////
//	//눈내리는 것때문에 깔아놓은 벽
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 5);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 1);
//
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 1.0f, 1.0f, 1.0f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.4f, 0.4f, 0.4f);
//	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
//	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
//
//	sc.model = mat4(1.0f);
//	sc.model *= Translate(vec3(0.0f, -1.3f, 0.0f));
//	sc.model *= Scale(0.7f);
//	sc.model *= RotateY(90);
//	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.view*sc.model);
//	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);
//	sc.plane->render();
//
//	glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 5);
//	glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 8);
//	glLoadIdentity();
//	int i, j;
//	float x, y, z;
//	glLoadIdentity();
//	glRotatef(pan, 0.0, 1.0, 0.0);
//	glRotatef(tilt, 1.0, 0.0, 0.0);
//	/*
//	if (fall == RAIN) {
//		glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 5);
//		glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 9);
//		glClearColor(0.1215, 0.0627, 0.1176, 1.0);
//		drawRain();
//	}
//	*/
//	if (fall == SNOW) {
//
//		glUniform1i(glGetUniformLocation(rendering_program1, "BrickTex"), 5);
//		glUniform1i(glGetUniformLocation(rendering_program1, "MossTex"), 8);
//		glClearColor(0.1215, 0.0627, 0.1176, 1.0);
//		drawSnow();
//	}
//
//	glUseProgram(rendering_program3);
//
//	glUniform1f(glGetUniformLocation(rendering_program3, "Time"), t);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glMatrixMode(GL_MODELVIEW);
//	// Disable depth test
//
//	// Enable Blending
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	// Enable Point Size. Enable Point Coord.
//	glEnable(GL_PROGRAM_POINT_SIZE); glPointSize(20.0f);
//	glEnable(GL_POINT_SPRITE);
//	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
//
//	glDrawArrays(GL_POINTS, 0, nParticles);
//
//	glutSwapBuffers();
//}
//
//void shutdown()
//{
//	glDeleteProgram(rendering_program1);
//	glDeleteProgram(rendering_program2);
//	glDeleteProgram(rendering_program3);
//}
//
//void init()
//{
//	sc.camerapos = vec3(1.0, 1.5, 3.0);
//	sc.mousepos = vec3(0.0);
//	sc.projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//	sc.look = LookAt(sc.camerapos, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
//	sc.view = mat4(1.0);
//	sc.width = 512; sc.height = 512;
//
//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0.1215, 0.0627, 0.1176, 1.0);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glShadeModel(GL_SMOOTH);
//
//	int x, z;
//
//	glShadeModel(GL_SMOOTH);
//	glClearDepth(1.0);
//	glEnable(GL_DEPTH_TEST);
//
//	// Ground Verticies
//	  // Ground Colors
//	for (z = 0; z < 21; z++) {
//		for (x = 0; x < 21; x++) {
//			ground_points[x][z][0] = x - 10.0;
//			ground_points[x][z][1] = accum;
//			ground_points[x][z][2] = z - 10.0;
//
//			ground_colors[z][x][0] = r; // red value
//			ground_colors[z][x][1] = g; // green value
//			ground_colors[z][x][2] = b; // blue value
//			ground_colors[z][x][3] = 0.0; // acummulation factor
//		}
//	}
//
//	// Initialize particles
//	for (loop = 0; loop < MAX_PARTICLES; loop++) {
//		initParticles(loop);
//	}
//}
////----------------------------------------------------------------------------
//void idle(void) {
//
//	if (HalfShapeAnimationFlag) {
//		HalfShapeAnimationTick++;
//	}
//	if (HandleAnimationFlag) {
//		BigteapotAnimationTick++;
//	}
//	if (BigAnimationFlag) {
//		BigAnimationTick++;
//	}
//	if (StarAnimationFlag) {
//		StarAnimationTick += 1;
//	}
//	if (StarAnimationFlag2) {
//		StarAnimationTick2 += 1;
//	}
//	if (TreeAnimationFlag) {
//		TreeAnimationTick += 1;
//	}
//
//	if (HalfShapeAnimationFlag || HandleAnimationFlag || BigAnimationFlag || StarAnimationFlag || StarAnimationFlag2 || TreeAnimationFlag) {
//		glutPostRedisplay();
//	}
//
//	t += 0.002f;
//	glutPostRedisplay();
//
//}
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 033: // Escape Key
//	case 'q': case 'Q':
//		exit(EXIT_SUCCESS);
//		break;
//	case 'x':
//		sc.camerapos[0] -= 0.1;
//		break;
//	case 'X':
//		sc.camerapos[0] += 0.1;
//		break;
//	case 'y':
//		sc.camerapos[1] -= 0.1;
//		break;
//	case 'Y':
//		sc.camerapos[1] += 0.1;
//		break;
//	case 'z':
//		sc.camerapos[2] -= 0.1;
//		break;
//	case 'Z':
//		sc.camerapos[2] += 0.1;
//		break;
//	case '1':
//		HalfShapeAnimationFlag = HalfShapeAnimationFlag == false;
//		break;
//	case '2':
//		HandleAnimationFlag = HandleAnimationFlag == false;
//		break;
//	case '3':
//		StarAnimationFlag = StarAnimationFlag == false;
//		break;
//	case '4':
//		BigAnimationFlag = BigAnimationFlag == false;
//		break;
//	case '5':
//		TreeAnimationFlag = TreeAnimationFlag == false;
//		break;
//	case '6':
//		StarAnimationFlag2 = StarAnimationFlag2 == false;
//		break;
//	case '0':
//		HalfShapeAnimationFlag = true;
//		HandleAnimationFlag = true;
//		StarAnimationFlag = true;
//		BigAnimationFlag = true;
//		TreeAnimationFlag = true;
//		break;
//	case '9':
//		HalfShapeAnimationFlag = false;
//		HandleAnimationFlag = false;
//		StarAnimationFlag = false;
//		BigAnimationFlag = false;
//		TreeAnimationFlag = false;
//		break;
//	}
//	if (key == 'r') { // Rain
//		fall = RAIN;
//		glutPostRedisplay();
//	}
//	if (key == 's') { // Snow
//		fall = SNOW;
//		glutPostRedisplay();
//	}
//	if (key == 'q') { // QUIT
//		exit(0);
//	}
//	sc.look = LookAt(sc.camerapos, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }); //얘를 다시 호출해 줘야 한다.
//	glutPostRedisplay();
//}
//
//void motion(int x, int y)
//{
//	vec3 disp, n;
//	float angle, leng;
//
//	disp = sc.mousepos;
//
//	sc.mousepos.x = (float)x / (sc.width / 2) - 1.0;
//	sc.mousepos.y = (float)(sc.height - y) / (sc.height / 2) - 1.0;
//	leng = sc.mousepos.x*sc.mousepos.x + sc.mousepos.y*sc.mousepos.y;
//	if (leng > 0.98)
//		sc.mousepos.z = sqrtf(1.0 - 0.98);
//	else
//		sc.mousepos.z = sqrt(1.0 - leng);
//
//	n = cross(disp, sc.mousepos);
//	leng = length(n);
//	angle = degrees(length(n));
//
//	disp = sc.mousepos - disp;
//
//	switch (sc.uimode) {
//	case 0:
//		disp *= 0.2;
//		sc.view = Translate(disp.x, disp.y, 0.0)*sc.view;
//		break;
//	case 1:
//		sc.view = Scale(0.2*disp.y + 1.0)*sc.view;
//		break;
//	case 2:
//		if (angle != 0)
//			sc.view = Rotate(angle, n)*sc.view;
//
//		break;
//	}
//	glutPostRedisplay();
//}
////----------------------------------------------------------------------------
//void mouse(int button, int state, int x, int y)
//{
//	float u, v, theta, angle, s, leng;
//	vec3 n;
//
//	u = (float)x / (sc.width / 2) - 1.0;
//	v = (float)(sc.height - y) / (sc.height / 2) - 1.0;
//
//	if (state == GLUT_DOWN) {
//		sc.mousepos.x = u;
//		sc.mousepos.y = v;
//		leng = length(vec2(sc.mousepos.x, sc.mousepos.y));
//		if (leng > 0.98)
//			sc.mousepos.z = sqrtf(1.0 - 0.98);
//		else
//			sc.mousepos.z = sqrt(1.0 - leng);
//
//		switch (button) {
//		case GLUT_LEFT_BUTTON:
//			sc.uimode = 0; break;
//		case GLUT_MIDDLE_BUTTON:
//			sc.uimode = 1; break;
//		case GLUT_RIGHT_BUTTON:
//			sc.uimode = 2; break;
//		}
//	}
//	glutPostRedisplay();
//}
//
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//
//	GLfloat left = -2.5, right = 2.5, bottom = -2.0, top = 3.6;
//	GLfloat aspect = (GLfloat)w / h;
//
//	if (aspect <= 1.0) {
//		bottom /= aspect;
//		top /= aspect;
//	}
//	else {
//		left *= aspect;
//		right *= aspect;
//	}
//
//	sc.projection = Ortho(left, right, bottom, top, -36.0, 36.0);
//	sc.width = w; sc.height = h;
//}
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//	glutInitWindowSize(sc.width, sc.height);
//	glutCreateWindow("Multi-Light Pig");
//	glewInit();
//
//	version();
//	startup();
//	init();
//	glutIdleFunc(idle);
//	glutDisplayFunc(render);
//
//	glutMouseFunc(mouse);
//
//	glutKeyboardFunc(keyboard);
//	glutMotionFunc(motion);
//	glutReshapeFunc(reshape);
//	glutMainLoop();
//	shutdown();
//
//	system("pause");
//}
