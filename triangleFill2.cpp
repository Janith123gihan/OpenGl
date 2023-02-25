#include <gl/glut.h>
#include <Windows.h>

void Triangle() {
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	
	glBegin(GL_LINES);
	glVertex2i(100, 100);
	glVertex2i(300, 400);

	glVertex2i(300, 400);
	glVertex2i(450, 100);

	glVertex2i(450, 100);
	glVertex2i(100, 100);

	glEnd();

	float m1 = 1.5; 
	float end1 = ((400 - 100) / m1) + 100; 
	float c1 = 100 - (m1 * 100);
	
	glBegin(GL_LINES);
	for (float i = 100; i <= 400; i++) {
		glVertex2f((i - c1) / m1, i);
		glVertex2f(end1, i);
	}

	float m2 = -2; 
	float c2 = 100 - (m2 * 450);
	
	glBegin(GL_LINES);
		for (float i = 100; i <= 400; i++) {
			glVertex2f(end1, i);
			glVertex2f((i - c2) / m2, i);

		}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Triangle");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 500, 500);

	glutDisplayFunc(Triangle);
	glutMainLoop();
	return 0;
}