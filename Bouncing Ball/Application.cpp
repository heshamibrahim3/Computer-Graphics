#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>	
#include <compgraphmath2020.h>
#define _USE_MATH_DEFINES 
#include <math.h>



using namespace std;
GLsizei winWidth = 700, winHeight = 700;
GLint line;
GLint Xin = 1;
GLint Yin = 1;
GLdouble d = 50;
vec2 o = { 50 , 50 };
GLboolean colorBounce = true;
int end1;
float middle = 350;



void init()
{
	glClearColor(1.0, 1.0, 0.0, 0.0);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_FLAT);
	glLoadIdentity();

}




void circle(vec2 o, GLdouble d) {
	if (!colorBounce) {
		glBegin(GL_POLYGON);
		for (GLdouble t = 0; t < 2 * pi(); t += 0.01)
			glVertex2d(o.x + d * cos(t), o.y + d * sin(t));
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		for (GLdouble t = 0; t < 2 * pi(); t += 0.01)
			glVertex2d(o.x + d * cos(t), o.y + d * sin(t));
		glEnd();
	}
}




void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);

	glVertex2i(263, middle);
	glVertex2i(438, middle);
	glutPostRedisplay();
	glutSwapBuffers();
	glEnd();



	if ((o.x > 263 - 50 && o.x < 438 + 50) && (o.y < middle + 50 && o.y > middle - 50)) {
		glColor3f(1.0, 0.0, 0.0);
	}
	else {
		glColor3f(0.0, 1.0, 0.0);
	}

	circle(o, d);
	glFlush();

}



void specialkey(int key, int x, int y) {

	if (key == 101 && middle <= 690) {
		middle = middle + 4;
		glutPostRedisplay();
	}
	else if (key == 103 && middle >= 10) {
		middle = middle - 4;
		glutPostRedisplay();
	}
}


void update(int n)
{
	o.x += Xin;
	o.y += Yin;
	if (o.x + d > 700 || o.x - d < 0) {
		Xin *= -1;
		colorBounce = true;
	}
	if (o.y + d > 700 || o.y - d < 0) {
		Yin *= -1;
		colorBounce = false;
	}

	glutPostRedisplay();
	glutTimerFunc(2, update, 0);
	line = (1) * o.y;
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Problem 1");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(2, update, 0);
	glutSpecialFunc(specialkey);
	glutMainLoop();

	return 0;
}