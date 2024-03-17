#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 VColor;
uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * position;
    VColor = color;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 VColor;

void main()
{
	
    color = vec4(1, 1, 1, 1);
    //vec4(1.0f, 0, 0, 1.0f)
};