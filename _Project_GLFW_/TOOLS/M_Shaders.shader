#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;  
layout (location = 1) in vec2 TexCoord; 

uniform mat4 u_MVP;         // Model-View-Projection matrix

out vec2 TexCoord0;
// texture passed to the fragment shader

void main()
{    
    
    gl_Position = u_MVP * vec4(aPos, 1.0);
    TexCoord0 = TexCoord;
  
}

#shader fragment
#version 330 core

                      
in vec2 TexCoord0; // texture from the vertex shader

out vec4 FragColor; // Final output color

uniform sampler2D gSampler;
void main()
{
    
    FragColor = texture2D(gSampler,TexCoord0);
    
}
