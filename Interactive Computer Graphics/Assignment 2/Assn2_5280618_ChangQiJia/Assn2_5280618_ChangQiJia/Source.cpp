#include <cstdio>		
#include <iostream>
#include <cstddef>
#include <sstream> 
#include <ctime> 
using namespace std;	

#define GLEW_STATIC		
#include <GLEW/glew.h>	
#include <GLFW/glfw3.h>	
#include <glm/glm.hpp>	
#include <glm/gtx/transform.hpp>
using namespace glm;	

#include "shader.h"
#include "camera.h"
#include <AntTweakBar.h>

#define PI 3.14159265
#define MAX_SLICES 36
#define MIN_SLICES 36
#define MAX_VERTICES (MAX_SLICES+2)*3	
#define CIRCLE_RADIUS 0.5

struct Vertex 
{
	GLfloat position [3]; 
	GLfloat color [3]; 
};

Vertex g_vertices [] = 
{
	-0.5f, 0.5f, 0.5f,	// position
	1.0f, 0.0f, 1.0f,	// colour
	// vertex 2
	-0.5f, -0.5f, 0.5f,	// position
	1.0f, 0.0f, 0.0f,	// colour
	// vertex 3
	0.5f, 0.5f, 0.5f,	// position
	1.0f, 1.0f, 1.0f,	// colour
	// vertex 4
	0.5f, -0.5f, 0.5f,	// position
	1.0f, 1.0f, 0.0f,	// colour
	// vertex 5
	-0.5f, 0.5f, -0.5f,	// position
	0.0f, 0.0f, 1.0f,	// colour
	// vertex 6
	-0.5f, -0.5f, -0.5f,// position
	0.0f, 0.0f, 0.0f,	// colour
	// vertex 7
	0.5f, 0.5f, -0.5f,	// position
	0.0f, 1.0f, 1.0f,	// colour
	// vertex 8
	0.5f, -0.5f, -0.5f,	// position
	0.0f, 1.0f, 0.0f,	// colour
};

GLuint g_indices[] = {
	0, 1, 2,	// triangle 1
	2, 1, 3,	// triangle 2
	4, 5, 0,	// triangle 3
	0, 5, 1,	// ...
	2, 3, 6,
	6, 3, 7,
	4, 0, 6,
	6, 0, 2,
	1, 5, 3,
	3, 5, 7,
	5, 4, 7,
	7, 4, 6,	// triangle 12
};

GLfloat circle1 [MAX_VERTICES] ;

GLfloat circle2 [MAX_VERTICES] ;

GLfloat circle3 [MAX_VERTICES] ;

GLfloat circle4 [MAX_VERTICES] ;

GLfloat planetCircle [MAX_VERTICES] ;

GLfloat circleColor [MAX_VERTICES] ;

GLfloat planetColor [MAX_VERTICES] ;

mat3 baseColor (vec3 (1.0,0.0,0.0) , vec3 (0.0,1.0,0.0),vec3 (0.0,0.0,1.0)); 

mat3 newColor (vec3 (1.0,0.0,0.0) , vec3 (0.0,1.0,0.0),vec3 (0.0,0.0,1.0)); 

mat4 temp, temp1; 

GLuint g_IBO = 0;				
GLuint g_VBO[8];
GLuint g_VAO [6];
GLuint g_shaderProgramID = 0;
GLuint g_MVP_Index = 0;	
GLuint g_MVP_Color = 0;	
GLuint g_modelMatrixIndex = 0;
glm::mat4 g_modelMatrix [6];		// object's model matrix
glm::mat4 g_viewMatrix;			// view matrix
glm::mat4 g_projectionMatrix;	// projection matrix

GLfloat g_orbitSpeed [5];
GLfloat g_rotationSpeed[6] ;
bool animate = true; 
GLfloat size [6]; 
GLfloat orbit [5]; 
static GLfloat rotationAngle[6] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat orbitOffset [4]; 

Camera g_camera; 

GLuint g_slices = MIN_SLICES;	


static void error_callback(int error, const char* description)
{
    cerr << description << endl;	
}

void random_size (float sSize)
{
	srand (time(NULL)); 

	float max ; 

	sSize -= 0.2f; 

	// size of 1st planet
	int temp = sSize *10; 


	max = rand () % temp; 

	max /= 10 ; 

	if (max == 0) 
		max = 0.1f;
	if (max > size[0]) 
		max = size [0] - 0.1f; 

	size[1] = max;

	//size of 2nd planet
	temp = sSize *10; 

	max = rand () % temp; 

	max /= 10 ; 

	if (max == 0) 
		max = 0.1f;
	if (max > size[0]) 
		max = size [0] - 0.1f; 

	size[2] = max;

	//size of 3rd planet
	temp = sSize *10; 

	max = rand () % temp; 

	max /= 10 ; 

	if (max == 0) 
		max = 0.1f;
	if (max > size[0]) 
		max = size [0] - 0.1f; 

	size[3] = max;

	//size of 4th planet
	temp = sSize *10; 

	max = rand () % temp; 

	max /= 10 ; 

	if (max == 0) 
		max = 0.1f;
	if (max > size[0]) 
		max = size [0] - 0.1f; 

	size[4] = max;

	//size of 5th planet
	temp = sSize *10; 

	max = rand () % temp; 

	max /= 10 ; 

	if (max == 0) 
		max = 0.1f;
	if (max > size[0]) 
		max = size [0] - 0.1f; 

	size[5] = max;
}

void random_speed () 
{
	srand (time(NULL)); 

	//orbitspeed for planet 1
	float max; 

	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;

	g_orbitSpeed [0] = max; 

	//orbitspeed for planet 2
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;

	g_orbitSpeed [1] = max; 

	//orbitspeed for planet 3
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;

	g_orbitSpeed [2] = max; 

	//orbitspeed for planet 4 (moon for planet 3) 
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;

	g_orbitSpeed [3] = max; 

	//orbitspeed for planet 5
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;

	g_orbitSpeed [4] = max; 

	//rotation speed for sun 
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;
	g_rotationSpeed[0] = max; 

	//rotation speed for planet 1 
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;
	g_rotationSpeed[1] = max; 

	//rotation speed for planet 2
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;
	g_rotationSpeed[2] = max; 

	//rotation speed for planet 3 
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;
	g_rotationSpeed[3] = max; 

	//rotation speed for planet 4  (moon for planet 3) 
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;
	g_rotationSpeed[4] = max; 

	//rotation speed for planet 5 
	max = rand()% 10;
	max /= 10;

	if (max <= 0) 
		max = 0.1f;
	g_rotationSpeed[5] = max; 

}

void random_orbit () 
{
	srand (time(NULL)); 

	//orbit for planet 1
	float max; 
	int pos;

	max = rand()% 10;
	max /= 10;

	if (max < 1.05f) 
		max = 1.05f;
	else if ( max > 2.0f)
		max = 2.0f;

	orbit [0] = max; 

	max = rand()% 10;
	max /= 10;

	if (max < 0.05f) 
		max = 0.05f;
	else if ( max > 0.25f)
		max = 0.25f;

	pos = rand() % 2; 

	if (pos == 0) 
		max *= -1; 

	orbitOffset [0] = max; 

	//orbit for planet 2
	max = rand()% 10;
	max /= 10;

	if (max < 2.05f) 
		max = 2.05f;
	else if ( max > 3.0f)
		max = 3.0f;

	orbit [1] = max; 

	max = rand()% 10;
	max /= 10;

	if (max < 0.05f) 
		max = 0.05f;
	else if ( max > 0.25f)
		max = 0.25f;

	pos = rand() % 2; 

	if (pos == 0) 
		max *= -1; 

	orbitOffset [1] = max; 

	//orbit for planet 3
	max = rand()% 10;
	max /= 10;

	if (max < 3.05f) 
		max = 3.05f;
	else if ( max > 4.0f)
		max = 4.0f;

	orbit [2] = max;

	max = rand()% 10;
	max /= 10;

	if (max < 0.05f) 
		max = 0.05f;
	else if ( max > 0.25f)
		max = 0.25f;

	pos = rand() % 2; 

	if (pos == 0) 
		max *= -1; 

	orbitOffset [2] = max; 

	//orbit for planet 4 (moon for planet 3) 
	max = rand()% 10;
	max /= 10;

	if (max < 1.0f) 
		max = 1.0f;
	else if ( max > 1.5f)
		max = 1.5f;

	orbit [3] = max; 

	//orbit for planet 5
	max = rand()% 10;
	max /= 10;

	if (max < 4.05f) 
		max = 4.05f;
	else if ( max > 5.0f)
		max = 5.0f;

	orbit [4] = max; 

	max = rand()% 10;
	max /= 10;

	if (max < 0.05f) 
		max = 0.05f;
	else if ( max > 0.25f)
		max = 0.25f;

	pos = rand() % 2; 

	if (pos == 0) 
		max *= -1; 

	orbitOffset [3] = max; 
}

void generate_circle()
{
	float angle = PI*2 / static_cast<float>(g_slices);	// used to generate x and y coordinates
	float scale_factor = static_cast<float> (1024 / 768);	// scale to make it a circle instead of an elipse
	int index = 0;	// vertex index

	// generate vertex coordinates for triangle fan
	for (int i = 0; i < g_slices+2; i++)
	{
		// multiply by 3 because a vertex has x, y, z coordinates
		index = i * 3;

		circle1[index] = (orbit[0] * cos(angle) * scale_factor ) + orbitOffset[0];
		circle1[index + 1] = 0.0f;
		circle1[index + 2] = orbit[0] * sin(angle);

		circle2[index] = (orbit[1] * cos(angle) * scale_factor) + orbitOffset [1];
		circle2[index + 1] = 0.0f;
		circle2[index + 2] = orbit[1] * sin(angle);

		circle3[index] = (orbit[2] * cos(angle) * scale_factor) + orbitOffset[2];
		circle3[index + 1] = 0.0f;
		circle3[index + 2] = orbit[2] * sin(angle);

		circle4[index] = ((orbit[4] * cos(angle) * scale_factor)) + orbitOffset[3] ;
		circle4[index + 1] = (orbit[4] * sin(angle));
		circle4[index + 2] = 0.0f;
	
		circleColor [index] = 1.0f;
		circleColor [index + 1] = 0.0f;
		circleColor [index + 2] = 0.0f;

		// update to next angle
		angle += PI*2 / static_cast<float>(g_slices);
	}

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[1]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (circle1), circle1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (circle2), circle2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[3]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (circle3), circle3, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[4]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (circle4), circle4, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (circleColor), circleColor, GL_STATIC_DRAW);

}

void generate_planetOrbit(float size)
{
	srand (time(NULL)); 

	float angle = PI*2 / static_cast<float>(g_slices);	// used to generate x and y coordinates
	float scale_factor = static_cast<float> (1024 / 768);	// scale to make it a circle instead of an elipse
	int index = 0;	// vertex index

	// generate vertex coordinates for triangle fan
	for (int i = 0; i < g_slices+2; i++)
	{
		// multiply by 3 because a vertex has x, y, z coordinates
		index = i * 3;

		planetCircle[index] = (size * cos(angle) * scale_factor );
		planetCircle[index + 1] = 0.0f;
		planetCircle[index + 2] = size * sin(angle);

		float max; 

		max = rand()% 11;
		max /= 10;
		planetColor [index] = max;

		max = rand()% 11;
		max /= 10;
		planetColor [index + 1] = max;

		max = rand()% 11;
		max /= 10;
		planetColor [index + 2] = max;

		// update to next angle
		angle += PI*2 / static_cast<float>(g_slices);
	}

	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[6]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (planetCircle), planetCircle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[7]);
	glBufferData (GL_ARRAY_BUFFER, sizeof (planetColor), planetColor, GL_STATIC_DRAW);


}

static void init (GLFWwindow* window) 
{
	size[0] = 0.7f;

	glClearColor (0 ,0 ,0, 1); 

	glEnable(GL_DEPTH_TEST);	// enable depth buffer test

	g_shaderProgramID = loadShaders("SimpleVS.vert", "SimpleFS.frag");

	GLuint positionIndex = glGetAttribLocation(g_shaderProgramID, "aPosition");
	GLuint colorIndex = glGetAttribLocation(g_shaderProgramID, "aColor");
	g_MVP_Index = glGetUniformLocation(g_shaderProgramID, "uModelMatrix");
	g_MVP_Color = glGetUniformLocation(g_shaderProgramID, "colorModelMatrix");

	g_modelMatrix[0] = glm::mat4(1.0f);	
	g_modelMatrix[1] = glm::mat4(1.0f);	
	g_modelMatrix[2] = glm::mat4(1.0f);	
	g_modelMatrix[3] = glm::mat4(1.0f);	
	g_modelMatrix[4] = glm::mat4(1.0f);	
	g_modelMatrix[5] = glm::mat4(1.0f);		

	g_modelMatrix[0] *= glm::translate (glm::vec3 (0.0f, 0.0f, 0.0f)); 
	g_modelMatrix[0] *= glm::scale(glm::vec3(size [0], size [0], size [0]));
	random_size(size [0]) ; 
	random_speed();
	random_orbit ();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / height;

	g_camera.setViewMatrix(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	g_camera.setProjectionMatrix(glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f));
	
	glGenBuffers(8, g_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertices), g_vertices, GL_STATIC_DRAW);

	generate_circle(); 
	generate_planetOrbit(0.8); 

	glGenBuffers(1, &g_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);


	glGenVertexArrays(6, g_VAO);

	//======================================= Planets =======================================
	glBindVertexArray(g_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);

	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex);

	//======================================= Orbit for 1st Planet =======================================
	glBindVertexArray(g_VAO[1]);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[1]);	
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex); 

	//======================================= Orbit for 2nd Planet =======================================
	glBindVertexArray(g_VAO[2]);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);	
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex); 

	//======================================= Orbit for 3rd Planet =======================================
	glBindVertexArray(g_VAO[3]);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[3]);	
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex); 

	//======================================= Orbit for 4th Planet =======================================
	glBindVertexArray(g_VAO[4]);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[4]);	
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[5]);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex); 

	//==============================================================================
	glBindVertexArray(g_VAO[5]);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[6]);	
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO[7]);
	glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(positionIndex);	// enable vertex attributes
	glEnableVertexAttribArray(colorIndex); 

}

static void render_scene () 
{
	glm::mat4 MVP;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glUseProgram(g_shaderProgramID);
	glBindVertexArray(g_VAO[0]);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[0];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[1];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[2];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[3];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[4];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * g_modelMatrix[5];
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &newColor[0][0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glLineWidth (1); 

	//=======================================
	glBindVertexArray(g_VAO[1]);
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawArrays(GL_LINE_LOOP, 0, g_slices+2);

	//=======================================
	glBindVertexArray(g_VAO[2]);
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawArrays(GL_LINE_LOOP, 0, g_slices+2);

	//=======================================
	glBindVertexArray(g_VAO[3]);
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawArrays(GL_LINE_LOOP, 0, g_slices+2);

	//=======================================
	glBindVertexArray(g_VAO[4]);
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() ;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawArrays(GL_LINE_LOOP, 0, g_slices+2);

	glLineWidth (30); 

	//=======================================
	glBindVertexArray(g_VAO[5]);
	MVP = g_camera.getProjectionMatrix() * g_camera.getViewMatrix() * temp;
	glUniformMatrix4fv(g_MVP_Index, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix3fv(g_MVP_Color, 1, GL_TRUE, &baseColor[0][0]);
	glDrawArrays(GL_LINE_LOOP, 0, g_slices+2);

	glFlush(); 
}

static void update_scene()
{
	// static variables for rotation angles
	static float orbitAngle [5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float scaleFactor = 0.1; 
	static bool increment = false; 

	// update rotation angles
	orbitAngle[0] += g_orbitSpeed[0] * scaleFactor;
	orbitAngle[1] += g_orbitSpeed[1] * scaleFactor;
	orbitAngle[2] += g_orbitSpeed[2] * scaleFactor;
	orbitAngle[3] += g_orbitSpeed[3] * scaleFactor;
	orbitAngle[4] += g_orbitSpeed[4] * scaleFactor;

	rotationAngle[0] += g_rotationSpeed[0] * scaleFactor;
	rotationAngle[1] += g_rotationSpeed[1] * scaleFactor;
	rotationAngle[2] += g_rotationSpeed[2] * scaleFactor;
	rotationAngle[3] += g_rotationSpeed[3] * scaleFactor;
	rotationAngle[4] += g_rotationSpeed[4] * scaleFactor;
	rotationAngle[5] += g_rotationSpeed[5] * scaleFactor;

	// update model matrix
	g_modelMatrix[0] = glm::rotate(rotationAngle[0], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::scale(glm::vec3(size [0], size [0], size [0]));

	g_modelMatrix[1] =glm::translate(glm::vec3(orbitOffset[0], 0.0f, 0.0f)) 
					* glm::rotate(orbitAngle[0], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::translate(glm::vec3(orbit[0], 0.0f, 0.0f))
					* glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f))
					* glm::rotate(rotationAngle[1], glm::vec3(0.0f, 1.0f, 1.0f))
					* glm::scale(glm::vec3(size [1], size [1], size [1]));

	g_modelMatrix[2] = glm::translate(glm::vec3(orbitOffset[1], 0.0f, 0.0f)) 
					* glm::rotate(orbitAngle[1], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::translate(glm::vec3(orbit[1], 0.0f, 0.0f))
					* glm::rotate(rotationAngle[2], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::scale(glm::vec3(size [2], size [2], size [2]));

	g_modelMatrix[3] =glm::translate(glm::vec3(orbitOffset[2], 0.0f, 0.0f))  
					* glm::rotate(orbitAngle[2], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::translate(glm::vec3(orbit[2], 0.0f, 0.0f))
					* glm::rotate(rotationAngle[3], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::scale(glm::vec3(size [3], size [3], size [3]));

	g_modelMatrix[4] = g_modelMatrix[3]
					* glm::rotate(orbitAngle[3], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::translate(glm::vec3(orbit[3], 0.0f, 0.0f))
					* glm::rotate(rotationAngle[4], glm::vec3(0.0f, 1.0f, 0.0f))
					* glm::scale(glm::vec3(size [4], size [4], size [4]));

	g_modelMatrix[5] = glm::translate(glm::vec3(orbitOffset[3], 0.0f, 0.0f))  
					* glm::rotate(orbitAngle[4], glm::vec3(0.0f, 0.0f, 1.0f))
					* glm::translate(glm::vec3(orbit[4], 0.0f, 0.0f))
					* glm::rotate(rotationAngle[5], glm::vec3(0.0f, 0.0f, 1.0f))
					* glm::scale(glm::vec3(size [5], size [5], size [5]));

	temp = g_modelMatrix[2];

	if (newColor [0][0] && newColor [1][1] && newColor [2][2] <= 0.0) 
	{
		//increment
		increment = true; 
	}
	else if (newColor [0][0] && newColor [1][1] &&newColor [2][2] >= 1.0) 
	{
		//decrement 
		increment = false; 
	}

	if (increment) 
	{
		newColor [0][0] += 0.1; 
		newColor [1][1] += 0.1; 
		newColor [2][2] += 0.1; 
	}

	else 
	{
		newColor [0][0] -= 0.1; 
		newColor [1][1] -= 0.1; 
		newColor [2][2] -= 0.1; 
	}
	
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// variables to store mouse cursor coordinates
	static double previous_xpos = xpos;
	static double previous_ypos = ypos;
	double delta_x = xpos - previous_xpos;
	double delta_y = ypos - previous_ypos;

	// pass mouse movement to camera class
	g_camera.updateYaw(delta_x);
	g_camera.updatePitch(delta_y);

	// update previous mouse coordinates
	previous_xpos = xpos;
	previous_ypos = ypos;

	// pass mouse data to tweak bar
	TwEventMousePosGLFW(xpos, ypos);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// pass mouse data to tweak bar
	TwEventMouseButtonGLFW(button, action);
}

static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static int counter = 0; 
	static bool poly = false; 

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
		}

	else if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			random_size (size[0]); 
			random_speed ();
			random_orbit () ;
			generate_circle(); 
		}

	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (!animate)
		{
			animate = true; 
		}

		else 
		{
			animate = false; 
		}
	}

	else if (key == GLFW_KEY_1 && action == GLFW_PRESS) 
	{
		g_camera.setViewMatrix(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		g_camera.setPitch (0); 
	}

	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) 
	{
		g_camera.setViewMatrix(glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		g_camera.setPitch (275);  

	}

	else if (key == GLFW_KEY_B && action == GLFW_PRESS)
		{
		if (counter == 0) 
			{
				//black -> white
				glClearColor (1 ,1 ,1, 1); 
			}
		else if (counter == 1) 
			{
				//white -> red
				glClearColor (1 ,0 ,0, 1); 
			}
		else if (counter == 2) 
			{
				//red -> green
				glClearColor (0 ,1 ,0, 1); 
			}
		else if (counter == 3) 
			{
				// green -> blue
				glClearColor (0 ,0 ,1, 1); 
			}
		else if (counter == 4) 
			{
				//blue -> black
				glClearColor (0 ,0 ,0, 1); 
			}

			counter ++; 
			if (counter > 4) 
				counter = 0; 
		}
	
}

int main () 
{
	GLFWwindow* window = NULL; 
	TwBar *TweakBar;

	glfwSetErrorCallback (error_callback); 

	if (!glfwInit ()) 
	{
		exit (EXIT_FAILURE); 
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow (1024,768, "Assignment 2", NULL, NULL); 

	if(window == NULL)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent (window); 
	glfwSwapInterval (1); 

	if (glewInit() != GLEW_OK)
	{
		cerr << "Glew Initialization Failed" << endl;
		exit (EXIT_FAILURE); 
	}

	glfwSetKeyCallback (window, key_callback); 
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);

	TwInit(TW_OPENGL_CORE, NULL);

	TwWindowSize(1024, 768);
	TwDefine(" TW_HELP visible=false ");	// disable help menu
	TwDefine(" GLOBAL fontsize=3 ");		// set large font size
	
	TweakBar = TwNewBar("Main");
	TwDefine(" Main label='Help' refresh=0.02 text=light size='350 100' ");

	char s1 [3] = "R"; 
	TwAddVarRO(TweakBar, "Randomize Orbit, Size, Speed", TW_TYPE_CSSTRING (sizeof (s1)), s1, "");

	char s2 [3] = "P"; 
	TwAddVarRO(TweakBar, "Toggle Animation", TW_TYPE_CSSTRING (sizeof (s2)), s2, "");

	char s3 [6] = "ESC"; 
	TwAddVarRO(TweakBar, "Exit Program", TW_TYPE_CSSTRING (sizeof (s3)), s3, "");

	init(window); 
	
	float lastUpdateTime = glfwGetTime();
	float currentTime = lastUpdateTime;

	while (!glfwWindowShouldClose (window)) 
	{
		currentTime = glfwGetTime();
		
		if (currentTime - lastUpdateTime > 0.02)
		{
			if (animate) 
				update_scene();		

			g_camera.update(window); 

			render_scene(); 
			TwDraw();

			glfwSwapBuffers (window); 
			glfwPollEvents ();
			lastUpdateTime = currentTime;
		}
		
	}

	glfwDestroyWindow (window); 

	glDeleteProgram (g_shaderProgramID); 
	glDeleteBuffers(1, &g_IBO);
	glDeleteBuffers (1, g_VBO); 
	glDeleteVertexArrays (1, g_VAO); 

	TwTerminate();

	glfwTerminate(); 
}