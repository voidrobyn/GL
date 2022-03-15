#include "MeshLoader.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexture(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh){
		inFile >> mesh.ColorCount;
		mesh.Colors = new Color[mesh.ColorCount];
		for (int i = 0; i < mesh.ColorCount; i++) {
			inFile >> mesh.Colors[i].r;
			inFile >> mesh.Colors[i].g;
			inFile >> mesh.Colors[i].b;
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh){
		inFile >> mesh.IndexCount;
		mesh.Indices = new GLushort[mesh.IndexCount];
		for (int i = 0; i < mesh.IndexCount; i++) {
			inFile >> mesh.Indices[i];
		}
	}

	void LoadTexture(ifstream& inFile, Mesh& mesh){
		inFile >> mesh.TexCoordsCount;
		cout << mesh.TexCoordsCount << endl;
		mesh.TexCoords = new TexCoord[mesh.TexCoordsCount];
		for (int i = 0; i < mesh.TexCoordsCount; i++) {
			inFile >> mesh.TexCoords[i].u;
			inFile >> mesh.TexCoords[i].v;
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadTexture(inFile, *mesh);
		LoadIndices(inFile, *mesh);
		

		return mesh;
	}
}