#include <windows.h>
#include <GL/glut.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);

	glBegin(GL_POINTS);

	GLint dx = x2 - x1;
	GLint dy = y2 - y1;
	GLint steps;
	GLint k;

	GLfloat xincrement;
	GLfloat yincrement;
	GLfloat x = x1;
	GLfloat y = y1;

	if (abs(dx) > abs(dy))
		steps = abs(dx);

	else 
		steps = abs(dy);
	xincrement = float(dx) / steps;
	yincrement = float(dy) / steps;
	glVertex2f(x, y);
		for (k = 0; k < steps; k++) {
			x += xincrement;
			y += yincrement;
			glVertex2f(x, y);
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