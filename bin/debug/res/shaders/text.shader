#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 uv;
out vec3 frag_pos;

uniform mat4 proj;
uniform float time;

void main()
{
    //float temp = position.y + sin(1 + time) * 100;
    //vec4 new_pos = vec4(position.x, temp, position.zw);
    vec4 out_pos = proj * position;
    gl_Position = proj * position;
    uv = texCoord;
    frag_pos = out_pos.xyz;

}  

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 uv;
in vec3 frag_pos;

uniform float time;
uniform sampler2D text;
uniform vec4 text_color;

void main()
{    
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, uv).r);
    vec3 some_color  = sampled.rgb * text_color.rgb;
    //vec3 frag_inv = vec3(1.0f, 1.0f, 1.0f);//vec3(frag_pos.x - 1.0, frag_pos.y - 1.0, frag_pos.z - 1.0);
    //some_color = vec3(some_color.r * sin(uv.x * 10 + time), (some_color.g * frag_pos.y) * .1, some_color.b);
    color = vec4(some_color.rgb, sampled.a); 
    //color = vec4(1.0f, 1.0f, 1.0f, 1.0f); 
    //color = vec4(frag_pos.xy, 1.0f, 1.0f);
    //sampled * vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //vec4(textColor, 1.0) * 
}  