#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;  
layout (location = 1) in vec3 aColor; 

uniform mat4 u_MVP;         // Model-View-Projection matrix


out vec3 fragColor; // Color passed to the fragment shader

void main()
{    
    
    gl_Position = u_MVP * vec4(aPos, 1.0);
    
    fragColor = aColor;
}

#shader fragment
#version 330 core

in vec3 fragColor; // Color from the vertex shader
out vec4 FragColor; // Final output color

void main()
{
    
    FragColor = vec4(fragColor, 1.0);
}
//vec4(1.0, 0.0, 0.0, 1.0)