#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 vTexCoord;

uniform mat4 proj;

void main()
{
    gl_Position = proj * position;
    vTexCoord = texCoord;
}  

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 vTexCoord;

uniform sampler2D text;
uniform vec4 text_color;

void main()
{    
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, vTexCoord).r);
    vec3 some_color  = sampled.rgb * text_color.rgb;
    color = vec4(some_color.rgb, sampled.a); 
    //color = vec4(1.0f, 1.0f, 1.0f, 1.0f); 
    //sampled * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //vec4(textColor, 1.0) * 
}  