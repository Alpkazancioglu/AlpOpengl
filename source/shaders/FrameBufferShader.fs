#version 330 core

layout(location = 0) out vec4 FragmentColor;

in vec2 v_textCoord;
uniform sampler2D viewport;



void main()
{
    
    FragmentColor = vec4(texture(viewport,v_textCoord).rgb,1.0f);
    float average = 0.2126 * FragmentColor.r + 0.7152 * FragmentColor.g + 0.0722 * FragmentColor.b;
    FragmentColor = vec4(average, average, average, 1.0);
}