#version 330 core

layout(location = 0) out vec4 FragmentColor;
in vec2 v_textCoord;

uniform sampler2D uTexture;
uniform vec3 uColor;
uniform int colorFlag; 




void main()
{
    if (colorFlag == 0)
    {
        vec4 textColor = texture(uTexture,v_textCoord);
        FragmentColor = textColor;
    
    }
    else if (colorFlag == 1)
        FragmentColor = vec4(uColor,1.0f);


 
}




