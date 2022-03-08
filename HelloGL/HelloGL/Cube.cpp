#include "Cube.h"

Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices = nullptr;
int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

Cube::Cube(float x, float y, float z) {
	_rotation = 0.0f;
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Cube::~Cube() {

}

void Cube::Draw() {
	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr) {
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
		glColorPointer(3, GL_FLOAT, 0, indexedColors);

		glPushMatrix();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Cube::Update() {
	_rotation += 0.1f;
}

void Cube::SetRotation(float Rotation) {

}

bool Cube::Load(char* path) {
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good()) {
		std::cerr << "Cant open text file" << path << std::endl;
		return false;
	}

	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices]; 
	for (int i = 0; i < numVertices; i++){
		inFile >> indexedVertices[i].x;
		inFile >> indexedVertices[i].y;
		inFile >> indexedVertices[i].z;
	}

	inFile >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++) {
		inFile >> indexedColors[i].r;
		inFile >> indexedColors[i].g;
		inFile >> indexedColors[i].b;
	}

	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++){
		inFile >> indices[i];
	}

	inFile.close();
	return true;
}