#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath> 

int WinWidth = 500, WinHeight = 500;

typedef struct { float x; float y; }Point2D;
typedef struct { float x; float y; float z; }Point3D;

double zoomup = 1.1;
double zoomdown = 0.9;

Point3D A, B, C, D, E, F, G, H;	// Vertices of the cube

void InitCube() {
	A.x = -100; A.y = -100; A.z = 100;
	B.x = 100; B.y = -100; B.z = 100;
	C.x = 100; C.y = 100; C.z = 100;
	D.x = -100; D.y = 100; D.z = 100;

	E.x = -100; E.y = -100; E.z = -100;
	F.x = 100; F.y = -100; F.z = -100;
	G.x = 100; G.y = 100; G.z = -100;
	H.x = -100; H.y = 100; H.z = -100;
}

Point2D Project_OrthoXY(Point3D p) {  // Orthographic parallel projection on 
	Point2D p2;
	p2.x = p.x;
	p2.y = p.y;
	return p2;
}


Point3D translate3D(Point3D p, float tx, float ty, float tz) {
	Point3D tp3;
	//.....wite the equations for 3D translation
	tp3.x = p.x + tx;
	tp3.y = p.y + ty;
	tp3.z = p.z + tz;

	return tp3;
}
void translate_x(float tx) {
	A = translate3D(A, tx, 0, 0);
	B = translate3D(B, tx, 0, 0);
	C = translate3D(C, tx, 0, 0);
	D = translate3D(D, tx, 0, 0);

	E = translate3D(E, tx, 0, 0);
	F = translate3D(F, tx, 0, 0);
	G = translate3D(G, tx, 0, 0);
	H = translate3D(H, tx, 0, 0);

	glutPostRedisplay();
}
void translate_y(float ty) {
	A = translate3D(A, 0, ty, 0);
	B = translate3D(B, 0, ty, 0);
	C = translate3D(C, 0, ty, 0);
	D = translate3D(D, 0, ty, 0);

	E = translate3D(E, 0, ty, 0);
	F = translate3D(F, 0, ty, 0);
	G = translate3D(G, 0, ty, 0);
	H = translate3D(H, 0, ty, 0);

	glutPostRedisplay();
}

Point3D rotate_y(Point3D p, Point3D piv, float ang) {
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;

	double ca = cos(ang);
	double sa = sin(ang);

	pr.x = p.x * ca + p.z * sa - piv.x * ca - piv.z * sa + piv.x;
	pr.z = p.z * ca + piv.x * sa - p.x * sa - piv.z * ca + piv.z;
	pr.y = p.y;

	return pr;
}

Point3D rotate_x(Point3D p, Point3D piv, float ang) {
	ang = ang * 3.14159265359 / 180.0;					//angle in radians 
	Point3D pr;

	double ca = cos(ang);
	double sa = sin(ang);
	pr.y = p.y * ca + piv.z * sa - p.z * sa - piv.y * ca + piv.y;
	pr.z = p.y * sa + p.z * ca - piv.z * ca - piv.y * sa + piv.z;
	pr.x = p.x;

	return pr;
}
Point3D scale(Point3D p, Point3D piv, float zoom) {

	Point3D pr;

	pr.x = zoom * p.x + piv.x - piv.x * zoom;
	pr.y = piv.y - zoom * piv.y + zoom * p.y;
	pr.z = piv.z - zoom * piv.z + zoom * p.z;

	return pr;
}
void rotatebox_y(float ang) {

	Point3D mid;
	mid.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x) / 8;
	mid.y = (A.y + B.y + C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	mid.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;

	A = rotate_y(A, mid, ang);
	B = rotate_y(B, mid, ang);
	C = rotate_y(C, mid, ang);
	D = rotate_y(D, mid, ang);
	E = rotate_y(E, mid, ang);
	F = rotate_y(F, mid, ang);
	G = rotate_y(G, mid, ang);
	H = rotate_y(H, mid, ang);


	glutPostRedisplay();
}

void rotatebox_x(float ang) {

	Point3D mid;
	mid.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x) / 8;
	mid.y = (A.y + B.y + C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	mid.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;

	A = rotate_x(A, mid, ang);
	B = rotate_x(B, mid, ang);
	C = rotate_x(C, mid, ang);
	D = rotate_x(D, mid, ang);
	E = rotate_x(E, mid, ang);
	F = rotate_x(F, mid, ang);
	G = rotate_x(G, mid, ang);
	H = rotate_x(H, mid, ang);


	glutPostRedisplay();
}
void scaleBox(float zoom) {

	Point3D mid;
	mid.x = (A.x + B.x + C.x + D.x + E.x + F.x + G.x + H.x) / 8;
	mid.y = (A.y + B.y + C.y + D.y + E.y + F.y + G.y + H.y) / 8;
	mid.z = (A.z + B.z + C.z + D.z + E.z + F.z + G.z + H.z) / 8;

	A = scale(A, mid, zoom);
	B = scale(B, mid, zoom);
	C = scale(C, mid, zoom);
	D = scale(D, mid, zoom);

	E = scale(E, mid, zoom);
	F = scale(F, mid, zoom);
	G = scale(G, mid, zoom);
	H = scale(H, mid, zoom);

	glutPostRedisplay();
}

void DrawCube() {
	Point2D Ap, Bp, Cp, Dp, Ep, Fp, Gp, Hp;

	Ap = Project_OrthoXY(A);
	Bp = Project_OrthoXY(B);
	Cp = Project_OrthoXY(C);
	Dp = Project_OrthoXY(D);
	Ep = Project_OrthoXY(E);
	Fp = Project_OrthoXY(F);
	Gp = Project_OrthoXY(G);
	Hp = Project_OrthoXY(H);

	//DRAWING BACK FACE
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(Ep.x, Ep.y); glVertex2i(Fp.x, Fp.y);	glVertex2i(Gp.x, Gp.y); glVertex2i(Hp.x, Hp.y);
	glEnd();

	//DRAWING FRONT FACE
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(Ap.x, Ap.y); glVertex2i(Bp.x, Bp.y);	glVertex2i(Cp.x, Cp.y); glVertex2i(Dp.x, Dp.y);
	glEnd();

	//DRAWING OTHER LINES
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(Ap.x, Ap.y); glVertex2i(Ep.x, Ep.y);

	glVertex2i(Bp.x, Bp.y); glVertex2i(Fp.x, Fp.y);

	glVertex2i(Cp.x, Cp.y); glVertex2i(Gp.x, Gp.y);

	glVertex2i(Dp.x, Dp.y); glVertex2i(Hp.x, Hp.y);
	glEnd();

}

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: translate_x(-5); break;
	case GLUT_KEY_RIGHT: translate_x(5); break;
	case GLUT_KEY_UP: translate_y(5); break;
	case GLUT_KEY_DOWN: translate_y(-5); break;
	default: return;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		scaleBox(zoomup);
		break;
	case '-':
		scaleBox(zoomdown);
		break;
	case 'R':

		break;
	case 'w':
		rotatebox_x(5);
		break;
	case 'W':
		rotatebox_x(5);
		break;
	case 's':
		rotatebox_x(-5);
		break;
	case 'S':
		rotatebox_x(-5);
		break;
	case 'a':
		rotatebox_y(-5);
		break;
	case 'A':
		rotatebox_y(-5);
		break;
	case 'd':
		rotatebox_y(5);
		break;
	case 'D':
		rotatebox_y(5);
		break;
	case 'q':
		exit(EXIT_SUCCESS);
	case 'Q':
		exit(EXIT_SUCCESS);
	default: return;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{

		}
		else if (button == GLUT_RIGHT_BUTTON)
		{

		}
	}
}

void myDisplay()
{
	glLineWidth(2.0);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawCube();

	glFlush();
}

void myInit() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WinWidth, WinHeight);
	glutCreateWindow("Projection of a Cube");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WinWidth / 2, WinWidth / 2, -WinWidth / 2, WinWidth / 2);
	glViewport(0, 0, WinWidth, WinHeight);

	myInit();
	InitCube();

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutMainLoop();

	return(0);
}
