#include <cstdio>		// for C++ i/o
#include <iostream>
#include <string>
#include <cstddef>
#include <ctime>
using namespace std;	// to avoid having to use std::

#define GLEW_STATIC		// include GLEW as a static library
#include <GLEW/glew.h>	// include GLEW
#include <GLFW/glfw3.h>	// include GLFW (which includes the OpenGL header)
#include <glm/glm.hpp>	// include GLM (ideally should only use the GLM headers that are actually used)
#include <glm/gtx/transform.hpp>
using namespace glm;	// to avoid having to use glm::

#include <AntTweakBar.h>
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "shader.h"
#include "bmpfuncs.h"
#include "camera.h"

Camera g_camera;			// camera
float animation; 

struct Vertex
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat tangent[3];
	GLfloat texCoord[2];
};

struct LightProperties
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
	vec3 attenuation; 
	float cutoffAngle;
	vec3 direction;
};

struct MaterialProperties
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

Vertex g_vertices[] = {
	// Front: triangle 1
	// vertex 1
	0.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.0f, 0.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate

	// triangle 2
	// vertex 1
	10.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.0f, 0.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 0.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 0.0f,			// texture coordinate
};

Vertex front_vertices[] = {
	// Front: triangle 1
	// vertex 1
	0.0f, 10.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 10.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	
	// triangle 2
	// vertex 1
	10.0f, 10.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 0.0f,			// texture coordinate
};

Vertex left_vertices[] = {
	// Front: triangle 1
	// vertex 1
	0.0f, 10.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	
	// triangle 2
	// vertex 1
	0.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.0f, 0.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 0.0f,			// texture coordinate
};

Vertex right_vertices[] = {
	// Front: triangle 1
	// vertex 1
	10.0f, 10.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 1.0f,			// texture coordinate
	// vertex 2
	10.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	
	// triangle 2
	// vertex 1
	10.0f, 10.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	// vertex 2
	10.0f, 0.0f, 10.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 0.0f, 0.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 0.0f,			// texture coordinate
};

Vertex floor_vertices[] = {
	// Front: triangle 1
	// vertex 1
	0.0f, 0.0f, 10.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 5.0f,			// texture coordinate
	// vertex 2
	10.0f, 0.0f, 10.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.0f, 0.0f, 0.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	5.0f, 5.0f,			// texture coordinate
	
	// triangle 2
	// vertex 1
	0.0f, 0.0f, 0.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	5.0f, 5.0f,			// texture coordinate
	// vertex 2
	10.0f, 0.0f, 10.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	10.0f, 0.0f, 0.0f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	5.0f, 0.0f,			// texture coordinate
};

Vertex panel[] = {
	// Front: triangle 1
	// vertex 1
	3.0f, 4.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 2
	3.0f, 0.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	7.0f, 4.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate

	// triangle 2
	// vertex 1
	7.0f, 4.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 2
	3.0f, 0.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	7.0f, 0.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
};

Vertex frontPainting[] = {
	// Front: triangle 1
	// vertex 1
	3.0f, 7.0f, 0.05f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 1.0f,			// texture coordinate
	// vertex 2
	3.0f, 4.0f, 0.05f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	7.0f, 7.0f, 0.05f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate

	// triangle 2
	// vertex 1
	7.0f, 7.0f, 0.05f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	// vertex 2
	3.0f, 4.0f, 0.05f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	7.0f, 4.0f, 0.05f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 0.0f,			// texture coordinate
};


Vertex leftPainting[] = {
	// Front: triangle 1
	// vertex 1
	0.05f, 7.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.05f, 4.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.05f, 7.0f, 3.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	
	// triangle 2
	// vertex 1
	0.05f, 7.0f, 3.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 1.0f,			// texture coordinate
	// vertex 2
	0.05f, 4.0f, 7.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.05f, 4.0f, 3.0f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	1.0f, 0.0f,			// texture coordinate
};

Vertex cube_vertices[] = {
	// Front: triangle 1
	// vertex 1
	-0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate

	// triangle 2
	// vertex 1
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.5f, -0.5f, 0.5f,	// position
	0.0f, 0.0f, 1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate

	// Right: triangle 3
	// vertex 1
	0.5f, 0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate
	// vertex 2
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.5f, 0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate

	// triangle 4
	// vertex 1
	0.5f, 0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate
	// vertex 2
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.5f, -0.5f, -0.5f,	// position
	1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	
	// Back: triangle 5
	// vertex 1
	0.5f, -0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 2
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate

	// triangle 6
	// vertex 1
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate
	// vertex 2
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	// vertex 3
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, -1.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate

	// Left: triangle 7
	// vertex 1
	-0.5f, -0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	// vertex 2
	-0.5f, 0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate
	// vertex 3
	-0.5f, -0.5f, -0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate

	// triangle 8
	// vertex 1
	-0.5f, -0.5f, -0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 2
	-0.5f, 0.5f, 0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate
	// vertex 3
	-0.5f, 0.5f, -0.5f,	// position
	-1.0f, 0.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate

	// Top: triangle 9
	// vertex 1
	-0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
	// vertex 2
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	// vertex 3
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate

	// triangle 10
	// vertex 1
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate
	// vertex 2
	0.5f, 0.5f, 0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	// vertex 3
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate

	// Bottom: triangle 11
	// vertex 1
	0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 2.0f,			// texture coordinate
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate
	// vertex 3
	0.5f, -0.5f, -0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate

	// triangle 12
	// vertex 1
	0.5f, -0.5f, -0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	2.0f, 0.0f,			// texture coordinate
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 2.0f,			// texture coordinate
	// vertex 3
	-0.5f, -0.5f, -0.5f,// position
	0.0f, -1.0f, 0.0f,	// normal
	1.0f, 0.0f, 0.0f,	// tangent
	0.0f, 0.0f,			// texture coordinate
};




bool cameraRotation = false; 

GLuint g_windowWidth = 1024;		// window dimensions
GLuint g_windowHeight = 768;

GLuint g_MVP_Index;
GLuint g_M_Index;
GLuint g_viewPointIndex;
GLuint g_texSamplerIndex;
GLuint g_normalSamplerIndex;
GLuint g_lightPositionIndex;
GLuint g_lightAmbientIndex;
GLuint g_lightDiffuseIndex;
GLuint g_lightSpecularIndex;
GLuint g_lightShininessIndex;
GLuint g_lightCutoffIndex;
GLuint g_lightDirectionIndex;
GLuint g_alphaIndex;

GLuint g_materialAmbientIndex;
GLuint g_materialDiffuseIndex;
GLuint g_materialSpecularIndex;


GLuint c_MVP_Index;
GLuint c_M_Index;
GLuint c_viewPointIndex;
GLuint c_envMapSamplerIndex;
GLuint c_lightPositionIndex;
GLuint c_lightAmbientIndex;
GLuint c_lightDiffuseIndex;
GLuint c_lightSpecularIndex;
GLuint c_lightShininessIndex;
GLuint c_materialAmbientIndex;
GLuint c_materialDiffuseIndex;
GLuint c_materialSpecularIndex;
GLuint c_hueIndex;
GLuint c_satIndex;
GLuint c_lightIndex;

LightProperties g_lightProperties;
MaterialProperties g_materialProperties [5];

unsigned char* g_texImage[14];	//image data
GLuint g_textureID[12];			//texture id

glm::mat4 g_modelMatrix[9];		// object's model matrix
float reflectValue; 
float alpha;

float hue, sat, light; 

Vertex* g_pMeshVertices [5];	// pointer to mesh vertices
GLint g_numberOfVertices [5];	// number of vertices in the mesh
GLint* g_pMeshIndices [5];	// pointer to mesh indices
GLint g_numberOfFaces [5];		// number of faces in the mesh


GLuint g_FBO = 0;				// framebuffer object identifier
GLuint g_IBO[5];				// index buffer object identifier
GLuint g_VBO[11];				// vertex buffer object identifier
GLuint g_VAO[11];				// vertex array object identifier
GLuint g_shaderProgramID[2];	// shader program identifier

GLint imageWidth[9];			//image width info
GLint imageHeight[9];			//image height info


bool load_mesh(const char* fileName, int index)
{
	// load file with assimp 
	const aiScene* pScene = aiImportFile(fileName, aiProcess_Triangulate 
		| aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	// check whether scene was loaded
	if (!pScene)
	{
		cout << "Could not load mesh." << endl;
		return false;
	}

	// get pointer to mesh 0
	const aiMesh* pMesh = pScene->mMeshes[0];

	// store number of mesh vertices
	g_numberOfVertices[index] = pMesh->mNumVertices;

	// if mesh contains vertex coordinates
	if (pMesh->HasPositions())
	{
		// allocate memory for vertices
		g_pMeshVertices[index] = new Vertex[pMesh->mNumVertices];

		// read vertex coordinates and store in the array
		for (int i = 0; i < pMesh->mNumVertices; i++)
		{
			const aiVector3D* pVertexPos = &(pMesh->mVertices[i]);

			g_pMeshVertices[index][i].position[0] = (GLfloat)pVertexPos->x;
			g_pMeshVertices[index][i].position[1] = (GLfloat)pVertexPos->y;
			g_pMeshVertices[index][i].position[2] = (GLfloat)pVertexPos->z;
		}
	}

	// if mesh contains normals
	if (pMesh->HasNormals())
	{
		// read normals and store in the array
		for (int i = 0; i < pMesh->mNumVertices; i++)
		{
			const aiVector3D* pVertexNormal = &(pMesh->mNormals[i]);

			g_pMeshVertices[index][i].normal[0] = (GLfloat)pVertexNormal->x;
			g_pMeshVertices[index][i].normal[1] = (GLfloat)pVertexNormal->y;
			g_pMeshVertices[index][i].normal[2] = (GLfloat)pVertexNormal->z;
		}
	}

	// if mesh contains faces
	if (pMesh->HasFaces())
	{
		// store number of mesh faces
		g_numberOfFaces[index] = pMesh->mNumFaces;

		// allocate memory for vertices
		g_pMeshIndices[index] = new GLint[pMesh->mNumFaces*3];

		// read normals and store in the array
		for (int i = 0; i < pMesh->mNumFaces; i++)
		{
			const aiFace* pFace = &(pMesh->mFaces[i]);

			g_pMeshIndices[index][i * 3] = (GLint)pFace->mIndices[0];
			g_pMeshIndices[index][i * 3 + 1] = (GLint)pFace->mIndices[1];
			g_pMeshIndices[index][i * 3 + 2] = (GLint)pFace->mIndices[2];
		}
	}

	// release the scene
	aiReleaseImport(pScene);

	return true;
}

static void init(GLFWwindow* window)
{
	animation = 0.0; 
	reflectValue = 0.5; 
	alpha = 0.8; 

	hue = 0.0; 
	sat = 0.0; 
	light = 0.0; 

	glEnable(GL_DEPTH_TEST);		// enable depth buffer test
	g_texImage[0] = readBitmapRGBImage("images/Fieldstone.bmp", &imageWidth[0], &imageHeight[0]);
	g_texImage[1] = readBitmapRGBImage("images/FieldstoneBumpDOT3.bmp", &imageWidth[1], &imageHeight[1]);
	g_texImage[2] = readBitmapRGBImage("images/Tile4.bmp", &imageWidth[2], &imageHeight[2]);
	g_texImage[3] = readBitmapRGBImage("images/Tile4BumpDOT3.bmp", &imageWidth[3], &imageHeight[3]);
	g_texImage[4] = readBitmapRGBImage("images/smile.bmp", &imageWidth[4], &imageHeight[4]);
	g_texImage[5] = readBitmapRGBImage("images/check.bmp", &imageWidth[5], &imageHeight[5]);

	g_texImage[6] = readBitmapRGBImage("images/cm_front.bmp", &imageWidth[6], &imageHeight[6]);
	g_texImage[7] = readBitmapRGBImage("images/cm_back.bmp", &imageWidth[6], &imageHeight[6]);
	g_texImage[8] = readBitmapRGBImage("images/cm_left.bmp", &imageWidth[6], &imageHeight[6]);
	g_texImage[9] = readBitmapRGBImage("images/cm_right.bmp", &imageWidth[6], &imageHeight[6]);
	g_texImage[10] = readBitmapRGBImage("images/cm_top.bmp", &imageWidth[6], &imageHeight[6]);
	g_texImage[11] = readBitmapRGBImage("images/cm_bottom.bmp", &imageWidth[6], &imageHeight[6]);

	g_texImage[12] = readBitmapRGBImage("images/White.bmp", &imageWidth[7], &imageHeight[7]);
	g_texImage[13] = readBitmapRGBImage("images/WhiteBumpDOT3.bmp", &imageWidth[8], &imageHeight[8]);

	// create and compile our GLSL program from the shader files
	g_shaderProgramID[0] = loadShaders("NormalMappingVS.vert", "NormalMappingFS.frag");
	g_shaderProgramID[1] = loadShaders("CubeEnvMapVS.vert", "CubeEnvMapFs.frag"); 

	// find the location of shader variables
	GLuint positionIndex = glGetAttribLocation(g_shaderProgramID[0], "aPosition");
	GLuint normalIndex = glGetAttribLocation(g_shaderProgramID[0], "aNormal");
	GLuint tangentIndex = glGetAttribLocation(g_shaderProgramID[0], "aTangent");
	GLuint texCoordIndex = glGetAttribLocation(g_shaderProgramID[0], "aTexCoord");

	g_MVP_Index = glGetUniformLocation(g_shaderProgramID[0], "uModelViewProjectionMatrix");
	g_M_Index = glGetUniformLocation(g_shaderProgramID[0], "uModelMatrix");
	g_viewPointIndex = glGetUniformLocation(g_shaderProgramID[0], "uViewPoint");
	g_texSamplerIndex = glGetUniformLocation(g_shaderProgramID[0], "uTextureSampler");
	g_normalSamplerIndex = glGetUniformLocation(g_shaderProgramID[0], "uNormalSampler");

	g_lightPositionIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.position");
	g_lightAmbientIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.ambient");
	g_lightDiffuseIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.diffuse");
	g_lightSpecularIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.specular");
	g_lightShininessIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.shininess");
	g_lightCutoffIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.cutoffAngle");
	g_lightDirectionIndex = glGetUniformLocation(g_shaderProgramID[0], "uLightingProperties.direction");
	g_alphaIndex = glGetUniformLocation(g_shaderProgramID[0], "uAlpha");

	g_materialAmbientIndex = glGetUniformLocation(g_shaderProgramID[0], "uMaterialProperties.ambient");
	g_materialDiffuseIndex = glGetUniformLocation(g_shaderProgramID[0], "uMaterialProperties.diffuse");
	g_materialSpecularIndex = glGetUniformLocation(g_shaderProgramID[0], "uMaterialProperties.specular");

	//=======================================================================

	GLuint cubePositionIndex = glGetAttribLocation(g_shaderProgramID[1], "aPosition");
	GLuint cubeNormalIndex = glGetAttribLocation(g_shaderProgramID[1], "aNormal");
	GLuint cubeTexCoordIndex = glGetAttribLocation(g_shaderProgramID[1], "aTexCoord");

	c_MVP_Index = glGetUniformLocation(g_shaderProgramID[1], "uModelViewProjectionMatrix");
	c_M_Index = glGetUniformLocation(g_shaderProgramID[1], "uModelMatrix");
	c_viewPointIndex = glGetUniformLocation(g_shaderProgramID[1], "uViewPoint");
	c_envMapSamplerIndex = glGetUniformLocation(g_shaderProgramID[1], "uEnvironmentMap");

	c_lightPositionIndex = glGetUniformLocation(g_shaderProgramID[1], "uLightingProperties.position");
	c_lightAmbientIndex = glGetUniformLocation(g_shaderProgramID[1], "uLightingProperties.ambient");
	c_lightDiffuseIndex = glGetUniformLocation(g_shaderProgramID[1], "uLightingProperties.diffuse");
	c_lightSpecularIndex = glGetUniformLocation(g_shaderProgramID[1], "uLightingProperties.specular");
	c_lightShininessIndex = glGetUniformLocation(g_shaderProgramID[1], "uLightingProperties.shininess");

	c_materialAmbientIndex = glGetUniformLocation(g_shaderProgramID[1], "uMaterialProperties.ambient");
	c_materialDiffuseIndex = glGetUniformLocation(g_shaderProgramID[1], "uMaterialProperties.diffuse");
	c_materialSpecularIndex = glGetUniformLocation(g_shaderProgramID[1], "uMaterialProperties.specular");

	c_hueIndex = glGetUniformLocation (g_shaderProgramID[1], "AddHue"); 
	c_satIndex = glGetUniformLocation (g_shaderProgramID[1], "AddSat"); 
	c_lightIndex = glGetUniformLocation (g_shaderProgramID[1], "AddLig"); 


	// initialise model matrix to the identity matrix
	g_modelMatrix[0] = glm::mat4(1.0f);
	g_modelMatrix[1] = glm::mat4(1.0f);
	g_modelMatrix[2] = glm::mat4(1.0f);
	g_modelMatrix[3] = glm::mat4(1.0f);
	g_modelMatrix[4] = glm::mat4(1.0f);
	g_modelMatrix[5] = glm::mat4(1.0f);
	g_modelMatrix[6] = glm::mat4(1.0f);
	g_modelMatrix[7] = glm::mat4(1.0f);
	g_modelMatrix[8] = glm::mat4(1.0f);

	load_mesh("models/cube.obj", 0);
	load_mesh("models/WusonOBJ.obj", 1);

	// initialise view matrix and projection matrix
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / height;

	g_camera.setViewMatrix(glm::vec3(5.0, 1.5, 8.5), glm::vec3(0, -15, 0), glm::vec3(0, 1, 0));
	g_camera.setProjectionMatrix(glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f));

	// initialise light and material properties
	g_lightProperties.position = glm::vec4(5.0f, 1.0f, 12.0f, 1.0f);
	g_lightProperties.ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_lightProperties.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_lightProperties.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_lightProperties.shininess = 10.0f;
	g_lightProperties.cutoffAngle = 20.0f;
	g_lightProperties.direction = glm::vec3(0.0f, -1.0f, 0.0f);

	g_materialProperties[0].ambient = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	g_materialProperties[0].diffuse = glm::vec4(0.2f, 0.7f, 1.0f, 1.0f);
	g_materialProperties[0].specular = glm::vec4(0.2f, 0.7f, 1.0f, 1.0f);

	g_materialProperties[1].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_materialProperties[1].diffuse = glm::vec4(0.2f, 0.7f, 1.0f, 1.0f);
	g_materialProperties[1].specular = glm::vec4(0.2f, 0.7f, 1.0f, 1.0f);

	g_materialProperties[2].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_materialProperties[2].diffuse = glm::vec4(0.2f, 0.7f, 1.0f, 1.0f);
	g_materialProperties[2].specular = glm::vec4(0.2f, 0.7f, 1.0f, 1.0f);

	g_materialProperties[3].ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_materialProperties[3].diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_materialProperties[3].specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// generate identifier for texture object and set texture properties
	glGenTextures(9, g_textureID);
	glBindTexture(GL_TEXTURE_2D, g_textureID[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[0], imageHeight[0], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, g_textureID[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[1], imageHeight[1], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[1]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//============================================
	
	glBindTexture(GL_TEXTURE_2D, g_textureID[2]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[2], imageHeight[2], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[2]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, g_textureID[3]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[3], imageHeight[3], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[3]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//============================================

	glBindTexture(GL_TEXTURE_2D, g_textureID[4]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[4], imageHeight[4], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[4]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//============================================

	glBindTexture(GL_TEXTURE_2D, g_textureID[5]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[5], imageHeight[5], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[5]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//============================================
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_textureID[6]);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, imageWidth[6], imageHeight[6], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[9]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, imageWidth[6], imageHeight[6], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[8]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, imageWidth[6], imageHeight[6], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[10]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, imageWidth[6], imageHeight[6], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[11]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, imageWidth[6], imageHeight[6], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[7]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, imageWidth[6], imageHeight[6], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[6]);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	//============================================

	glBindTexture(GL_TEXTURE_2D, g_textureID[7]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[7], imageHeight[7], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[12]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//============================================
	
	glBindTexture(GL_TEXTURE_2D, g_textureID[8]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[8], imageHeight[8], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[13]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//============================================

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(11, g_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(front_vertices), front_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(left_vertices), left_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(right_vertices), right_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vertices), floor_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_numberOfVertices[0], g_pMeshVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_numberOfVertices[1], g_pMeshVertices[1], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(panel), panel, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(frontPainting), frontPainting, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftPainting), leftPainting, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glGenBuffers(5, g_IBO);

	//Loading Cube
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)* 3 * g_numberOfFaces[0], g_pMeshIndices[0], GL_STATIC_DRAW);

	//Loading Wuson
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)* 3 * g_numberOfFaces[1], g_pMeshIndices[1], GL_STATIC_DRAW);


	// generate identifiers for VAO
	glGenVertexArrays(11, g_VAO);

	// create VAO and specify VBO data
	glBindVertexArray(g_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[0]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	//front
	glBindVertexArray(g_VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[1]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));

	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	//left
	glBindVertexArray(g_VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	//right
	glBindVertexArray(g_VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[3]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	//floor
	glBindVertexArray(g_VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[4]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);
	
	//panel
	glBindVertexArray(g_VAO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[7]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	glBindVertexArray(g_VAO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[8]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	glBindVertexArray(g_VAO[7]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[9]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	glBindVertexArray(g_VAO[8]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[0]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);

	glBindVertexArray(g_VAO[9]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[6]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[1]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);


	glBindVertexArray(g_VAO[10]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[10]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glVertexAttribPointer(tangentIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
	glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	
	// enable vertex attributes
	glEnableVertexAttribArray(positionIndex);
	glEnableVertexAttribArray(normalIndex);
	glEnableVertexAttribArray(tangentIndex);
	glEnableVertexAttribArray(texCoordIndex);
}

void draw_floor()
{
	glUseProgram(g_shaderProgramID[0]);	// use the shaders associated with the shader program

	glBindVertexArray(g_VAO[4]);		// make VAO active

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[2]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID[3]);

	glUniform1f(g_alphaIndex, reflectValue);

	// set shader variables
	glm::mat4 MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[4];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[4][0][0]);

	g_materialProperties[1].ambient = glm::vec4(0.2f, 0.2f, 0.2f, reflectValue);
	g_materialProperties[1].diffuse = glm::vec4(0.2f, 0.7f, 1.0f, reflectValue);
	g_materialProperties[1].specular = glm::vec4(0.2f, 0.7f, 1.0f, reflectValue);

	glUniform3fv(g_viewPointIndex, 1, &g_camera.getPosition()[0]);
	glUniform4fv(g_lightPositionIndex, 1, &g_lightProperties.position[0]);
	glUniform4fv(g_lightAmbientIndex, 1, &g_lightProperties.ambient[0]);
	glUniform4fv(g_lightDiffuseIndex, 1, &g_lightProperties.diffuse[0]);
	glUniform4fv(g_lightSpecularIndex, 1, &g_lightProperties.specular[0]);
	glUniform1fv(g_lightShininessIndex, 1, &g_lightProperties.shininess);
	glUniform1fv(g_lightCutoffIndex, 1, &g_lightProperties.cutoffAngle); 
	glUniform3fv(g_lightDirectionIndex, 1, &g_lightProperties.direction[0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[1].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[1].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[1].specular[0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void draw_objects(bool bReflect)
{
	glUseProgram(g_shaderProgramID[0]);	// use the shaders associated with the shader program
	
	// set shader variables
	glm::mat4 reflectMatrix = mat4(1.0f);
	glm::mat4 modelMatrix = mat4(1.0f);
	glm::mat4 MVP = mat4(1.0f);

	glm::vec3 lightPosition = g_lightProperties.position;

	if (bReflect)
	{
		reflectMatrix = glm::scale(vec3(1.0f, -1.0f, 1.0f));
		lightPosition = vec3(reflectMatrix * vec4(lightPosition, 1.0f));
	}
	else
	{
		reflectMatrix = mat4(1.0f);
	}

	glBindVertexArray(g_VAO[0]);		// make VAO active

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID[1]);

	modelMatrix = reflectMatrix * g_modelMatrix[0];
	// set uniform shader variables

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glUniform3fv(g_viewPointIndex, 1, &g_camera.getPosition()[0]);
	glUniform4fv(g_lightPositionIndex, 1, &lightPosition[0]);
	glUniform4fv(g_lightAmbientIndex, 1, &g_lightProperties.ambient[0]);
	glUniform4fv(g_lightDiffuseIndex, 1, &g_lightProperties.diffuse[0]);
	glUniform4fv(g_lightSpecularIndex, 1, &g_lightProperties.specular[0]);
	glUniform1fv(g_lightShininessIndex, 1, &g_lightProperties.shininess);
	glUniform1fv(g_lightCutoffIndex, 1, &g_lightProperties.cutoffAngle); 
	glUniform3fv(g_lightDirectionIndex, 1, &g_lightProperties.direction[0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[0].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[0].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[0].specular[0]);

	glUniform1i(g_texSamplerIndex, 0);
	glUniform1i(g_normalSamplerIndex, 1);

	//back wall

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== front wall ====================================

	glBindVertexArray(g_VAO[1]);

	modelMatrix = reflectMatrix * g_modelMatrix[1];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID[1]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== left wall ====================================

	glBindVertexArray(g_VAO[2]);

	// set uniform shader variables
	modelMatrix = reflectMatrix * g_modelMatrix[2];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== right wall ====================================

	glBindVertexArray(g_VAO[3]);

	// set uniform shader variables
	modelMatrix = reflectMatrix * g_modelMatrix[3];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== front painting ====================================

	glBindVertexArray (g_VAO[6]); 

	modelMatrix = reflectMatrix * g_modelMatrix[6];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[3].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[3].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[3].specular[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[4]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== left painting ====================================

	glBindVertexArray (g_VAO[7]); 

	modelMatrix = reflectMatrix * g_modelMatrix[6];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[5]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID[5]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== pedestal ====================================

	glBindVertexArray (g_VAO[10]); 

	modelMatrix = reflectMatrix * g_modelMatrix[7];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[3].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[3].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[3].specular[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[7]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID[8]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//=========================== Wuson ====================================
	glUseProgram(g_shaderProgramID[1]);

	glBindVertexArray (g_VAO[9]); 

	modelMatrix = reflectMatrix * g_modelMatrix[8];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(c_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(c_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glUniform3fv(c_viewPointIndex, 1, &g_camera.getPosition()[0]);
	glUniform4fv(c_lightPositionIndex, 1, &g_lightProperties.position[0]);
	glUniform4fv(c_lightAmbientIndex, 1, &g_lightProperties.ambient[0]);
	glUniform4fv(c_lightDiffuseIndex, 1, &g_lightProperties.diffuse[0]);
	glUniform4fv(c_lightSpecularIndex, 1, &g_lightProperties.specular[0]);
	glUniform1fv(c_lightShininessIndex, 1, &g_lightProperties.shininess);

	glUniform4fv(c_materialAmbientIndex, 1, &g_materialProperties[3].ambient[0]);
	glUniform4fv(c_materialDiffuseIndex, 1, &g_materialProperties[3].diffuse[0]);
	glUniform4fv(c_materialSpecularIndex, 1, &g_materialProperties[3].specular[0]);

	glUniform1f (c_hueIndex, hue);
	glUniform1f (c_satIndex, sat); 
	glUniform1f (c_lightIndex, light); 

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_textureID[6]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[1])*3, GL_UNSIGNED_INT, 0);

	//=========================== translucent screen ====================================
	glUseProgram(g_shaderProgramID[0]); 

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_textureID[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_textureID[1]);

	glEnable (GL_BLEND); 

	glBindVertexArray (g_VAO[5]); 
	
	glUniform1f(g_alphaIndex, alpha);

	modelMatrix = reflectMatrix * g_modelMatrix[5];

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * modelMatrix ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &modelMatrix[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[2].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[2].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[2].specular[0]);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable (GL_BLEND); 

	//===============================================================
	
}

static void render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	// clear colour buffer and depth buffer
	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);  //disable any modification of all color components
	glDepthMask(GL_FALSE);                                //disable any modification to depth buffer
	glEnable(GL_STENCIL_TEST);                            //enable stencil testing

	//setup the stencil buffer for a function reference value
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 1);

	draw_floor();

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);   //allow all color components to be modified 
	glDepthMask(GL_TRUE);                              //allow depth buffer contents to be modified

	draw_objects(true);	//Draw reflected view

	glDisable(GL_STENCIL_TEST);		//disable stencil testing

	//blend in reflection
	glEnable(GL_BLEND);		//enable blending            
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	draw_floor();

	glDisable(GL_BLEND);	//disable blending

	draw_objects(false);	//Draw actual Object

	glFlush();	// flush the pipeline
}

static void update_scene()
{
		
		animation += 1.0f;

		g_modelMatrix [7] = glm :: translate (glm:: vec3 (5.0f , 0.0f, 5.0f))
			* glm::scale (glm :: vec3 (0.75f, 3.0f, 0.75f)); 

		g_modelMatrix [8] = glm :: translate (glm:: vec3 (5.0f , 1.5f, 5.0f))
						* glm::scale (glm :: vec3 (0.3f, 0.3f, 0.3f))
						* glm :: rotate (glm::radians (animation), (glm :: vec3 (0.0f, 1.0f, 0.0f)));
 
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// quit if the ESCAPE key was press
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// set flag to close the window
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		// compute size of the image
		int size = g_windowWidth * g_windowHeight * 3;

		// allocate memory to store the image
		unsigned char* outBuffer = new unsigned char[size];

		// read pixels from the colour buffer
		glReadPixels(0, 0, g_windowWidth, g_windowHeight, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)outBuffer);

		// write the image to a file
		writeBitmapRGBImage("images/screenshot.bmp", (char*)outBuffer, g_windowWidth, g_windowHeight);

		// deallocate memory
		delete[] outBuffer;
	}


	else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		// compute size of the image
		int size = g_windowWidth * g_windowHeight * 3;

		// allocate memory to store the image
		unsigned char* outBuffer = new unsigned char[size];

		// read pixels from the colour buffer
		glReadPixels(0, 0, g_windowWidth, g_windowHeight, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)outBuffer);

		// write the image to a file
		writeBitmapRGBImage("images/temp.bmp", (char*)outBuffer, g_windowWidth, g_windowHeight);

		// deallocate memory
		delete[] outBuffer;

		g_texImage[5] = readBitmapRGBImage("images/temp.bmp", &imageWidth[5], &imageHeight[5]);

		//============================================

		glBindTexture(GL_TEXTURE_2D, g_textureID[5]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth[5], imageHeight[5], 0, GL_BGR, GL_UNSIGNED_BYTE, g_texImage[5]);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
		//============================================
	}

}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// pass mouse data to tweak bar
	TwEventMousePosGLFW(xpos, ypos);

	static double previous_xpos = xpos;
	static double previous_ypos = ypos;

	if (cameraRotation) 
	{

		double delta_x = xpos - previous_xpos;
		double delta_y = ypos - previous_ypos;

	
		// pass mouse movement to camera class
		g_camera.updateYaw(delta_x);
		g_camera.updatePitch(delta_y);

		// update previous mouse coordinates
	}

	previous_xpos = xpos;
	previous_ypos = ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// pass mouse data to tweak bar
	TwEventMouseButtonGLFW(button, action);

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		cameraRotation = true; 
	}

	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		cameraRotation = false; 
	}
}

static void error_callback(int error, const char* description)
{
	cerr << description << endl;	// output error description
}

int main(void)
{
	GLFWwindow* window = NULL;	// pointer to a GLFW window handle
	TwBar *TweakBar;			// pointer to a tweak bar
	double lastUpdateTime = glfwGetTime();	// last update time
	double elapsedTime = lastUpdateTime;	// time elapsed since last update
	double frameTime = 0.0f;				// frame time

	glfwSetErrorCallback(error_callback);	// set error callback function

	// initialise GLFW
	if (!glfwInit())
	{
		// if failed to initialise GLFW
		exit(EXIT_FAILURE);
	}

	// minimum OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// create a window and its OpenGL context
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Assignment 4", NULL, NULL);

	// if failed to create window
	if (window == NULL)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);	// set window context as the current context
	glfwSwapInterval(1);			// swap buffer interval

	// initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		// if failed to initialise GLEW
		cerr << "GLEW initialisation failed" << endl;
		exit(EXIT_FAILURE);
	}

	// set key callback function
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// initialise AntTweakBar
	TwInit(TW_OPENGL_CORE, NULL);

	// give tweak bar the size of graphics window
	TwWindowSize(g_windowWidth, g_windowHeight);
	TwDefine(" TW_HELP visible=false ");	// disable help menu
	TwDefine(" GLOBAL fontsize=3 ");		// set large font size

	// create a tweak bar
	TweakBar = TwNewBar("Main");
	TwDefine(" Main label='Light Control ' refresh=0.02 text=light size='300 600' ");

	TwAddVarRW(TweakBar, "Light X", TW_TYPE_FLOAT, &g_lightProperties.position[0], " group='Light Position' min=2.0 max=12.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Light Y", TW_TYPE_FLOAT,&g_lightProperties.position[1], " group='Light Position' min=2.0 max=12.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Light Z", TW_TYPE_FLOAT, &g_lightProperties.position[2], " group='Light Position' min=2.0 max=12.0 step=0.1 ");

	TwAddSeparator(TweakBar, NULL, NULL);

	//========================================================

	TwAddVarRW(TweakBar, "Floor Reflective", TW_TYPE_FLOAT, &reflectValue, " group='Floor' min=0.0 max=1.0 step=0.01 ");

	TwAddSeparator(TweakBar, NULL, NULL);

	//========================================================
	TwAddVarRW(TweakBar, "Panel Alpha", TW_TYPE_FLOAT, &alpha, " group='Glass Partition' min=0.0 max=1.0 step=0.01 ");
	
	TwAddSeparator(TweakBar, NULL, " group='Glass Partition'");

	TwAddVarRW(TweakBar, "Ambient R", TW_TYPE_FLOAT, &g_materialProperties[2].ambient[0], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Ambient G", TW_TYPE_FLOAT, &g_materialProperties[2].ambient[1], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Ambient B", TW_TYPE_FLOAT, &g_materialProperties[2].ambient[2], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");

	TwAddSeparator(TweakBar, NULL, " group='Glass Partition'");
	
	TwAddVarRW(TweakBar, "Diffuse R", TW_TYPE_FLOAT, &g_materialProperties[2].diffuse[0], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Diffuse G", TW_TYPE_FLOAT, &g_materialProperties[2].diffuse[1], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Diffuse B", TW_TYPE_FLOAT, &g_materialProperties[2].diffuse[2], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");

	TwAddSeparator(TweakBar, NULL, " group='Glass Partition'");

	TwAddVarRW(TweakBar, "Specular R", TW_TYPE_FLOAT, &g_materialProperties[2].specular[0], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Specular G", TW_TYPE_FLOAT, &g_materialProperties[2].specular[1], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Specular B", TW_TYPE_FLOAT, &g_materialProperties[2].specular[2], " group='Glass Partition' min=0.0 max=1.0 step=0.1 ");
	
	TwAddSeparator(TweakBar, NULL, NULL);

	//========================================================

	TwAddVarRW(TweakBar, "Hue", TW_TYPE_FLOAT, &hue, " group='CubeMap' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Saturation", TW_TYPE_FLOAT, &sat, " group='CubeMap' min=0.0 max=1.0 step=0.1 ");
	TwAddVarRW(TweakBar, "Brightness", TW_TYPE_FLOAT, &light, " group='CubeMap' min=0.0 max=1.0 step=0.1 ");

	// initialise rendering states
	init(window);

	// the rendering loop
	while (!glfwWindowShouldClose(window))
	{
		g_camera.update(window);

		update_scene();		// update the scene

		render_scene();		// render the scene

		TwDraw();			// draw tweak bar(s)

		glfwSwapBuffers(window);	// swap buffers
		glfwPollEvents();			// poll for events

		elapsedTime = glfwGetTime() - lastUpdateTime;	// current time - last update time

	}

	// clean up

	/*if (g_pMeshVertices)
		delete[] g_pMeshVertices;
	if (g_pMeshIndices)
		delete[] g_pMeshIndices;*/

	glDeleteProgram(g_shaderProgramID[0]);
	glDeleteProgram(g_shaderProgramID[1]);
	glDeleteBuffers(5, g_IBO);
	glDeleteBuffers(10, g_VBO);
	glDeleteVertexArrays(2, g_VAO);

	// uninitialise tweak bar
	TwTerminate();

	// close the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}