#include "HelloGL.h"
#include "GLUTCallbacks.h"

HelloGL::HelloGL(int argc, char* argv[]) {
	rotation = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // double buffering
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100); // aspect ratio (max point onaxis is now 100 x and y not 1)
	glutCreateWindow("simple openGL program");
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000); //field of view, aspect ratio, near clipping distance, far clipping distance
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop(); //put nothing after this
}

void HelloGL::Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	DrawPolygon1();
	
	glFlush();
	glutSwapBuffers(); // double buffering
}

void HelloGL::DrawPolygon1() {
	glPushMatrix();
	glRotatef(rotation, 1.0f, 1.0f, 1.0f);

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	glVertex2f(-0.75f, 0.5f);
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	glVertex2f(-0.2f, 0.5f);
	glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
	glVertex2f(-0.1f, -0.5f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(-0.75, -0.5f);
	glEnd();
	glPopMatrix();
}



//
//	glBegin(GL_POLYGON);
//	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
//	glVertex2f(-0.5f, 0.5f);
//	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
//	glVertex2f(0.5f, 0.5f);
//	glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
//	glVertex2f(0.5f, -0.5f);
//	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
//	glVertex2f(-0.5f, -0.5f);
//	glEnd();
//	glPopMatrix();
//}




HelloGL::~HelloGL(void) {

}

void HelloGL::Update() {
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	rotation += 0.5f;
	//Sleep(10);
	if (rotation >= 360.0f)
		rotation = 0.0f;

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y) {
	if (key == 'd')
		rotation += 0.5f;
}

