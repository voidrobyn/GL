#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "SceneObject.h"
#include "StaticObject.h"

#define REFRESHRATE 16



class HelloGL {
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);

private:
	float rotation;
	Camera* camera;
	SceneObject* objects[200];
	StaticObject* staticObjects[200];
};
