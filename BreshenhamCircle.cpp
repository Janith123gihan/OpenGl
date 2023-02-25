#include <windows.h>
#include <GL/glut.h>

int ww = 600, wh = 400;


void drawCircle(GLint r)
{
	glPointSize(2.0);

	glBegin(GL_POINTS);

	GLint x = r;
	GLint y = 0;
	GLint d = 3 - 2 * r;

	while (y <= x) {
		glVertex2f(300 + x, 200 + y);
		glVertex2f(300 + x, 200 - y);
		glVertex2f(300 - x, 200 + y);
		glVertex2f(300 - x, 200 - y);
		glVertex2f(300 + y, 200 + x);
		glVertex2f(300 + y, 200 - x);
		glVertex2f(300 - y, 200 + x);
		glVertex2f(300 - y, 200 - x);
		if (d < 0)
			d = d + 4 * y + 6;
		else {
			d = d + 4 * (y - x) + 10;
			x--;
		}
		y++;
	}
	glEnd();

}

void display()
{
	drawCircle(100);
	glFlush();
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
	glutInitWindowPosition(0, 0);


	

	glutCreateWindow("circle");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	myinit();
	glutMainLoop();

	return 0;
}