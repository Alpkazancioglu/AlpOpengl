#version 330 core
layout(location = 0) in vec2 position; 
layout(location = 1) in vec2 textCoord;




out vec2 v_textCoord;
uniform mat4 ratioMat;

void main()
{

	v_textCoord = textCoord;
	gl_Position = vec4(position*2.0f,0.0f,1.0f);
}