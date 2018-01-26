#include <cstdio>		
#include <iostream>
#include <cstddef>
#include <sstream> 
using namespace std;	

#define GLEW_STATIC		
#include <GLEW/glew.h>	
#include <GLFW/glfw3.h>	
#include <glm/glm.hpp>	
using namespace glm;	

#include "shader.h"
#include <AntTweakBar.h>

#define PI 3.14159265
#define MAX_SLICES 32
#define MIN_SLICES 8
#define MAX_VERTICES (MAX_SLICES+2)*3	
#define CIRCLE_RADIUS 0.25

bool poly = true; 
float g_backgroundColor[] = { 0.0f, 0.0f, 0.0f };

double xpos, ypos; 


GLfloat g_Vertices[] = {
	0.0f, 0.50f, 0.0f,	//point
	-0.25f, 0.75f, 0.0f,	//line point1
	0.25f, 0.75f, 0.0f,		//line point2
	-0.9f, -0.8f, 0.0f,		//triangle point1 (left)
	-0.6f, -0.8f, 0.0f,		//triangle point2 (right) 
	-0.75f, -0.4f, 0.0f,	//triangle point3 (top)
	0.75f, 0.95f, 0.0f,		//star point1 (top) 
	0.8f, 0.85f, 0.0f,		//star point2 (between top and right)
	0.9f, 0.8f, 0.0f,		//star point3 (right) 
	0.8f, 0.75f, 0.0f,		//star point4 (between right and bottom right) 
	0.825f, 0.6f, 0.0f,		//star point5 (bottom right)
	0.75f, 0.7f, 0.0f,		//star point6 (between bottom right and bottom left) 
	0.675f, 0.6f, 0.0f,		//star point7 (bottom left) 
	0.7f, 0.75f, 0.0f,		// star point8 (between bottom left and left) 
	0.6f, 0.8f, 0.0f,		//star point9 (left)
	0.7f, 0.85f, 0.0f,		//star point 10 (between left and top) 
	-0.25f, -0.5f, 0.0f,	//rect top left 
	0.25f, -0.5f, 0.0f,		//rect top right
	-0.25f, -0.75f, 0.0f,	//rect bottom left 
	0.25f, -0.75f, 0.0f		//rect bottom right
};

GLfloat g_vertexColors[] = {
	0.75f, 0.75f, 0.75f,	// point
	0.2f, 0.6f, 1.0f,		// line 
	0.2f, 0.6f, 1.0f,		
	1.0f, 0.5f, 0.5f,		// traingle
	1.0f, 0.5f, 0.5f,		
	1.0f, 0.5f, 0.5f,		
	0.4f, 0.75f, 0.75f,		// Star
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.4f, 0.75f, 0.75f,
	0.3f, 0.8f, 0.3f,		//Rectangle
	0.3f, 0.8f, 0.3f,
	0.3f, 0.8f, 0.3f,
	0.3f, 0.8f, 0.3f,

};

GLfloat circle [MAX_VERTICES] = 
{
	0.7f, -0.5f, 0.0f,
	0.7f, -0.5f, 0.0f,
};

GLfloat circleColor [MAX_VERTICES] = 
{
	0.8f, 0.5f, 0.8f,
	0.8f, 0.5f, 0.8f,
};

GLuint g_slices = MIN_SLICES;	

GLuint g_VBO [4] ;				
GLuint g_VAO [2];			
GLuint g_shaderProgramID = 0;		

void generate_circle()
{
	float angle = PI*2 / static_cast<float>(g_slices);	// used to generate x and y coordinates
	float scale_factor = static_cast<float>(1024/768);	// scale to make it a circle instead of an elipse
	int index = 0;	// vertex index

	circle[3] = (CIRCLE_RADIUS * scale_factor) + 0.7;	// set x coordinate of vertex 1

	// generate vertex coordinates for triangle fan
	for (int i = 2; i < g_slices+2; i++)
	{
		// multiply by 3 because a vertex has x, y, z coordinates
		index = i * 3;

		circle[index] = (CIRCLE_RADIUS * cos(angle) * scale_factor) + 0.7;
		circle[index + 1] = (CIRCLE_RADIUS * sin(angle)) - 0.5;
		circle[index + 2] = 0.0f;

		circleColor [index] = 0.8f;
		circleColor [index + 1] = 0.5f;
		circleColor [index + 2] = 0.8f;

		// update to next angle
		angle += PI*2 / static_cast<float>(g_slices);
	}
}

static void init () 
{
	glClearColor (0 ,0 ,0, 1); 

	g_shaderProgramID = loadShaders("SimpleVS.vert", "SimpleFS.frag");

	generate_circle(); 

	glGenBuffers (4, g_VBO); 
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[0]); 
	glBufferData (GL_ARRAY_BUFFER, sizeof (g_Vertices), g_Vertices, GL_STATIC_DRAW); 
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[1]); 
	glBufferData (GL_ARRAY_BUFFER, sizeof (g_vertexColors), g_vertexColors, GL_STATIC_DRAW); 

	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[2]); 
	glBufferData (GL_ARRAY_BUFFER, sizeof (circle), circle, GL_DYNAMIC_DRAW); 
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[3]); 
	glBufferData (GL_ARRAY_BUFFER, sizeof (circleColor), circleColor, GL_STATIC_DRAW); 

	glGenVertexArrays (2, g_VAO); 

	glBindVertexArray (g_VAO[0]); 
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[0]); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[1]); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	
	glBindVertexArray (g_VAO[1]); 
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[2]); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer (GL_ARRAY_BUFFER, g_VBO[3]); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

}

static void error_callback(int error, const char* description)
{
    cerr << description << endl;	
}

static void render_scene () 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glUseProgram(g_shaderProgramID);

	glLineWidth (5.0); 
	glPointSize (10); 

	glBindVertexArray (g_VAO[0]); 
	glDrawArrays (GL_POINTS, 0, 1); 
	glDrawArrays (GL_LINES, 1, 2); 
	glDrawArrays (GL_TRIANGLES, 3,3); 
	glDrawArrays (GL_LINE_LOOP, 6, 10); 
	glDrawArrays (GL_TRIANGLE_STRIP, 16, 4); 

	glBindVertexArray (g_VAO[1]);
	glDrawArrays (GL_TRIANGLE_FAN, 0, g_slices+2); 
	glFlush(); 
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// pass mouse data to tweak bar
	TwEventMousePosGLFW(xpos, ypos);
}

static void mouse_button_callback (GLFWwindow* window , int button , int action, int mod) 
{

	TwEventMouseButtonGLFW(button, action);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xpos, &ypos);
		cout << "Mouse Position\tX = " << xpos << " , Y = " << ypos << endl; 

	}
}

static void size_function(GLFWwindow* window, int width, int height) 
{
	string str;          
	ostringstream tempStr;  
	tempStr<< "Assignment 1 - "; 
	tempStr<<width;
	tempStr<< " X "; 
	tempStr<< height; 
	str=tempStr.str();      

	char *end = new char [str.length() + 1]; 
	strcpy (end, str.c_str()); 

	glViewport (0, 0, width, height); 
	
	glfwSetWindowTitle (window, end); 
}

static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static int counter = 0; 

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
		}

	else if (key == GLFW_KEY_B && action == GLFW_PRESS)
		{
		if (counter == 0) 
			{
				//black -> white
				glClearColor (1 ,1 ,1, 1);

				g_backgroundColor[0] = 1.0f;
				g_backgroundColor[1] = 1.0f;
				g_backgroundColor[2] = 1.0f;
			}
		else if (counter == 1) 
			{
				//white -> red
				glClearColor (1 ,0 ,0, 1); 

				g_backgroundColor[0] = 1.0f;
				g_backgroundColor[1] = 0.0f;
				g_backgroundColor[2] = 0.0f;
			}
		else if (counter == 2) 
			{
				//red -> green
				glClearColor (0 ,1 ,0, 1); 

				g_backgroundColor[0] = 0.0f;
				g_backgroundColor[1] = 1.0f;
				g_backgroundColor[2] = 0.0f;
			}
		else if (counter == 3) 
			{
				// green -> blue
				glClearColor (0 ,0 ,1, 1); 

				g_backgroundColor[0] = 0.0f;
				g_backgroundColor[1] = 0.0f;
				g_backgroundColor[2] = 1.0f;
			}
		else if (counter == 4) 
			{
				//blue -> black
				glClearColor (0 ,0 ,0, 1); 

				g_backgroundColor[0] = 0.0f;
				g_backgroundColor[1] = 0.0f;
				g_backgroundColor[2] = 0.0f;
			}

			counter ++; 
			if (counter > 4) 
				counter = 0; 
		}

	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		if (!poly)
		{
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			poly = true; 
		}

		else 
		{
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			poly = false; 
		}
	}

	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		if (g_slices < MAX_SLICES)
		{
			g_slices++;	// increment number of slices

			// generate vertices of triangle fan
			generate_circle();

			// bind and copy data to GPU
			glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (g_slices + 2), circle, GL_DYNAMIC_DRAW);

			glBindBuffer (GL_ARRAY_BUFFER, g_VBO[3]); 
			glBufferData (GL_ARRAY_BUFFER, sizeof(float) * 3 * (g_slices + 2), circleColor, GL_STATIC_DRAW); 
			
		}
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (g_slices > MIN_SLICES)
		{
			g_slices--;	// decrement number of slices

			// generate vertices of triangle fan
			generate_circle();

			// bind and copy data to GPU
			glBindBuffer(GL_ARRAY_BUFFER, g_VBO[2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * (g_slices + 2), circle, GL_DYNAMIC_DRAW);

			glBindBuffer (GL_ARRAY_BUFFER, g_VBO[3]); 
			glBufferData (GL_ARRAY_BUFFER, sizeof(float) * 3 * (g_slices + 2), circleColor, GL_STATIC_DRAW); 
		}
	}
	
}

int main () 
{
	GLFWwindow* window = NULL; 
	int width, height; 
	TwBar *TweakBar;

	glfwSetErrorCallback (error_callback); 

	if (!glfwInit ()) 
	{
		exit (EXIT_FAILURE); 
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow (1024,768, "Assignment 1 - 1024 X 768", NULL, NULL); 

	if(window == NULL)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent (window); 
	glfwSwapInterval (0); 

	if (glewInit() != GLEW_OK)
	{
		cerr << "Glew Initialization Failed" << endl;
		exit (EXIT_FAILURE); 
	}

	glfwSetKeyCallback (window, key_callback); 
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetMouseButtonCallback (window, mouse_button_callback); 
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	glfwSetFramebufferSizeCallback (window, size_function); 

	TwInit(TW_OPENGL_CORE, NULL);

	TwWindowSize(1024, 768);
	TwDefine(" TW_HELP visible=false ");	// disable help menu
	TwDefine(" GLOBAL fontsize=3 ");		// set large font size
	
	TweakBar = TwNewBar("Main");
	
	TwDefine(" Main label='My GUI' refresh=0.02 text=light size='300 350' ");
	TwAddVarRO(TweakBar, "Polygone", TW_TYPE_BOOLCPP, &poly, " group='Display' ");
	TwAddVarRO(TweakBar, "BgColor", TW_TYPE_COLOR3F, &g_backgroundColor, " label='Background Color' group='Display' opened=true ");

	TwAddSeparator (TweakBar , NULL , NULL); 

	TwAddVarRO(TweakBar, "X ", TW_TYPE_DOUBLE, &xpos, " group='Last Cursor Position' ");
	TwAddVarRO(TweakBar, "Y ", TW_TYPE_DOUBLE, &ypos, " group='Last Cursor Position' ");

	TwAddSeparator(TweakBar, NULL, NULL);

	char s1 [3] = "W"; 
	TwAddVarRO(TweakBar, "Toggle Polygone", TW_TYPE_CSSTRING (sizeof (s1)), s1, "group = 'Help '");

	char s2 [3] = "B"; 
	TwAddVarRO(TweakBar, "Toggle Bg Color", TW_TYPE_CSSTRING (sizeof (s2)), s2, "group = 'Help '");

	char s3 [3] = "Up"; 
	TwAddVarRO(TweakBar, "Increase triangle no", TW_TYPE_CSSTRING (sizeof (s3)), s3, "group = 'Help '");

	char s4 [5] = "Down"; 
	TwAddVarRO(TweakBar, "Decrease triangle no", TW_TYPE_CSSTRING (sizeof (s4)), s4, "group = 'Help '");

	char s5 [6] = "ESC"; 
	TwAddVarRO(TweakBar, "Exit Program", TW_TYPE_CSSTRING (sizeof (s5)), s5, "group = 'Help '");

	init(); 

	while (!glfwWindowShouldClose (window)) 
	{

		if (!poly)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else 
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		render_scene(); 

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		TwDraw();


		glfwSwapBuffers (window); 
		glfwPollEvents ();
		
	}

	glfwDestroyWindow (window); 

	glDeleteProgram (g_shaderProgramID); 
	glDeleteBuffers (4, g_VBO); 
	glDeleteVertexArrays (2, g_VAO); 

	TwTerminate();

	glfwTerminate(); 
}