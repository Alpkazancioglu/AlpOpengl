#version 330 core

layout(location = 0) in vec2 position; 
layout(location = 1) in vec2 textCoord;




out vec2 v_textCoord;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 ratioMat;


void main(){
	
	v_textCoord = textCoord;
	vec2 newpos = position;
	
	

	gl_Position =  projection * view * model * vec4(newpos,0.0f,1.0f);

}