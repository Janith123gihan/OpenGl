#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

int sh = 600, sw = 1000;

typedef struct {
	float x;
	float y;
}Point2D;

int score;

Point2D tc, lc; //Center of the Tray and the Lid

int tang, tzoom; //Tray's angle, and scale factor
int lang, lzoom; //Lid's angle, and scale factor

Point2D translate(Point2D p, float tx, float ty) {
	Point2D ptemp;
	ptemp.x = p.x + tx; //.....write the equations for translation 
	ptemp.y = p.y + ty; //.....write the equations for translation
	return ptemp;
}

Point2D rotate_arb(Point2D p, Point2D piv, float ang) {
	Point2D ptemp;
	ang = ang * 3.14 / 180.0;

	double ac = cos(ang);
	double as = sin(ang);

	ptemp.x = (p.x * ac) - (p.y * as) - (piv.x * ac) + (piv.y * as) + piv.x;//Calculate the point here
	ptemp.y = (p.x * as) + (p.y * ac) - (piv.x * as) - (piv.y * ac) + piv.y;//Calculate the point here

	return ptemp;
}

Point2D scale_arb(Point2D p, Point2D piv, int sf) { // sf - scale factor
	Point2D ptemp;

	ptemp.x = (p.x * sf) + piv.x - (sf * piv.x);//Calculate the point here
	ptemp.y = (p.y * sf) + piv.y - (sf * piv.y);//Calculate the point here

	return ptemp;
}

void relocateTray() { // set a random position of the tray
	Point2D rv; //Random value
	int zv;
	int rr;

	int minX = 100, maxX = sw-100, intervalX = 100, rangeX = maxX - minX + 1;
	int minY = 100, maxY = sh - 100, intervalY = 100, rangeY = maxY - minY + 1;

		//Random numbers multiples of <interval> between <min> and <max>
	rv.x = minX + (rand() % rangeX) / intervalX * intervalX;
	rv.y = minY + (rand() % rangeY) / intervalY * intervalY;

	tc.x = rv.x;  tc.y = rv.y; // set random location (tc.x , tc.y) of the tray 

	//defining min and max for zoom
	int minZ = 1, maxZ = 5, intervalZ = 1, rangeZ = maxZ - minZ + 1;
	zv = minZ + (rand() % rangeZ) / intervalZ * intervalZ;


	//defining min and max for rotate
	int minR = 0, maxR = 90, intervalR = 10, rangeR = maxR - minR + 1;
	rr = minR + (rand() % rangeR) / intervalR * intervalR;


	tzoom = zv; // set random scale factor of the tray; 
	tang = rr;  // set random rotation angle of the tray;
}

void checkPos() { //check whether the tray and lid are overlapping
	if (((tc.x == lc.x) && (tc.y == lc.y))&&(tzoom == lzoom )&& ((tang == lang)|| (tang == (90+lang)))){
		score += 10;
		relocateTray();
	}
}

void drawSquare(Point2D center, int ang, int zoom) {
	Point2D p1, p2, p3, p4;

	p1.x = center.x - 10; 	p1.y = center.y - 10;
	p2.x = center.x - 10; 	p2.y = center.y + 10;
	p3.x = center.x + 10; 	p3.y = center.y + 10;
	p4.x = center.x + 10; 	p4.y = center.y - 10;

	//Scale the points p1, p2, p3, and p4;
	p1 = scale_arb(p1, center, zoom);
	p2 = scale_arb(p2, center, zoom);
	p3 = scale_arb(p3, center, zoom);
	p4 = scale_arb(p4, center, zoom);

	//Rotate the points p1, p2, p3, and p4;
	p1 = rotate_arb(p1, center, ang);
	p2 = rotate_arb(p2, center, ang);
	p3 = rotate_arb(p3, center, ang);
	p4 = rotate_arb(p4, center, ang);

	glBegin(GL_POLYGON);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glVertex2i(p3.x, p3.y);
	glVertex2i(p4.x, p4.y);
	glEnd();
}

void drawGrid() { // You don't need to modify anything in this function
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);

	for (int x = 100; x < sw; x += 100) {
		glVertex2i(x, 0);
		glVertex2i(x, sh);
	}

	for (int y = 100; y < sw; y += 100) {
		glVertex2i(0, y);
		glVertex2i(sw, y);
	}

	glEnd();
}

void printScore() // You don't need to modify anything in this function
{
	string str = "Score = " + to_string((long long)score);

	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2f(10, 10);

	int len, i;
	len = str.length();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void drawTray() {
	glColor3f(1.0, 0.0, 0.0);
	drawSquare(tc, tang, tzoom);
}

void drawLid() {
	glColor3f(1.0, 1.0, 0.0);
	drawSquare(lc, lang, lzoom);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawGrid();
	printScore();
	drawTray();
	drawLid();
	
	glFlush();
}

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if(lc.x >100){
			lc = translate(lc,-10,0);
			lang = (lang + 10) % 90;
		}
		break;
	case GLUT_KEY_RIGHT:
		if(lc.x<900){
			lc = translate(lc, 10, 0);
			lang = (lang - 10) % 90;
		}
		break;
	case GLUT_KEY_UP:
		if(lc.y<500){
			lc = translate(lc, 0, 10);
			lang = (lang - 10) % 90;
		}
		break;
	case GLUT_KEY_DOWN:
		if(lc.y>100){
			lc = translate(lc, 0, -10);
			lang = (lang + 10) % 90;
		}
		break;
	default: return;
	}
	checkPos(); // check whether the squares are overlapping
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		lzoom = lzoom + 1;
		break;
	case '-':
		lzoom = lzoom - 1;
		break;
	case 'R':
		lang = (lang + 10) % 90;
		break;
	case 'r':
		lang = (lang - 10) % 90;
		break;
	case 'q':
		exit(EXIT_SUCCESS);
	case 'Q':
		exit(EXIT_SUCCESS);
	default: return;
	}
	checkPos();
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
}

void testFunction() {
	int rv; //Random value
	int min = 100, max = 900, interval = 100, range = max - min + 1;

	printf("start \n"); // '\n' is used for new line
	for (int i = 1; i <= 50; i++) {

		//Random numbers multiples of <interval> between <min> and <max>
		rv = min + (rand() % range) / interval * interval;

		printf("(%d) rv is %d \t\t\t\t", i, rv); // '\t' adds a tab chracter
	}
	printf("end \n"); // '\n' is used for new line
}

void myinit() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, sw, 0, sh);
	glViewport(0, 0, sw, sh);
	srand(time(0));
	glPointSize(1.0);

	score = 0;

	// Place the Tray
	relocateTray();

	// Place the Lid
	lc.x = 100;	lc.y = 100; //Lid's Center
	lang = 0; lzoom = 1;   //Lid's angle, and scale factor

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(sw, sh);
	glutCreateWindow("Tray & Lid Game");

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display);

	myinit();

	testFunction();

	glutMainLoop();
	return(0);
}