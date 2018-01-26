#version 330 core

// input data (different for all executions of this shader)
in vec3 aPosition;
in vec3 aNormal;
in vec3 aTangent;
in vec2 aTexCoord;

// uniform input data
uniform mat4 uModelViewProjectionMatrix;
uniform mat4 uModelMatrix;

// output data (will be interpolated for each fragment)
out vec3 vPosition;
out vec3 vNormal;
out vec3 vTangent;
out vec2 vTexCoord;

void main()
{
	// set vertex position
    gl_Position = uModelViewProjectionMatrix * vec4(aPosition, 1.0);

	// world space
	vPosition = (uModelMatrix * vec4(aPosition, 1.0)).xyz;
	vNormal = (uModelMatrix * vec4(aNormal, 0.0)).xyz;
	vTangent = (uModelMatrix * vec4(aTangent, 0.0)).xyz;
	vTexCoord = aTexCoord;
}

