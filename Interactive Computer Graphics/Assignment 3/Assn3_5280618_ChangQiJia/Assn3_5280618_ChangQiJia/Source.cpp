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
#include "camera.h"

#define MAX_LIGHTS 3
#define MAX_ITEM 11

Camera g_camera;			// camera

// struct for vertex attributes
struct Vertex
{
	GLfloat position[3];
	GLfloat normal[3];
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
	float spotlight; 
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
	-0.667f, 0.0f, 0.0f,	//rect bottom left 
	0.0f, 0.0f, 1.0f,	// normal
	// vertex 2
	0.667f, 0.0f, 0.0f,	//rect bottom right
	0.0f, 0.0f, 1.0f,	// normal
	// vertex 3
	-0.667f, 0.5f, 0.0f,	//rect top left 
	0.0f, 0.0f, 1.0f,	// normal
	// vertex 3
	0.667f, 0.5f, 0.0f,	//rect top right
	0.0f, 0.0f, 1.0f,	// normal
};

bool cameraRotation = false; 

GLuint g_MVP_Index = 0;
GLuint g_M_Index = 0;
GLuint g_viewPointIndex = 0;
GLuint g_lightPositionIndex[MAX_LIGHTS];
GLuint g_lightAmbientIndex[MAX_LIGHTS];
GLuint g_lightDiffuseIndex[MAX_LIGHTS];
GLuint g_lightSpecularIndex[MAX_LIGHTS];
GLuint g_lightShininessIndex[MAX_LIGHTS];
GLuint g_lightAttenuationIndex[MAX_LIGHTS];
GLuint g_lightCutoffAngleIndex[MAX_LIGHTS];
GLuint g_lightDirectionIndex[MAX_LIGHTS];
GLuint g_lightSpotlightIndex[MAX_LIGHTS];


bool lightOn [MAX_LIGHTS] ; 
GLuint g_materialAmbientIndex ;
GLuint g_materialDiffuseIndex ;
GLuint g_materialSpecularIndex ;

LightProperties g_lightProperties[MAX_LIGHTS];
MaterialProperties g_materialProperties [MAX_ITEM];

/*
glm::vec4 materialAmbient(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 materialDiffuse(0.2f, 0.7f, 1.0f, 1.0f);
glm::vec4 materialSpecular(0.2f, 0.7f, 1.0f, 1.0f);*/
	

// initialise lighting properties
glm::vec4 lightAmbient(0.2f, 0.2f, 0.2f, 1.0f);
glm::vec4 lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 lightSpecular(1.0f, 1.0f, 1.0f, 1.0f);

GLuint g_windowWidth = 1024;		// window dimensions
GLuint g_windowHeight = 768;


glm::mat4 g_modelMatrix [8];		// object's model matrix
glm::vec3 g_viewPoint;			// view point

Vertex* g_pMeshVertices [5];	// pointer to mesh vertices
GLint g_numberOfVertices [5];	// number of vertices in the mesh
GLint* g_pMeshIndices [5];	// pointer to mesh indices
GLint g_numberOfFaces [5];		// number of faces in the mesh

GLuint g_IBO[5];				// index buffer object identifier
GLuint g_VBO[6];				// vertex buffer object identifier
GLuint g_VAO[6];				// vertex array object identifier
GLuint g_shaderProgramID = 0;	// shader program identifier

float dance; 
bool discoMode; 
float danceRotate; 
glm:: vec3 sphereLightMovement, cubeLightMovement; 

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
	glEnable(GL_DEPTH_TEST);	// enable depth buffer test

	dance = 0.3f;
	discoMode = false; 
	danceRotate = 0.0f; 

	// create and compile our GLSL program from the shader files
	g_shaderProgramID = loadShaders("PerFragLightingVS.vert", "PerFragLightingFS.frag");

	// find the location of shader variables
	GLuint positionIndex = glGetAttribLocation(g_shaderProgramID, "aPosition");
	GLuint normalIndex = glGetAttribLocation(g_shaderProgramID, "aNormal");
	g_MVP_Index = glGetUniformLocation(g_shaderProgramID, "uModelViewProjectionMatrix");
	g_M_Index = glGetUniformLocation(g_shaderProgramID, "uModelMatrix");
	g_viewPointIndex = glGetUniformLocation(g_shaderProgramID, "uViewPoint");
	
	g_lightPositionIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].position");
	g_lightAmbientIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].ambient");
	g_lightDiffuseIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].diffuse");
	g_lightSpecularIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].specular");
	g_lightShininessIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].shininess");
	g_lightAttenuationIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].attenuation");
	g_lightCutoffAngleIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].cutoffAngle");
	g_lightDirectionIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].direction");
	g_lightSpotlightIndex[0] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[0].spotlight");


	g_lightPositionIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].position");
	g_lightAmbientIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].ambient");
	g_lightDiffuseIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].diffuse");
	g_lightSpecularIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].specular");
	g_lightShininessIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].shininess");
	g_lightAttenuationIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].attenuation");
	g_lightCutoffAngleIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].cutoffAngle");
	g_lightDirectionIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].direction");
	g_lightSpotlightIndex[1] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[1].spotlight");


	g_lightPositionIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].position");
	g_lightAmbientIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].ambient");
	g_lightDiffuseIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].diffuse");
	g_lightSpecularIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].specular");
	g_lightShininessIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].shininess");
	g_lightAttenuationIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].attenuation");
	g_lightCutoffAngleIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].cutoffAngle");
	g_lightDirectionIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].direction");
	g_lightSpotlightIndex[2] = glGetUniformLocation(g_shaderProgramID, "uLightingProperties[2].spotlight");

	g_materialAmbientIndex = glGetUniformLocation(g_shaderProgramID, "uMaterialProperties.ambient");
	g_materialDiffuseIndex = glGetUniformLocation(g_shaderProgramID, "uMaterialProperties.diffuse");
	g_materialSpecularIndex = glGetUniformLocation(g_shaderProgramID, "uMaterialProperties.specular");
	
	lightOn [0] = true; 
	lightOn [1] = true; 
	lightOn [2] = true; 

	// initialise model matrix to the identity matrix
	g_modelMatrix[0] = glm::mat4(1.0f);		//table
	g_modelMatrix[1] = glm::mat4(1.0f);		//sphere light
	g_modelMatrix[2] = glm::mat4(1.0f);		//cube light
	g_modelMatrix[3] = glm::mat4(1.0f);		//chair 1
	g_modelMatrix[4] = glm::mat4(1.0f);		//chair 2
	g_modelMatrix[5] = glm::mat4(1.0f);		//Ornament 1
	g_modelMatrix[6] = glm::mat4(1.0f);		//Ornament 2
	g_modelMatrix[7] = glm::mat4(1.0f);		//Spotlight

	// initialise view matrix
	g_viewPoint = glm::vec3(0, 0, 3);
	g_camera.setViewMatrix(glm::vec3(0, 0.25, 1.5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / height;

	// initialise projection matrix
	g_camera.setProjectionMatrix(glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f));
	// load mesh
	load_mesh("models/cube.obj", 0);
	load_mesh("models/sphere.obj", 1);
	load_mesh("models/WusonOBJ.obj", 2);
	load_mesh("models/suzanne.obj", 3);

	g_lightProperties[0].position = glm::vec4(2.0f, 1.3f, 2.0f, 1.0f);
	g_lightProperties[0].ambient = glm::vec4(0.4f, 0.3f, 0.5f, 1.0f);
	g_lightProperties[0].diffuse = glm::vec4(0.3f, 0.7f, 0.5f, 1.0f);
	g_lightProperties[0].specular = glm::vec4(0.4f, 0.2f, 0.5f, 1.0f);
	g_lightProperties[0].shininess = 10.0f;
	g_lightProperties[0].attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
	g_lightProperties[0].cutoffAngle = -1.0f;
	g_lightProperties[0].direction = glm::vec3(0.0f, -1.0f, 0.0f);
	g_lightProperties[0].spotlight = 0.0f; 

	g_lightProperties[1].position = glm::vec4(-2.0f, 0.0f, -2.0f, 1.0f);
	g_lightProperties[1].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_lightProperties[1].diffuse = glm::vec4(0.5f, 0.8f, 0.8f, 1.0f);
	g_lightProperties[1].specular = glm::vec4(1.0f, 0.0f, 0.8f, 1.0f);
	g_lightProperties[1].shininess = 10.0f;
	g_lightProperties[1].attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
	g_lightProperties[1].cutoffAngle = -1.0f;
	g_lightProperties[1].direction = glm::vec3(0.0f, -1.0f, 0.0f);
	g_lightProperties[1].spotlight = 0.0f; 

	g_lightProperties[2].position = glm::vec4(0.0f, 1.3f, 0.0f, 1.0f);
	g_lightProperties[2].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_lightProperties[2].diffuse = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
	g_lightProperties[2].specular = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
	g_lightProperties[2].shininess = 10.0f;
	g_lightProperties[2].attenuation = glm::vec3(1.0f, 0.0f, 0.0f);
	g_lightProperties[2].cutoffAngle = 20.0f;
	g_lightProperties[2].direction = glm::vec3(0.0f, -1.0f, 0.0f);
	g_lightProperties[2].spotlight = 1.0f; 

	//position for sphere light
	sphereLightMovement [0] = 1.9f; 
	sphereLightMovement [1] = 1.4f; 
	sphereLightMovement [2] = 1.9f; 

	//position for cube light
	cubeLightMovement [0] = -1.94f; 
	cubeLightMovement [1] = 0.05f; 
	cubeLightMovement [2] = -1.94f; 


	//Material properties for table
	g_materialProperties[0].ambient = glm::vec4(0.7f, 0.4f, 1.0f, 1.0f);
	g_materialProperties[0].diffuse = glm::vec4(0.6f, 0.7f, 0.2f, 1.0f);
	g_materialProperties[0].specular = glm::vec4(1.0f, 0.7f, 0.7f, 1.0f);

	//Material properties for wall (front and back) 
	g_materialProperties[1].ambient = glm::vec4(0.7f, 0.3f, 0.3f, 1.0f);
	g_materialProperties[1].diffuse = glm::vec4(0.3f, 0.2f, 0.8f, 1.0f);
	g_materialProperties[1].specular = glm::vec4(0.5f, 0.7f, 0.8f, 1.0f);

	//Material properties for wall (left and right) 
	g_materialProperties[2].ambient = glm::vec4(0.3f, 0.4f, 0.1f, 1.0f);
	g_materialProperties[2].diffuse = glm::vec4(0.8f, 0.7f, 0.3f, 1.0f);
	g_materialProperties[2].specular = glm::vec4(0.5f, 0.8f, 0.4f, 1.0f);

	//Material properties for wall (Floor) 
	g_materialProperties[3].ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	g_materialProperties[3].diffuse = glm::vec4(0.8f, 1.0f, 0.2f, 1.0f);
	g_materialProperties[3].specular = glm::vec4(1.0f, 0.2f, 0.7f, 1.0f);

	//Material properties for wall (Ceiling) 
	g_materialProperties[4].ambient = glm::vec4(0.4f, 0.8f, 1.0f, 1.0f);
	g_materialProperties[4].diffuse = glm::vec4(0.1f, 0.5f, 0.8f, 1.0f);
	g_materialProperties[4].specular = glm::vec4(0.4f, 0.5f, 1.0f, 1.0f);

	//Material properties for sphere light
	g_materialProperties[5].ambient = glm::vec4(0.4f, 0.3f, 0.5f, 1.0f);
	g_materialProperties[5].diffuse = glm::vec4(0.3f, 0.7f, 0.5f, 1.0f);
	g_materialProperties[5].specular = glm::vec4(0.4f, 0.2f, 0.5f, 1.0f);

	//Material properties for chair 
	g_materialProperties[6].ambient = glm::vec4(0.4f, 0.3f, 0.7f, 1.0f);
	g_materialProperties[6].diffuse = glm::vec4(0.2f, 0.3f, 0.7f, 1.0f);
	g_materialProperties[6].specular = glm::vec4(0.2f, 0.7f, 0.8f, 1.0f);

	//Material properties for wuson ornament 
	g_materialProperties[7].ambient = glm::vec4(0.4f, 0.8f, 0.3f, 1.0f);
	g_materialProperties[7].diffuse = glm::vec4(0.8f, 0.6f, 0.1f, 1.0f);
	g_materialProperties[7].specular = glm::vec4(0.4f, 0.2f, 0.8f, 1.0f);

	//Material properties for suzanne ornament 
	g_materialProperties[8].ambient = glm::vec4(0.7f, 0.3f, 0.9f, 1.0f);
	g_materialProperties[8].diffuse = glm::vec4(0.2f, 0.4f, 0.6f, 1.0f);
	g_materialProperties[8].specular = glm::vec4(0.4f, 0.6f, 0.8f, 1.0f);

	//Material properties for cube light
	g_materialProperties[9].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_materialProperties[9].diffuse = glm::vec4(0.5f, 0.8f, 0.8f, 1.0f);
	g_materialProperties[9].specular = glm::vec4(1.0f, 0.0f, 0.8f, 1.0f);

	//Material properties for spotlight
	g_materialProperties[10].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_materialProperties[10].diffuse = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
	g_materialProperties[10].specular = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);

	// generate identifier for VBOs and copy data to GPU
	glGenBuffers(6, g_VBO);
	//Loading Cube
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_numberOfVertices[0], g_pMeshVertices[0], GL_STATIC_DRAW);

	//Loading Wall
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

	//Loading Sphere
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_numberOfVertices[1], g_pMeshVertices[1], GL_STATIC_DRAW);

	//Loading Wuson
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_numberOfVertices[2], g_pMeshVertices[2], GL_STATIC_DRAW);

	//Loading suzanne
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*g_numberOfVertices[3], g_pMeshVertices[3], GL_STATIC_DRAW);

	//===============================================================================

	// generate identifier for IBO and copy data to GPU
	glGenBuffers(5, g_IBO);

	//Loading Cube
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)* 3 * g_numberOfFaces[0], g_pMeshIndices[0], GL_STATIC_DRAW);

	//Loading Sphere
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)* 3 * g_numberOfFaces[1], g_pMeshIndices[1], GL_STATIC_DRAW);

	//Loading Wuson
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)* 3 * g_numberOfFaces[2], g_pMeshIndices[2], GL_STATIC_DRAW);

	//Loading suzanne
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)* 3 * g_numberOfFaces[3], g_pMeshIndices[3], GL_STATIC_DRAW);

	//===============================================================================

	// generate identifiers for VAO
	glGenVertexArrays(6, g_VAO);

	//Cube
	glBindVertexArray(g_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[0]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	//==================================================

	//Front Back wall 
	glBindVertexArray (g_VAO [1]); 
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[1]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	//==================================================

	//Left Right wall
	glBindVertexArray (g_VAO [2]); 
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	//===================================================

	//Sphere
	glBindVertexArray(g_VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[3]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[1]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	//===================================================

	//Wuson
	glBindVertexArray(g_VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[4]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[2]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);

	//===================================================

	//suzanne
	glBindVertexArray(g_VAO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO[3]);
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(normalIndex);


}

static void moveLights () 
{
	static bool light1Left, light1Up, light2Left, light2Up; 

	if (g_lightProperties[0].position[0] >= 2.0f) 
		light1Left = true; 
	else if (g_lightProperties [0]. position[0] <= -2.0f) 
		light1Left = false; 

	if (g_lightProperties[0] .position [2] >= 2.0f) 
		light1Up = true; 
	else if (g_lightProperties [0].position[2] <= -2.0f) 
		light1Up = false; 


	if (light1Left && light1Up)			//bottom right
		{
			g_lightProperties [0]. position[0] -= 0.1f;

			if (sphereLightMovement[0] > -1.94f) 
				sphereLightMovement[0] -= 0.1f;
		}
	else if (!light1Left && light1Up) // bottom left
		{
			g_lightProperties [0].position [2] -= 0.1f;

			if (sphereLightMovement[2] > -1.94f)
				sphereLightMovement[2] -= 0.1f;
		}
	else if (!light1Left && !light1Up) // top left
		{
			g_lightProperties [0]. position[0] += 0.1f;

			if (sphereLightMovement[0] < 1.94f)
				sphereLightMovement[0] += 0.1f;
		}
	else if (light1Left && !light1Up) //top right
		{
			g_lightProperties [0].position [2] += 0.1f; 
			
			if (sphereLightMovement[2] < 1.94f)
				sphereLightMovement[2] += 0.1f;
		}


	if (g_lightProperties[1].position[0] >= 2.0f) 
		light2Left = true; 
	else if (g_lightProperties [1]. position[0] <= -2.0f) 
		light2Left = false; 

	if (g_lightProperties[1] .position [2] >= 2.0f) 
		light2Up = true; 
	else if (g_lightProperties [1].position[2] <= -2.0f) 
		light2Up = false; 

	if (light2Left && light2Up)			//bottom right
		{
			g_lightProperties [1]. position[0] -= 0.1f;

			if (cubeLightMovement[0] > -1.9f) 
				cubeLightMovement[0] -= 0.1f;
		}
	else if (!light2Left && light2Up) // bottom left
		{
			g_lightProperties [1].position [2] -= 0.1f;

			if (cubeLightMovement[2] > -1.9f)
				cubeLightMovement[2] -= 0.1f;
		}
	else if (!light2Left && !light2Up) // top left
		{
			g_lightProperties [1]. position[0] += 0.1f;

			if (cubeLightMovement[0] < 1.9f)
				cubeLightMovement[0] += 0.1f;
		}
	else if (light2Left && !light2Up) //top right
		{
			g_lightProperties [1].position [2] += 0.1f; 
			
			if (cubeLightMovement[2] < 1.9f)
				cubeLightMovement[2] += 0.1f;
		}
		

}

static void discoSpot () 
{
	double temp; 
	float tempFloat; 

	srand (time (NULL)); 
	
	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].ambient[0] = tempFloat;
	g_materialProperties[10].ambient [0] = tempFloat; 
	
	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].ambient[1] = tempFloat;
	g_materialProperties[10].ambient [1] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].ambient[2] = tempFloat;
	g_materialProperties[10].ambient [2] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].diffuse[0] = tempFloat;
	g_materialProperties[10].diffuse [0] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].diffuse[1] = tempFloat;
	g_materialProperties[10].diffuse [1] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].diffuse[2] = tempFloat;
	g_materialProperties[10].diffuse [2] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].specular[0] = tempFloat;
	g_materialProperties[10].specular [0] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].specular[1] = tempFloat;
	g_materialProperties[10].specular [1] = tempFloat; 

	temp = rand () % 10;
	tempFloat = temp / 10;
	g_lightProperties[2].specular[2] = tempFloat;
	g_materialProperties[10].specular [2] = tempFloat; 

	float direction; 

	direction = rand () %7; 
	tempFloat = direction / 10;
	tempFloat += -0.3f;

	g_lightProperties[2].direction[0] = tempFloat; 

	direction = rand () % 7; 
	tempFloat = direction / 10;
	tempFloat += -0.3f;

	g_lightProperties[2].direction[2] = tempFloat; 


}

static void resetSpot () 
{
	g_lightProperties[2].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_lightProperties[2].diffuse = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
	g_lightProperties[2].specular = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
	g_lightProperties[2].direction = glm::vec3(0.0f, -1.0f, 0.0f);

	g_materialProperties[10].ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	g_materialProperties[10].diffuse = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
	g_materialProperties[10].specular = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);

}

static void render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear colour buffer and depth buffer

	glUseProgram(g_shaderProgramID);	// use the shaders associated with the shader program

	// ================================ Drawing Table ====================================
	glBindVertexArray(g_VAO[0]);
	glm::mat4 MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix [0];

	// pass the modelViewProjection matrix to the shader
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[0][0][0]);
	glUniform3fv(g_viewPointIndex, 1, &g_viewPoint[0]);

	vec4 temp (0.0f, 0.0f, 0.0f, 0.0f); 

	if (lightOn[0] ) 
		{
			glUniform4fv(g_lightPositionIndex[0], 1, &g_lightProperties[0].position[0]);
			glUniform4fv(g_lightAmbientIndex[0], 1, &g_lightProperties[0].ambient[0]);
			glUniform4fv(g_lightDiffuseIndex[0], 1, &g_lightProperties[0].diffuse[0]);
			glUniform4fv(g_lightSpecularIndex[0], 1, &g_lightProperties[0].specular[0]);
			glUniform1fv(g_lightShininessIndex[0], 1, &g_lightProperties[0].shininess);
			glUniform3fv(g_lightAttenuationIndex[0], 1, &g_lightProperties[0].attenuation[0]);
			glUniform1fv(g_lightCutoffAngleIndex[0], 1, &g_lightProperties[0].cutoffAngle); 
			glUniform3fv(g_lightDirectionIndex[0], 1, &g_lightProperties[0].direction[0]);
			glUniform1fv(g_lightSpotlightIndex[0], 1, &g_lightProperties[0].spotlight);
		}
	else 
		{


			glUniform4fv(g_lightPositionIndex[0], 1, &temp[0]);
			glUniform4fv(g_lightAmbientIndex[0], 1, &temp[0]);
			glUniform4fv(g_lightDiffuseIndex[0], 1, &temp[0]);
			glUniform4fv(g_lightSpecularIndex[0], 1, &temp[0]);
			glUniform1fv(g_lightShininessIndex[0], 1, &temp[0]);
			glUniform3fv(g_lightAttenuationIndex[0], 1, &temp[0]);
			glUniform1fv(g_lightCutoffAngleIndex[0], 1, &temp[0]);
			glUniform3fv(g_lightDirectionIndex[0], 1, &temp[0]);
			glUniform1fv(g_lightSpotlightIndex[0], 1, &temp[0]);

		}

	if (lightOn[1] ) 
		{
			glUniform4fv(g_lightPositionIndex[1], 1, &g_lightProperties[1].position[0]);
			glUniform4fv(g_lightAmbientIndex[1], 1, &g_lightProperties[1].ambient[0]);
			glUniform4fv(g_lightDiffuseIndex[1], 1, &g_lightProperties[1].diffuse[0]);
			glUniform4fv(g_lightSpecularIndex[1], 1, &g_lightProperties[1].specular[0]);
			glUniform1fv(g_lightShininessIndex[1], 1, &g_lightProperties[1].shininess);
			glUniform3fv(g_lightAttenuationIndex[1], 1, &g_lightProperties[1].attenuation[0]);
			glUniform1fv(g_lightCutoffAngleIndex[1], 1, &g_lightProperties[1].cutoffAngle); 
			glUniform3fv(g_lightDirectionIndex[1], 1, &g_lightProperties[1].direction[0]);
			glUniform1fv(g_lightSpotlightIndex[1], 1, &g_lightProperties[1].spotlight);

		}

	else
		{
			glUniform4fv(g_lightPositionIndex[1], 1, &temp[0]);
			glUniform4fv(g_lightAmbientIndex[1], 1, &temp[0]);
			glUniform4fv(g_lightDiffuseIndex[1], 1, &temp[0]);
			glUniform4fv(g_lightSpecularIndex[1], 1, &temp[0]);
			glUniform1fv(g_lightShininessIndex[1], 1, &temp[0]);
			glUniform3fv(g_lightAttenuationIndex[1], 1, &temp[0]);
			glUniform1fv(g_lightCutoffAngleIndex[1], 1, &temp[0]);
			glUniform3fv(g_lightDirectionIndex[1], 1, &temp[0]);
			glUniform1fv(g_lightSpotlightIndex[1], 1, &temp[0]);
		}

	if (lightOn[2] ) 
		{
			glUniform4fv(g_lightPositionIndex[2], 1, &g_lightProperties[2].position[0]);
			glUniform4fv(g_lightAmbientIndex[2], 1, &g_lightProperties[2].ambient[0]);
			glUniform4fv(g_lightDiffuseIndex[2], 1, &g_lightProperties[2].diffuse[0]);
			glUniform4fv(g_lightSpecularIndex[2], 1, &g_lightProperties[2].specular[0]);
			glUniform1fv(g_lightShininessIndex[2], 1, &g_lightProperties[2].shininess);
			glUniform3fv(g_lightAttenuationIndex[2], 1, &g_lightProperties[2].attenuation[0]);
			glUniform1fv(g_lightCutoffAngleIndex[2], 1, &g_lightProperties[2].cutoffAngle); 
			glUniform3fv(g_lightDirectionIndex[2], 1, &g_lightProperties[2].direction[0]);
			glUniform1fv(g_lightSpotlightIndex[2], 1, &g_lightProperties[2].spotlight);
		}

	else
		{
			glUniform4fv(g_lightPositionIndex[2], 1, &temp[0]);
			glUniform4fv(g_lightAmbientIndex[2], 1, &temp[0]);
			glUniform4fv(g_lightDiffuseIndex[2], 1, &temp[0]);
			glUniform4fv(g_lightSpecularIndex[2], 1, &temp[0]);
			glUniform1fv(g_lightShininessIndex[2], 1, &temp[0]);
			glUniform3fv(g_lightAttenuationIndex[2], 1, &temp[0]);
			glUniform1fv(g_lightCutoffAngleIndex[2], 1, &temp[0]);
			glUniform3fv(g_lightDirectionIndex[2], 1, &temp[0]);
			glUniform1fv(g_lightSpotlightIndex[2], 1, &temp[0]);


		}

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[0].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[0].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[0].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[0])*3, GL_UNSIGNED_INT, 0);	// display the vertices based on their indices and primitive type


	// ================================ Drawing Cube Light ====================================

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix [2];

	// pass the modelViewProjection matrix to the shader
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[2][0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[9].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[9].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[9].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[0])*3, GL_UNSIGNED_INT, 0);

	// ================================ Drawing Chair 1 ====================================

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix [3];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[3][0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[6].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[6].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[6].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[0])*3, GL_UNSIGNED_INT, 0);

	// ================================ Drawing Chair 2 ====================================

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix [4];

	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[4][0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[6].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[6].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[6].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[0])*3, GL_UNSIGNED_INT, 0);

	// ==============================================

	mat4 position; 

	glBindVertexArray(g_VAO[1]);

	// Changing material properties
	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[1].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[1].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[1].specular[0]);

	// ================================ Drawing Back Wall ====================================
	position = glm::translate (glm:: vec3 (0.0f, 0.0f, -2.0f))
			* glm::scale (glm :: vec3 (3.0f, 3.0f, 3.0f)); 

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * position;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// ================================ Drawing Front Wall ====================================
	position = glm::translate (glm:: vec3 (0.0f, 0.0f, 2.0f))
			* glm::scale (glm :: vec3 (3.0f, 3.0f, 3.0f)); 

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * position;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// ================================ Drawing Right Wall ==================================== 
	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[2].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[2].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[2].specular[0]);

	position = glm :: rotate (glm::radians (90.0f), (glm :: vec3 (0.0f, 1.0f, 0.0f))) 
			* glm::translate (glm:: vec3 (0.0f, 0.0f, 2.0f))
			* glm::scale (glm :: vec3 (3.0f, 3.0f, 3.0f)); 
			

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * position;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// ================================ Drawing Left Wall ====================================
	position = glm :: rotate (glm::radians (90.0f), (glm :: vec3 (0.0f, 1.0f, 0.0f))) 
			* glm::translate (glm:: vec3 (0.0f, 0.0f, -2.0f))
			* glm::scale (glm :: vec3 (3.0f, 3.0f, 3.0f)); 
			

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * position;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// ================================ Drawing Floor ====================================

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[3].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[3].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[3].specular[0]);

	position = glm :: rotate (glm::radians (90.0f), (glm :: vec3 (1.0f, 0.0f, 0.0f))) 
			* glm::translate (glm:: vec3 (0.0f, -2.0f, 0.0f))
			* glm::scale (glm :: vec3 (3.0f, 8.0f, 3.0f)); 
			

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * position;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// ================================ Drawing Ceiling ====================================

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[4].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[4].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[4].specular[0]);

	position = glm :: rotate (glm::radians (90.0f), (glm :: vec3 (1.0f, 0.0f, 0.0f))) 
			* glm::translate (glm:: vec3 (0.0f, -2.0f, -1.5f))
			* glm::scale (glm :: vec3 (3.0f, 8.0f, 3.0f)); 
			

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * position;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// ================================ Drawing Sphere Light ====================================

	glBindVertexArray(g_VAO[3]);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[1];
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[1][0][0]);
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[5].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[5].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[5].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[1])*3, GL_UNSIGNED_INT, 0);

	// ================================ Drawing Spotlight Light ====================================

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[7];
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[7][0][0]);
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[10].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[10].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[10].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[1])*3, GL_UNSIGNED_INT, 0);

	// ================================ Drawing Wuson Ornament ====================================

	glBindVertexArray(g_VAO[4]);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[5];
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[5][0][0]);
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[7].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[7].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[7].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[2])*3, GL_UNSIGNED_INT, 0);	

	// ================================ Drawing suzanne Ornament ====================================

	glBindVertexArray(g_VAO[5]);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[6];
	glUniformMatrix4fv(g_M_Index, 1, GL_FALSE, &g_modelMatrix[6][0][0]);
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);

	glUniform4fv(g_materialAmbientIndex, 1, &g_materialProperties[8].ambient[0]);
	glUniform4fv(g_materialDiffuseIndex, 1, &g_materialProperties[8].diffuse[0]);
	glUniform4fv(g_materialSpecularIndex, 1, &g_materialProperties[8].specular[0]);

	glDrawElements(GL_TRIANGLES, (g_numberOfFaces[3])*3, GL_UNSIGNED_INT, 0);	


	glFlush();	// flush the pipeline
}

static void update_scene()
{
	static bool up; 

	if (discoMode) 
	{

		if (dance >= 0.5f)
			up = false; 
		else if (dance <= 0.3f ) 
			up = true; 

		danceRotate += 1.0f;

		moveLights();  
		discoSpot (); 
	}

	if (up && discoMode) 
		dance += 0.01f; 
	else if (!up && discoMode) 
		dance -= 0.01f;

	else if (!discoMode) 
	{
		if (dance > 0.3f) 
			dance -= 0.01f;

		resetSpot (); 
	}

	//Table
	g_modelMatrix[0] = glm::translate (glm:: vec3 (0.0f, 0.15f, 0.0f))
				* glm::scale(glm::vec3(0.2f, 0.15f, 0.2f));

	//Sphere Light
	g_modelMatrix[1] = glm::translate (sphereLightMovement)
				* glm::scale (glm::vec3 (0.1f, 0.1f, 0.1f)); 

	//Cube Light
	g_modelMatrix[2] = glm::translate (cubeLightMovement)
				* glm::scale (glm::vec3 (0.05f, 0.05f, 0.05f)); 

	//Chair 1
	g_modelMatrix[3] = glm::translate (glm:: vec3 (-0.3f, 0.1f, 0.0f))
				* glm::scale (glm::vec3 (0.05f, 0.1f, 0.05f)); 

	//Chair 2
	g_modelMatrix[4] = glm::translate (glm:: vec3 (0.3f, 0.1f, 0.0f))
				* glm::scale (glm::vec3 (0.05f, 0.1f, 0.05f)); 

	//Wuson Ornament
	g_modelMatrix[5] = glm::translate (glm:: vec3 (0.15f, dance, 0.0f))
				* glm::rotate(glm::radians (danceRotate) , glm :: vec3 (0.0f, 1.0f, 0.0f))
				* glm::scale (glm::vec3 (0.05f, 0.05f, 0.05f)); 

	//suzanne Ornament
	g_modelMatrix[6] = glm::translate (glm:: vec3 (0.0f, 0.05f, 0.0f))
				* glm::translate (glm:: vec3 (-0.10f, dance, 0.0f))
				* glm::rotate(glm::radians (danceRotate) , glm :: vec3 (0.0f, 1.0f, 0.0f))
				* glm::scale (glm::vec3 (0.05f, 0.05f, 0.05f)); 

	//Spotlight
	g_modelMatrix[7] = glm::translate (glm:: vec3 (0.0f, 1.3f, 0.0f))
				* glm::scale (glm::vec3 (0.1f, 0.1f, 0.1f)); 
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

	else if (key == GLFW_KEY_P && action == GLFW_PRESS) 
	{
		if (discoMode) 
		{
			discoMode = false; 
		}

		else
		{
			discoMode = true; 
		}
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
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Assignment 3", NULL, NULL);

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

	TwAddVarRW(TweakBar, "Light 1 On", TW_TYPE_BOOLCPP, &lightOn[0], " group='Light 1 (Sphere)' ");
	
	TwAddVarRW(TweakBar, "Light 1 Ambient R", TW_TYPE_FLOAT, &g_lightProperties[0].ambient[0], " group='Light 1 (Sphere)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 1 Ambient G", TW_TYPE_FLOAT,&g_lightProperties[0].ambient[1], " group='Light 1 (Sphere)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 1 Ambient B", TW_TYPE_FLOAT, &g_lightProperties[0].ambient[2], " group='Light 1 (Sphere)' min=0.0 max=1.0 step=0.05 ");

	TwAddSeparator(TweakBar, NULL, " group='Light 1 (Sphere)'");

	TwAddVarRW(TweakBar, "Light 1 Diffuse R", TW_TYPE_FLOAT, &g_lightProperties[0].diffuse[0], " group='Light 1 (Sphere)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 1 Diffuse G", TW_TYPE_FLOAT, &g_lightProperties[0].diffuse[1], " group='Light 1 (Sphere)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 1 Diffuse B", TW_TYPE_FLOAT, &g_lightProperties[0].diffuse[2], " group='Light 1 (Sphere)' min=0.0 max=1.0 step=0.05 ");

	TwAddSeparator(TweakBar, NULL, " group='Light 1 (Sphere)'");

	TwAddVarRW(TweakBar, "Light 1 Specular R", TW_TYPE_FLOAT, &g_lightProperties[0].specular[0], " group='Light 1 (Sphere)' min=-0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 1 Specular G", TW_TYPE_FLOAT, &g_lightProperties[0].specular[1], " group='Light 1 (Sphere)' min=-0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 1 Specular B", TW_TYPE_FLOAT, &g_lightProperties[0].specular[2], " group='Light 1 (Sphere)' min=-0.0 max=1.0 step=0.05 ");

	TwAddSeparator(TweakBar, NULL, " group='Light 1 (Sphere)'");

	TwAddVarRW(TweakBar, "Light 1 Constant", TW_TYPE_FLOAT, &g_lightProperties[0].attenuation[0], " group='Light 1 (Sphere)' min=-0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "Light 1 Linear", TW_TYPE_FLOAT, &g_lightProperties[0].attenuation[1], " group='Light 1 (Sphere)' min=-0.0 max=1.0 step=0.001 ");
	TwAddVarRW(TweakBar, "Light 1 Quadratic", TW_TYPE_FLOAT, &g_lightProperties[0].attenuation[2], " group='Light 1 (Sphere)' min=-0.0 max=1.0 step=0.001 ");

	TwAddSeparator(TweakBar, NULL, NULL);

	//=============================================================================================================================

	TwAddVarRW(TweakBar, "Light 2 On", TW_TYPE_BOOLCPP, &lightOn[1], " group='Light 2 (Cube)' ");

	TwAddVarRW(TweakBar, "Light 2 Ambient R", TW_TYPE_FLOAT, &g_lightProperties[1].ambient[0], " group='Light 2 (Cube)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 2 Ambient G", TW_TYPE_FLOAT, &g_lightProperties[1].ambient[1], " group='Light 2 (Cube)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 2 Ambient B", TW_TYPE_FLOAT, &g_lightProperties[1].ambient[2], " group='Light 2 (Cube)' min=0.0 max=1.0 step=0.05 ");

	TwAddSeparator(TweakBar, NULL, " group='Light 2 (Cube)'");

	TwAddVarRW(TweakBar, "Light 2 Diffuse R", TW_TYPE_FLOAT, &g_lightProperties[1].diffuse[0], " group='Light 2 (Cube)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 2 Diffuse G", TW_TYPE_FLOAT, &g_lightProperties[1].diffuse[1], " group='Light 2 (Cube)' min=0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 2 Diffuse B", TW_TYPE_FLOAT, &g_lightProperties[1].diffuse[2], " group='Light 2 (Cube)' min=0.0 max=1.0 step=0.05 ");

	TwAddSeparator(TweakBar, NULL, " group='Light 2 (Cube)'");

	TwAddVarRW(TweakBar, "Light 2 Specular R", TW_TYPE_FLOAT, &g_lightProperties[1].specular[0], " group='Light 2 (Cube)' min=-0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 2 Specular G", TW_TYPE_FLOAT, &g_lightProperties[1].specular[1], " group='Light 2 (Cube)' min=-0.0 max=1.0 step=0.05 ");
	TwAddVarRW(TweakBar, "Light 2 Specular B", TW_TYPE_FLOAT, &g_lightProperties[1].specular[2], " group='Light 2 (Cube)' min=-0.0 max=1.0 step=0.05 ");

	TwAddSeparator(TweakBar, NULL, " group='Light 2 (Cube)'");

	TwAddVarRW(TweakBar, "Light 2 Constant", TW_TYPE_FLOAT, &g_lightProperties[1].attenuation[0], " group='Light 2 (Cube)' min=-0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "Light 2 Linear", TW_TYPE_FLOAT, &g_lightProperties[1].attenuation[1], " group='Light 2 (Cube)' min=-0.0 max=1.0 step=0.001 ");
	TwAddVarRW(TweakBar, "Light 2 Quadratic", TW_TYPE_FLOAT, &g_lightProperties[1].attenuation[2], " group='Light 2 (Cube)' min=-0.0 max=1.0 step=0.001 ");

	TwAddSeparator(TweakBar, NULL, NULL);

	//===========================================================================

	TwAddVarRW(TweakBar, "Spotlight On", TW_TYPE_BOOLCPP, &lightOn[2], " group='Spotlight (Sphere)' ");

	TwAddVarRW(TweakBar, "Cutoff Angle", TW_TYPE_FLOAT, &g_lightProperties[2].cutoffAngle, " group='Spotlight (Sphere)' min=-180.0 max=180.0 step=1.0 ");

	TwAddSeparator(TweakBar, NULL, " group='Spotlight (Sphere)' ");

	TwAddVarRW(TweakBar, "Spotlight Constant", TW_TYPE_FLOAT, &g_lightProperties[2].attenuation[0], " group='Spotlight (Sphere)' min=-0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "Spotlight Linear", TW_TYPE_FLOAT, &g_lightProperties[2].attenuation[1], " group='Spotlight (Sphere)' min=-0.0 max=1.0 step=0.01 ");
	TwAddVarRW(TweakBar, "Spotlight Quadratic", TW_TYPE_FLOAT, &g_lightProperties[2].attenuation[2], " group='Spotlight (Sphere)' min=-0.0 max=1.0 step=0.01 ");

	TwAddSeparator(TweakBar, NULL, " group='Spotlight (Sphere)' ");

	TwAddVarRO(TweakBar, "Direction: x", TW_TYPE_FLOAT, &g_lightProperties[2].direction[0], " group='Spotlight (Sphere)' min=-1.0 max=1.0 step=0.1");
	TwAddVarRO(TweakBar, "Direction: y", TW_TYPE_FLOAT, &g_lightProperties[2].direction[1], " group='Spotlight (Sphere)' min=-1.0 max=1.0 step=0.1");
	TwAddVarRO(TweakBar, "Direction: z", TW_TYPE_FLOAT, &g_lightProperties[2].direction[2], " group='Spotlight (Sphere)' min=-1.0 max=1.0 step=0.1");

	TwAddSeparator(TweakBar, NULL, NULL);

	//===========================================================================

	char s1 [3] = "P"; 
	TwAddVarRO(TweakBar, "Toggle Disco Mode", TW_TYPE_CSSTRING (sizeof (s1)), s1, "group = 'Help '");

	char s2 [6] = "ESC"; 
	TwAddVarRO(TweakBar, "Exit Program", TW_TYPE_CSSTRING (sizeof (s2)), s2, "group = 'Help '");

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

	glDeleteProgram(g_shaderProgramID);
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