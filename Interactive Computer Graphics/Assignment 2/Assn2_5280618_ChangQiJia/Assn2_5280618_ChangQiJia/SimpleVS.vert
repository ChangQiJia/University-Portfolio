#version 330 core

// input data (different for all executions of this shader)
in vec3 aPosition;
in vec3 aColor;


uniform mat4 uModelMatrix;
uniform mat3 colorModelMatrix; 

out vec3 vColor;

void main()
{
	gl_Position = uModelMatrix * vec4(aPosition, 1.0);
	
	vColor =  colorModelMatrix * aColor ;
}

