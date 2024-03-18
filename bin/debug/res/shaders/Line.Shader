#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 proj;

void main()
{
    //vFragPos = vec3(model * vec4(position, 1.0f));
    gl_Position = proj * vec4(position, 1.0f);

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 tint_color;

void main()
{
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}