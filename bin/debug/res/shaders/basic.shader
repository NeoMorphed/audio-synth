#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texId;

out vec2 vTexCoord;
out float vTexId;

uniform mat4 proj;
//uniform mat4 view;

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

uniform sampler2D uTextures[16];

void main()
{
    int index = int(vTexId);
    vec4 texColor = texture(uTextures[index], vTexCoord);
    color = texColor;
    //vec4(1.0f, 0, 0, 1.0f)
};