#include <windows.h>
#include <GL/glut.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf, xs, ys, xl, yl;

GLint butn = 0;
GLint stte = 1;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);

	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
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

			if (butn == 0) {
				xi = x;
				yi = (wh - y);
				butn = 1;
				xl = xi;
				yl = yi;

				if (stte == 1) {
					xf = xi;
					yf = yi;

					xs = xi;
					ys = yi;

					butn = 1;
					stte = 0;
				}

			}

			else {
				xf = x;
				yf = (wh - y);

				xl = xf;
				yl = yf;
				butn = 0;
			}


		}
	if (btn == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN)
		{

			xi = xs;
			yi = ys;
			xf = xl;
			yf = yl;

			stte = 1;
			butn = 0;


		}

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
	glutCreateWindow("Polygon");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	myinit();
	glutMainLoop();

	return 0;
}