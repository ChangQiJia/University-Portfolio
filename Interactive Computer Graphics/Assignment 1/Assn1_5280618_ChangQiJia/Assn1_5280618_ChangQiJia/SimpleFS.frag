#version 330 core

in vec3 vColor;

// ouput data
out vec3 fColor;

void main()
{
	// set output color
	fColor = vColor;
}