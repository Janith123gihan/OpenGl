#include <windows.h>
#include <GL/glut.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);

	GLfloat m = (y2 - y1) / (float)(x2 - x1);
	GLfloat c = y1 - m * x1;

	glBegin(GL_POINTS);

	
	GLfloat y;
	GLfloat x;

	if (x1 < x2 && y1 < y2) {

		if (0 < m && m < 1) {
			for (GLint x = x1; x <= x2; x++) {
				y = m * x + c;
				glVertex2f(x, y);
			}
		}
		else {
			for (GLint y = y1; y <= y2; y++) {
				x = (y - c) / m;
				glVertex2f(x, y);
			}
		}
	}
	else if (x1 > x2 && y1 < y2) {

		if (0 > m && m > -1) {
			for (GLint x = x1; x >= x2; x--) {
				y = m * x + c;
				glVertex2f(x, y);
			}
		}
		else {
			for (GLint y = y1; y <= y2; y++) {
				x = (y - c) / m;
				glVertex2f(x, y);
			}
		}
	}
	else if (x1 > x2 && y1 > y2) {

		if (0 < m && m < 1) {
			for (GLint x = x1; x >= x2; x--) {
				y = m * x + c;
				glVertex2f(x, y);
			}
		}
		else {
			for (GLint y = y1; y >= y2; y--) {
				x = (y - c) / m;
				glVertex2f(x, y);
			}
		}
	}
	else if (x1 < x2 && y1 > y2) {

		if (0 > m && m > -1) {
			for (GLint x = x1; x <= x2; x++) {
				y = m * x + c;
				glVertex2f(x, y);
			}
		}
		else {
			for (GLint y = y1; y >= y2; y--) {
				x = (y - c) / m;
				glVertex2f(x, y);
			}
		}
	}
	
	glEnd();

}

void display()
{
	drawLine(xi, yi, xf, yf);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
		}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		exit(0);
	if (key == 'e' || key == 'E')
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();
	}
}

void myinit()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Lines");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	myinit();
	glutMainLoop();

	return 0;
}