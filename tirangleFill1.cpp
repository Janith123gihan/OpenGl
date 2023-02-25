#include <gl/glut.h>
#include <Windows.h>

void Triangle() {
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);

	glBegin(GL_LINES);

	glVertex2i(100, 100);
	glVertex2i(400, 400);

	glVertex2i(400, 400);
	glVertex2i(400, 100);

	glVertex2i(400, 100);
	glVertex2i(100, 100);

	glEnd();

	GLint m = 1; 

	GLint c = 0; 
	glBegin(GL_LINES);
	for (int i = 100; i <= 400; i++) {
		glVertex2i(i, i);
		glVertex2i(400, i);
	}

	glEnd();

	glFlush();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Triangle Filling");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 500, 500);

	glutDisplayFunc(Triangle);
	glutMainLoop();
	return 0;
}