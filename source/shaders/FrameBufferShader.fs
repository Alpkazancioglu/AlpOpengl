#version 330 core

layout(location = 0) out vec4 FragmentColor;

in vec2 v_textCoord;
uniform sampler2D viewport;



void main()
{
    
    FragmentColor = vec4(texture(viewport,v_textCoord).rgb,1.0f);
    
}