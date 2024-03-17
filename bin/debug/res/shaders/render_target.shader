#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texId;
layout(location = 3) in vec4 color;

uniform mat4 proj;

out vec2 vTexCoord;
out float vTexId;

void main()
{
    gl_Position = proj * position;
    vTexCoord = texCoord;
    vTexId = texId;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;
in float vTexId;

uniform sampler2D samp;

void main()
{
    //vec4 texColor = texture(samp, vTexCoord);
    //color = texColor;
    color = vec4(1.0f, 0, 0, 1.0f);
    //vec4(1.0f, 0, 0, 1.0f)
};