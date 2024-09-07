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
	vec4 newPos = model * vec4(position,0.0f,1.0f);
	newPos.x += 0.5f;
	newPos.y -= 0.5f;
	

	gl_Position =  projection * view * vec4(newPos.xy,0.0f,1.0f);

}