
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <math.h>
using namespace std;
struct Point2D
{
	float x, y;
};
Point2D list[3];
bool color = true;
float pointsize = 3.0;
void mouse(int button, int state,int x, int y){
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN){
			if(color)
				glColor3f(1.0,0.0,0.0);
			else
				glColor3f(1.0,1.0,1.0);
			glPointSize(pointsize);
			glBegin(GL_POINTS);
			glVertex2d(x,y);
			glEnd();
			glFlush();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN)
			color = !color;
	default:
		break;
	}
}
void moveMouse(int x, int y)
{
	glPointSize(pointsize);
			glBegin(GL_POINTS);
			glVertex2d(x,y);
			glEnd();
			glFlush();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
} 
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 720, 0);
}
int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("My window");
	glutDisplayFunc(display);
	init();
	glutMouseFunc(mouse);
	glutMotionFunc(moveMouse);
	glutMainLoop();
	return 0;
}