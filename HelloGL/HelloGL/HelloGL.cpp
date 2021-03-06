#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Planet.h"
#include "MeshLoader.h"
#include "Constants.h"

HelloGL::HelloGL(int argc, char* argv[]) {
	
	InitGL(argc, argv); //glut or GL
	InitObjects(); //creating objects
	InitLighting();
	planet_slower = 0;
	m_delete = false;
	deleted_once = false;
	glutMainLoop(); //put nothing after this
	//set ca
}

void HelloGL::Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_delete != true){
	for (int i = 0; i < 9; i++) {
		Planets[i]->Draw();
	}
	}
	Vector3 v = { -1.4f, 0.7f, -1.0f };
	Color c = { 255.0f, 255.0f, 255.0f };
	if ((m_delete == false) && (deleted_once == false)) {
		DrawString("Planets, arent they cool, i dont think so, hit p", &v, &c);
	}
	else if ((m_delete == false) && (deleted_once == true)) {
		DrawString("Theyre back :(( click p i dont like them", &v, &c);
	}
	else {
		DrawString("No more :)), dont click m", &v, &c);
	}

	glFlush();
	glutSwapBuffers(); // double buffering
}

HelloGL::~HelloGL(void) {
	delete camera;
}

void HelloGL::Update() {
	planet_slower++;
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
		camera->centre.x, camera->centre.y, camera->centre.z,
		camera->up.x, camera->up.y, camera->up.z);
	glTranslatef(0.0f, 0.0f, -5.0f);

	/*glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));*/

	if (m_delete != true) {
		for (int i = 0; i < 9; i++)
		{
			Planets[i]->Update();

		}
	}
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y) {
	//WS = zoom in/ zoom out
	//AD = left/right movement
	
	if (key == 'w') 
		camera->eye.y -= 100.0f; // zoom in
	if (key == 'a') {
		camera->eye.z += 100.0f; // zoom in
		camera->centre.z += 100.0f;
	}
	if (key == 's')
		camera->eye.y += 100.0f; // zoom in
	if (key == 'd') {
		camera->eye.z -= 100.0f; // zoom in
		camera->centre.z -= 100.0f;
	}
	if (key == 'p') {
		m_delete = true;
		deleted_once = true;
	}
	if (key == 'm') {
		m_delete = false;
	}
}

void HelloGL::InitObjects() {
	camera = new Camera();
	camera->eye.x = 1.0f; camera->eye.y = 10000.0f; camera->eye.z = 0.0f;
	camera->centre.x = 0.0f, camera->centre.y = 0.0f, camera->centre.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	
	//sun
	//(Mesh* mesh, Texture2D* texture, std::string name, int size, int x, int y, int z, int orbit, int sundistance)
	Mesh* sunMesh = MeshLoader::Load((char*)"cube.txt", SUN_SIZE);
	Texture2D* sunTexture = new Texture2D();
	sunTexture->Load((char*)"sun.tga", 512, 512);
	Planets[0] = new Planet(sunMesh, sunTexture, "Sun", SUN_SIZE, 0, 0, 0, 0, 0);

	//mercury
	Mesh* mercuryMesh = MeshLoader::Load((char*)"cube.txt", MERCURY_SIZE);
	Texture2D* mercuryTexture = new Texture2D();
	mercuryTexture->Load((char*)"Textures/mercury.bmp", 512, 512);
	Planets[1] = new Planet(mercuryMesh, mercuryTexture, "Mercury", MERCURY_SIZE, MERCURY_DISTANCE, 0, 0, 88, MERCURY_DISTANCE);

	//venus
	Mesh* venusMesh = MeshLoader::Load((char*)"cube.txt", VENUS_SIZE);
	Texture2D* venusTexture = new Texture2D();
	venusTexture->Load((char*)"Textures/venus.bmp", 512, 512);
	Planets[2] = new Planet(venusMesh, venusTexture, "Venus", VENUS_SIZE, VENUS_DISTANCE, 0, 0, 225, VENUS_DISTANCE);

	//earth
	Mesh* earthMesh = MeshLoader::Load((char*)"cube.txt", EARTH_SIZE);
	Texture2D* earthTexture = new Texture2D();
	earthTexture->Load((char*)"Textures/earth.bmp", 512, 512);
	Planets[3] = new Planet(earthMesh, earthTexture, "Earth", EARTH_SIZE, EARTH_DISTANCE, 0, 0, 365, EARTH_DISTANCE);

	//mars
	Mesh* marsMesh = MeshLoader::Load((char*)"cube.txt", MARS_SIZE);
	Texture2D* marsTexture = new Texture2D();
	marsTexture->Load((char*)"Textures/mars.bmp", 512, 512);
	Planets[4] = new Planet(marsMesh, marsTexture, "Mars", MARS_SIZE, MARS_DISTANCE, 0, 0, 687, MARS_DISTANCE);

	//jupiter
	Mesh* jupiterMesh = MeshLoader::Load((char*)"cube.txt", JUPITER_SIZE);
	Texture2D* jupiterTexture = new Texture2D();
	jupiterTexture->Load((char*)"Textures/jupiter.bmp", 512, 512);
	Planets[5] = new Planet(jupiterMesh, jupiterTexture, "Jupiter", JUPITER_SIZE, JUPITER_DISTANCE, 0, 0, 4330, JUPITER_DISTANCE);

	//saturn
	Mesh* saturnMesh = MeshLoader::Load((char*)"cube.txt", SATURN_SIZE);
	Texture2D* saturnTexture = new Texture2D();
	saturnTexture->Load((char*)"Textures/saturn.bmp", 512, 512);
	Planets[6] = new Planet(saturnMesh, saturnTexture, "Saturn", SATURN_SIZE, SATURN_DISTANCE, 0, 0, 10756, SATURN_DISTANCE);

	//uranus
	Mesh* uranusMesh = MeshLoader::Load((char*)"cube.txt", URANUS_SIZE);
	Texture2D* uranusTexture = new Texture2D();
	uranusTexture->Load((char*)"Textures/uranus.bmp", 512, 512);
	Planets[7] = new Planet(uranusMesh, uranusTexture, "Uranus", URANUS_SIZE, URANUS_DISTANCE, 0, 0, 30687, URANUS_DISTANCE);

	//neptune
	Mesh* neptuneMesh = MeshLoader::Load((char*)"cube.txt", NEPTUNE_SIZE);
	Texture2D* neptuneTexture = new Texture2D();
	neptuneTexture->Load((char*)"Textures/neptune.bmp", 512, 512);
	Planets[8] = new Planet(neptuneMesh, neptuneTexture, "Neptune", NEPTUNE_SIZE, NEPTUNE_DISTANCE, 0, 0, 60190, NEPTUNE_DISTANCE);
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::InitGL(int argc, char* argv[]) {

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); // double buffering
	//glEnable(GL_DEPTH_TEST);
	
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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(255, 255, 255);
	glRasterPos3f(2000.0f, 0.0f, 2000.0f);
	glTranslatef(position->x, position->y, position->z);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}
