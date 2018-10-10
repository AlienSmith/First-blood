#shader fragment
#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;// uniform is like global variables 

void main()
{
	FragColor = ourColor;
}