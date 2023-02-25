#include <gl/glut.h>
#include <Windows.h>


void fill() {
	glColor3f(1.0, 0.0, 1.0);
	glPointSize(2.0);

	GLfloat r = 100;
	GLfloat x = 0, y = r;
	GLfloat p = 1 - r;

	x = 0; y = r; p = 1 - r;
	glBegin(GL_LINES);
	while (x != y)
	{
		x++;
		if (p <= 0) {
			p = p + (2 * x) + 3;
		}
		else {

			p = p + 2 * (x - y) + 5;
			y--;
		}

		glVertex2f(0, y); glVertex2f(x, y);
		glVertex2f(0, y); glVertex2f(-x, y);

		glVertex2f(0, -y); glVertex2f(x, -y);
		glVertex2f(0, -y); glVertex2f(-x, -y);

		glVertex2f(0, x); glVertex2f(y, x);
		glVertex2f(0, x); glVertex2f(-y, x);

		glVertex2f(0, -x); glVertex2f(y, -x);
		glVertex2f(0, -x); glVertex2f(-y, -x);


		glVertex2f(0, 0); glVertex2f(-r, 0);
		glVertex2f(0, 0); glVertex2f(r, 0);
	}
	glEnd();

	glFlush();
}
void circle() {
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);

	GLfloat r = 100;
	GLfloat x = 0, y = r;
	GLfloat p = 1 - r;


	glBegin(GL_POINTS);
	while (x != y)
	{
		x++;
		if (p < 0) {
			p = p + (2 * x) + 3;
		}
		else {
			y--;
			p = p + 2 * (x - y) + 5;
		}

		glVertex2i(x, y);
		glVertex2i(-x, y);

		glVertex2i(x, -y);
		glVertex2i(-x, -y);

		glVertex2i(y, x);
		glVertex2i(-y, x);

		glVertex2i(y, -x);
		glVertex2i(-y, -x);


	}
	glEnd();



	glFlush();
	fill();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Fill Circle");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-250, 250, -250, 250);
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 500, 500);

	glutDisplayFunc(circle);
	glutMainLoop();
	return 0;
}