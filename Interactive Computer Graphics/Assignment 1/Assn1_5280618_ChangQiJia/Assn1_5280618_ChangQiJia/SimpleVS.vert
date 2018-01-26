#version 330 core

// input data (different for all executions of this shader)
layout(location = 0 ) in vec3 aPosition;
layout(location = 1 ) in vec3 aColor;

//in vec3 aPosition; 
//in vec3 aColor;

out vec3 vColor;

void main()
{
	 gl_Position = vec4(aPosition, 1.0);
	 vColor = aColor;
}
