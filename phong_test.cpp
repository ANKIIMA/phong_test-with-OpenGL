#include<GL/glut.h>
#include<iostream>
using namespace std;
GLfloat theta = 0.0f;

void init()
{
	GLfloat lightPos[] = { -50.0f,-50.0f,100.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat specular[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//坐标轴
	{
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(12.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 12.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 12.0);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	GLfloat lightPos[] = { 0.0,0.0,100.0f,1.0f };
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(theta, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutSolidSphere(6.0, 300, 60);

	glutSwapBuffers();
}

void myIdle()
{
	theta += 2.0f;
	if (theta == 360.0f)
		theta = 0.0f;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TEST");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(myIdle);

	glutMainLoop();
}