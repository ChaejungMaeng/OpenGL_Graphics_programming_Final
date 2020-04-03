#include "diging.h"
#include "vbocube.h"
#include "vboplane.h"
#include "time.h"
#include <algorithm>

void startup();
void render();
void shutdown();
extern void version();
extern GLuint compile_shaders(const char*  vsource, const char*  fsource);

struct scene {
	int width = 800, height = 600;

	// modeling 변수
	VBOCube *cube;
	VBOPlane *plane;

	// view  변수
	mat4 mv;
	mat4 projection;

	//  vao 변수
	GLuint rendering_program;
	GLuint vertex_array_object;
	GLint mv_location;
	GLint proj_location;
	GLint color_loc;
};
scene sc;
#define BASE_HEIGHT 0.5
#define LOWER_HEIGHT 1.0
#define UPPER_HEIGHT 1.0


void startup()
{
	/******* OpenGL Initialization */
	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL); //Passes if the incoming depth value is less than or
	/**** Shaders as variables */
	sc.rendering_program = compile_shaders("robotarm_v.glsl", "robotarm_f.glsl");
	glUseProgram(sc.rendering_program);

	// modeling
	sc.cube = new VBOCube();
	sc.plane = new VBOPlane(10.0f, 10.0f, 1, 1);
	sc.color_loc = glGetUniformLocation(sc.rendering_program, "color");

	// viewing
	sc.mv = LookAt(vec3(5.0f, 5.0f, 7.5f), vec3(0.0f, 0.75f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	float cameraZ = sc.height * 0.5 / tan(radians(0.5*50.0));
	sc.projection = Perspective(50.0f, sc.width/sc.height, 0.001*cameraZ, 10.0*cameraZ);

	sc.mv_location = glGetUniformLocation(sc.rendering_program, "mv_matrix");
	sc.proj_location = glGetUniformLocation(sc.rendering_program, "proj_matrix");
	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.mv);
	glUniformMatrix4fv(sc.proj_location, 1, GL_TRUE, sc.projection);

	glUseProgram(sc.rendering_program);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

	glUseProgram(sc.rendering_program);

	// floor
	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, sc.mv);
	glUniform3f(sc.color_loc, 0.3, 0.3, 0.3);
	sc.plane->render();

	mat4 mv_base, mv_lower, mv_upper;

	/******** base *******/
	// instance	
	mv_base = sc.mv * Translate(0.0, 0.5*BASE_HEIGHT, 0.0)*Scale(1.0, BASE_HEIGHT, 1.0);
	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, mv_base);
	glUniform3f(sc.color_loc, 0.3, 0.2, 0.9);
	sc.cube->render();

	/********* Lower Arm *****/
	mv_lower = sc.mv * Translate(0.0f, BASE_HEIGHT, 0.0f); //이게 기본 변환 행렬
	// instance
	mv_lower = mv_lower * Translate(0.0, 0.5*LOWER_HEIGHT, 0.0)*Scale(0.2, LOWER_HEIGHT, 0.2);
	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, mv_lower);
	glUniform3f(sc.color_loc, 0.9, 0.2, 0.2);
	sc.cube->render();

	/********* Upper Arm */
	mv_upper = sc.mv * Translate(0.0f, BASE_HEIGHT, 0.0f) * Translate(0.0f, LOWER_HEIGHT, 0.0f); //기존꺼를 미리 설정하고 (두번째에 있던 큐브)
	// instance - upper arm
	mv_upper = mv_upper * Translate(0.0, 0.5*UPPER_HEIGHT, 0.0)*Scale(0.2, UPPER_HEIGHT, 0.2); //여기에 추가한 변환
	glUniformMatrix4fv(sc.mv_location, 1, GL_TRUE, mv_upper);
	glUniform3f(sc.color_loc, 0.1, 0.9, 0.3);
	sc.cube->render();

	glutSwapBuffers();
}

void shutdown()
{
	glDeleteProgram(sc.rendering_program);
}

void idle() {
	
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	float add, minus;
	int frame;
	int i;

	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(sc.width , sc.height);
	glutCreateWindow("Robot Arm");
	glewInit();

	version();
	startup();
	glutDisplayFunc(render);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();
	shutdown();
	return 0;
}

//model에서 소스파일의 이름과 동일한 헤더파일 추가
//scene함수에서 VBOsphere 같은 거 추가
//startup에서 sc.sphere = new VBOSphere~ 선언
//render에서 sc.shpere->render();
//render에서 glUniforMaatrix4fv(sc.mv_location, 1, 