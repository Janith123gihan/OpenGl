#include <windows.h>
#include <GL/glut.h>
#include <math.h>

GLint xc = 100, yc = 100, r = 100;

void draw(GLint cx, GLint cy)
{
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}

void plotpixels(GLint h, GLint k, GLint x, GLint y)
{
	draw(x + h, y + k);
	draw(-x + h, y + k);
	draw(x + h, -y + k);
	draw(-x + h, -y + k);
	draw(y + h, x + k);
	draw(-y + h, x + k);
	draw(y + h, -x + k);
	draw(-y + h, -x + k);
}



void circle_draw(GLint xc, GLint yc, GLint r)
{
	GLint d = 1 - r, x = 0, y = r;
	while (y > x)
	{
		plotpixels(xc, yc, x, y);
		if (d < 0) d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
	plotpixels(xc, yc, x, y);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);
	circle_draw(xc, yc, r);
	glFlush();
}


void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);				
	glMatrixMode(GL_PROJECTION);					
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);							
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	
	glutInitWindowPosition(0, 0);					
	glutInitWindowSize(500, 500);					
	glutCreateWindow("Mid Point Circle");			
	init();											
	glutDisplayFunc(display);						
	glutMainLoop();									
	return 0;
}