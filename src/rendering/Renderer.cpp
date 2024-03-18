#include "Renderer.h"
#include "core/ErrorCheck.h"
#include "core/Rectangle.h"
#include "core/Window.h"
#include "math/common_math.h"
#include "RenderTarget.h"
#include "Sprite.h"
#include "Shader.h"
#include "Vertex.h"
#include "core/ScopeTimer.h"


#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

#define INDICES_SIZE 240000

namespace Tactics
{
void fill_indices();

unsigned int vertex_buffer;
unsigned int index_buffer;
unsigned int vertex_array;
unsigned int immediate_vertex_buffer;
unsigned int immediate_vertex_array;
unsigned int true_type_text_vertex_buffer;
unsigned int true_type_text_vertex_array;
unsigned int line_vbo;
unsigned int line_vao;
const int maxQuads = 10000;
const int maxVertices = maxQuads * 4 * 10;
const int MAX_POINT_COUNT = 10000;
Vector3* line_points = (Vector3*)malloc(MAX_POINT_COUNT * sizeof(Vector3));
float* verticesAttribs = new float[maxVertices];
uint32_t* indices = new uint32_t[INDICES_SIZE];
int verticeCount = 0;
float z_index = 0;
bool batch_begun = false;
BmFont* default_font;
unsigned int camera_ubo;
std::vector<Sprite*> queued_sprites;
void init_renderer()
{

	immediate_vertex_buffer = create_vertex_buffer(nullptr, 42 * sizeof(float), GL_DYNAMIC_DRAW);
	GLCall(glGenVertexArrays(1, &immediate_vertex_array));
	GLCall(glBindVertexArray(immediate_vertex_array));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VtxPC), (const void*)offsetof(VtxPC, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VtxPC), (const void*)offsetof(VtxPC, color));

	line_vbo = create_vertex_buffer(NULL, sizeof(Vector3) * MAX_POINT_COUNT , GL_DYNAMIC_DRAW);
	GLCall(glGenVertexArrays(1, &line_vao));
	GLCall(glBindVertexArray(line_vao));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
	//glBindVertexArray(0);

	true_type_text_vertex_buffer = create_vertex_buffer(nullptr, 24 * sizeof(float), GL_DYNAMIC_DRAW);
	GLCall(glGenVertexArrays(1, &true_type_text_vertex_array));
	GLCall(glBindVertexArray(true_type_text_vertex_array));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VtxPT), (const void*)offsetof(VtxPT, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VtxPT), (const void*)offsetof(VtxPT, tex_coords));
	
	vertex_buffer = create_vertex_buffer(nullptr, maxVertices * sizeof(float), GL_DYNAMIC_DRAW);
	GLCall(glGenVertexArrays(1, &vertex_array));
	GLCall(glBindVertexArray(vertex_array));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexId));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

	fill_indices();
	index_buffer = create_index_buffer(indices, INDICES_SIZE, GL_STATIC_DRAW);
	init_camera_ubo();
}

void draw_sprite(Texture* texture, Vector2 position, Rectangle source_rect)
{
	//Calculates texture coordinates of a sprite

	float texX = (float)source_rect.x;
	float texY = (texture->height - ((source_rect.height * ((source_rect.y + source_rect.height) / (float)source_rect.height))));
	float texWidth = (texX + source_rect.width) / (float)texture->width;
	float texHeight = (texY + source_rect.height) / (float)texture->height;
	texX /= (float)texture->width;
	texY /= (float)texture->height;

	//Texcoords for each corner of sprite stored for access in for loop
	Vector2 texCoords[4];
	texCoords[0] = vec2(texX, texY);
	texCoords[1] = vec2(texWidth, texY);
	texCoords[2] = vec2(texWidth, texHeight);
	texCoords[3] = vec2(texX, texHeight);
	Vector3 positions[4];
	positions[0] = vec3(std::floor(position.x), std::floor(position.y) + (float)source_rect.height, z_index);
	positions[1] = vec3(std::floor(position.x) + (float)source_rect.width, std::floor(position.y) + (float)source_rect.height, z_index);
	positions[2] = vec3(std::floor(position.x) + (float)source_rect.width, std::floor(position.y), z_index);
	positions[3] = vec3(std::floor(position.x), std::floor(position.y), z_index);

	for (int i = 0; i < 4; i++)
	{
		
		verticesAttribs[verticeCount] = positions[i].x;
		verticeCount++;
		verticesAttribs[verticeCount] = positions[i].y;
		verticeCount++;
		verticesAttribs[verticeCount] = positions[i].z;
		verticeCount++;
		verticesAttribs[verticeCount] = texCoords[i].x;
		verticeCount++;
		verticesAttribs[verticeCount] = texCoords[i].y;
		verticeCount++;
		verticesAttribs[verticeCount] = (float)texture->slot;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
	}
	z_index -= 0.000001f;
}

// void DrawText(Font font, const Shader &shader, std::string text, float x, float y, float scale, Vector3 color)
// {
	
// }
void draw_sprite(Sprite* sprite)
{
	//Calculates texture coordinates of a sprite
	float texX = (float)sprite->source_rect.x;
	float texY = (sprite->texture->height - ((sprite->source_rect.height * ((sprite->source_rect.y + sprite->source_rect.height) / (float)sprite->source_rect.height))));
	float texWidth = (texX + sprite->source_rect.width) / (float)sprite->texture->width;
	float texHeight = (texY + sprite->source_rect.height) / (float)sprite->texture->height;
	texX /= (float)sprite->texture->width;
	texY /= (float)sprite->texture->height;

	//Texcoords for each corner of sprite stored for access in for loop
	Vector2 texCoords[4];
	texCoords[0] = vec2(texX, texY);
	texCoords[1] = vec2(texWidth, texY);
	texCoords[2] = vec2(texWidth, texHeight);
	texCoords[3] = vec2(texX, texHeight);
	//Positions of each corner of sprite stored for access in for loop
	Vector3 positions[4];
	// TODO: use vector3 instead of vector2 for z layer so we can sort by depth

	float scaled_width = sprite->source_rect.width * sprite->scale.x;
	float scaled_height = sprite->source_rect.height * sprite->scale.y;
	float origin_x = -sprite->origin.x;
	float origin_y = -sprite->origin.y;
	float cos_rotation = cos(sprite->rotation);
	float sin_rotation = sin(sprite->rotation);

	float p0_x = std::floor(sprite->position.x + origin_x * cos_rotation - (origin_y + scaled_height) * sin_rotation);
	float p0_y = std::floor(sprite->position.y + origin_x * sin_rotation + (origin_y + scaled_height) * cos_rotation);


	float p1_x = std::floor(sprite->position.x + (origin_x + scaled_width) * cos_rotation - (origin_y + scaled_height) * sin_rotation);
	float p1_y = std::floor(sprite->position.y + (origin_x + scaled_width) * sin_rotation + (origin_y + scaled_height) * cos_rotation);

	float p2_x = std::floor(sprite->position.x + (origin_x + scaled_width) * cos_rotation - origin_y * sin_rotation);
	float p2_y = std::floor(sprite->position.y + (origin_x + scaled_width) * sin_rotation + origin_y * cos_rotation);
	
	float p3_x = std::floor(sprite->position.x + origin_x * cos_rotation - origin_y * sin_rotation);
	float p3_y = std::floor(sprite->position.y + origin_x * sin_rotation + origin_y * cos_rotation);

	positions[0] = vec3(p0_x, p0_y, z_index);
	positions[1] = vec3(p1_x, p1_y, z_index);
	positions[2] = vec3(p2_x, p2_y, z_index);
	positions[3] = vec3(p3_x, p3_y, z_index);



	// positions[0] = vec2(floor(sprite->position.x), floor(sprite->position.y) + (float)sprite->source_rect.height);
	// positions[1] = vec2(floor(sprite->position.x) + (float)sprite->source_rect.width, floor(sprite->position.y) + (float)sprite->source_rect.height);
	// positions[2] = vec2(floor(sprite->position.x) + (float)sprite->source_rect.width, floor(sprite->position.y));
	// positions[3] = vec2(floor(sprite->position.x), floor(sprite->position.y));

	//Adding all data for each vertice of the sprite into the vertex buffer
	for (int i = 0; i < 4; i++)
	{
		
		verticesAttribs[verticeCount] = positions[i].x;
		verticeCount++;
		verticesAttribs[verticeCount] = positions[i].y;
		verticeCount++;
		verticesAttribs[verticeCount] = positions[i].z;
		verticeCount++;
		verticesAttribs[verticeCount] = texCoords[i].x;
		verticeCount++;
		verticesAttribs[verticeCount] = texCoords[i].y;
		verticeCount++;
		verticesAttribs[verticeCount] = (float)sprite->texture->slot;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
	}
	z_index -= 0.000001f;
}
void draw_text(std::string text, Vector2 position, Vector4 color)
{
	int line_count = 0;
	Vector2 char_position = position;
	for (int i = 0; i < text.size(); i++)
	{
		char test_char = text[i];
		if (test_char == '\n')
		{
			//printf(text[i]);
			line_count++;
			char_position.x = position.x;
			continue;
		}
		//log(text);
		FontChar ch = default_font->font_chars[text[i]];

		float xpos = char_position.x + ch.bearing.x;
		float ypos = char_position.y + (ch.bearing.y);


		ypos += default_font->line_height * line_count;
		float w = (float)ch.source_rect.width;
		float h = (float)ch.source_rect.height;

		float texX = (float)ch.source_rect.x;
		float texY = (default_font->texture->height - ((ch.source_rect.height * ((ch.source_rect.y + ch.source_rect.height) / (float)ch.source_rect.height))));
		float texWidth = (texX + ch.source_rect.width) / (float)default_font->texture->width;
		float texHeight = (texY + ch.source_rect.height) / (float)default_font->texture->height;
		texX /= (float)default_font->texture->width;
		texY /= (float)default_font->texture->height;
		Vector2 texCoords[4];
		texCoords[0] = vec2(texX, texY);
		texCoords[1] = vec2(texWidth, texY);
		texCoords[2] = vec2(texWidth, texHeight);
		texCoords[3] = vec2(texX, texHeight);
		Vector3 positions[4];
		positions[0] = vec3(std::floor(xpos), std::floor(ypos) + (float)ch.source_rect.height, z_index);
		positions[1] = vec3(std::floor(xpos) + (float)ch.source_rect.width, std::floor(ypos) + (float)ch.source_rect.height, z_index);
		positions[2] = vec3(std::floor(xpos) + (float)ch.source_rect.width, std::floor(ypos), z_index);
		positions[3] = vec3(std::floor(xpos), std::floor(ypos), z_index);

		for (int j = 0; j < 4; j++)
		{
			
			verticesAttribs[verticeCount] = positions[j].x;
			verticeCount++;
			verticesAttribs[verticeCount] = positions[j].y;
			verticeCount++;
			verticesAttribs[verticeCount] = positions[j].z;
			verticeCount++;
			verticesAttribs[verticeCount] = texCoords[j].x;
			verticeCount++;
			verticesAttribs[verticeCount] = texCoords[j].y;
			verticeCount++;
			verticesAttribs[verticeCount] = (float)default_font->texture->slot;
			verticeCount++;
			verticesAttribs[verticeCount] = color.x;
			verticeCount++;
			verticesAttribs[verticeCount] = color.y;
			verticeCount++;
			verticesAttribs[verticeCount] = color.z;
			verticeCount++;
			verticesAttribs[verticeCount] = color.w;
			verticeCount++;
		}
		z_index -= 0.000001f;
		
		char_position.x += ch.advance; 
	}
}
void draw_text(std::string text, Vector2 position, BmFont* font)
{
	//GLCall(glUseProgram(shader->program));
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, font->texture->rendererID);
	//glBindVertexArray(vertexArray);

	//iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c!= text.end(); c++)
	{
		FontChar ch = font->font_chars[*c];

		float xpos = position.x + ch.bearing.x;
		//std::cout << xpos << std::endl;
		// float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		float ypos = position.y + (ch.bearing.y);

		float w = (float)ch.source_rect.width;
		float h = (float)ch.source_rect.height;

		//Calculates texture coordinates of a sprite
		float texX = (float)ch.source_rect.x;
		float texY = (font->texture->height - ((ch.source_rect.height * ((ch.source_rect.y + ch.source_rect.height) / (float)ch.source_rect.height))));
		float texWidth = (texX + ch.source_rect.width) / (float)font->texture->width;
		float texHeight = (texY + ch.source_rect.height) / (float)font->texture->height;
		texX /= (float)font->texture->width;
		texY /= (float)font->texture->height;
		//Update vertexBuffer for each character
		// float vertices[6][4] = 
		// {
		// 	{xpos,     ypos + h, texX, texY },
		// 	{xpos,     ypos,     texX, texHeight },
		// 	{xpos + w, ypos,     texWidth, texHeight },

		// 	{xpos,     ypos + h, texX, texY },
		// 	{xpos + w, ypos    , texWidth, texHeight },
		// 	{xpos + w, ypos + h, texWidth, texY }
		// };
		Vector2 texCoords[4];
		texCoords[0] = vec2(texX, texY);
		texCoords[1] = vec2(texWidth, texY);
		texCoords[2] = vec2(texWidth, texHeight);
		texCoords[3] = vec2(texX, texHeight);
		Vector3 positions[4];
		positions[0] = vec3(std::floor(xpos), std::floor(ypos) + (float)ch.source_rect.height, z_index);
		positions[1] = vec3(std::floor(xpos) + (float)ch.source_rect.width, std::floor(ypos) + (float)ch.source_rect.height, z_index);
		positions[2] = vec3(std::floor(xpos) + (float)ch.source_rect.width, std::floor(ypos), z_index);
		positions[3] = vec3(std::floor(xpos), std::floor(ypos), z_index);

		for (int i = 0; i < 4; i++)
		{
			
			verticesAttribs[verticeCount] = positions[i].x;
			verticesAttribs[verticeCount + 1] = positions[i].y;
			verticesAttribs[verticeCount + 2] = positions[i].z;
			verticesAttribs[verticeCount + 3] = texCoords[i].x;
			verticesAttribs[verticeCount + 4] = texCoords[i].y;
			verticesAttribs[verticeCount + 5] = (float)font->texture->slot;
			verticesAttribs[verticeCount + 6] = 1.0f;
			verticesAttribs[verticeCount + 7] = 1.0f;
			verticesAttribs[verticeCount + 8] = 1.0f;
			verticesAttribs[verticeCount + 9] = 1.0f;
			verticeCount += 10;
		}
		z_index -= 0.000001f;
		
		//Update content of vertexBuffer memory
		//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		position.x += ch.advance; 
	}
	//glBindVertexArray(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
}
void draw_true_type_text(Font* font, Shader* shader, std::string text, float x, float y, float scale, Vector4 color, float dt)
{
	GLCall(glUseProgram(shader->program));
	
	shader->set_uniform_vec4f("text_color", color);
	//iterate through all characters
	std::string::const_iterator c;
	float original_x_position = x;
	int count = 0;
	for (c = text.begin(); c!= text.end(); c++)
	{
		FontCharacter ch = font->fontCharacters[*c];

		float xpos = x + ch.Bearing.x * scale;
		// float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		float ypos = y - (ch.Bearing.y) * scale;

		//xpos += sin((dt + count) * 15) * 1;
		//ypos += sin((dt + count + dt) * 15) * 1;
		//ypos += (sin((dt + count) * 1)) * 50;
		//count++;

		// if (*c == 32)
		// {
		// 	xpos.x += (font->face->glyph->advance.x >> 6) * scale;
		// 	continue;
		// }
		// if (*c == 10)
		// {
		// 	xpos = original_x_position;
		// 	ypos += font->size * scale;
		// 	continue;
		// }

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		//Update vertexBuffer for each character
		float vertices[6][4] = 
		{
			{xpos,     ypos + h, 0.0f, 1.0f },
			{xpos,     ypos,     0.0f, 0.0f },
			{xpos + w, ypos,     1.0f, 0.0f },

			{xpos,     ypos + h, 0.0f, 1.0f },
			{xpos + w, ypos    , 1.0f, 0.0f },
			{xpos + w, ypos + h, 1.0f, 1.0f }
		};
		// float vertices[6][4] = 
		// {
		// 	{xpos,     ypos + h, 0.0f, 0.0f },
		// 	{xpos + w, ypos + h, 1.0f, 0.0f },
		// 	{xpos + w, ypos,     1.0f, 1.0f },

		// 	{xp	os + w, ypos    , 1.0f, 1.0f },
		// 	{xpos,     ypos,     0.0f, 1.0f },
		// 	{xpos,     ypos + h, 0.0f, 0.0f },
		// };
    // float vertices[6][4] = 
    // {
    //     { xpos,     ypos + h,   0.0f, 0.0f },            
    //     { xpos,     ypos,       0.0f, 1.0f },
    //     { xpos + w, ypos,       1.0f, 1.0f },

    //     { xpos,     ypos + h,   0.0f, 0.0f },
    //     { xpos + w, ypos,       1.0f, 1.0f },
    //     { xpos + w, ypos + h,   1.0f, 0.0f }           
    // };


	// for (int i = 0; i < 4; i++)
	// {
		
	// 	verticesAttribs[verticeCount] = positions[i].x;
	// 	verticeCount++;
	// 	verticesAttribs[verticeCount] = positions[i].y;
	// 	verticeCount++;
	// 	verticesAttribs[verticeCount] = texCoords[i].x;
	// 	verticeCount++;
	// 	verticesAttribs[verticeCount] = texCoords[i].y;
	// 	verticeCount++;
	// }
		glBindVertexArray(true_type_text_vertex_array);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		//Update content of vertexBuffer memory
		glBindBuffer(GL_ARRAY_BUFFER, true_type_text_vertex_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		//Advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; //Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void draw_lines_by_points(float* values, int value_count, Shader* shader)
{
	for (int i = 0; i < value_count; i++) {
		line_points[i] = vec3(200 + (float)i * 1.5f, values[i] * 200 + 500, 0.0f);
	}
	set_shader(shader);
	//shader->SetUniform4f("tint_color", color);
	glBindBuffer(GL_ARRAY_BUFFER, line_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, value_count * sizeof(Vector3), line_points);
	glBindVertexArray(line_vao);
	glEnable(GL_LINE_SMOOTH);
	//glLineWidth(2);
	GLCall(glDrawArrays(GL_LINE_STRIP, 0,  value_count));
	//memset(line_points, 0, MAX_POINT_COUNT * sizeof(Vector3));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void draw_immediate_rectangle(Rectangle rect, Vector4 color, Shader* shader)
{
	set_shader(shader);
	//color = Vector4(color.x / 255, color.y / 255, color.z / 255, color.w / 255);
	// Vector3 positions[4];

	// float scaled_width = sprite->source_rect.width * sprite->scale.x;
	// float scaled_height = sprite->source_rect.height * sprite->scale.y;
	// float origin_x = -sprite->origin.x;
	// float origin_y = -sprite->origin.y;
	// float cos_rotation = cos(sprite->rotation);
	// float sin_rotation = sin(sprite->rotation);

	// float p0_x = std::floor(sprite->position.x + origin_x * cos_rotation - (origin_y + scaled_height) * sin_rotation);
	// float p0_y = std::floor(sprite->position.y + origin_x * sin_rotation + (origin_y + scaled_height) * cos_rotation);


	// float p1_x = std::floor(sprite->position.x + (origin_x + scaled_width) * cos_rotation - (origin_y + scaled_height) * sin_rotation);
	// float p1_y = std::floor(sprite->position.y + (origin_x + scaled_width) * sin_rotation + (origin_y + scaled_height) * cos_rotation);

	// float p2_x = std::floor(sprite->position.x + (origin_x + scaled_width) * cos_rotation - origin_y * sin_rotation);
	// float p2_y = std::floor(sprite->position.y + (origin_x + scaled_width) * sin_rotation + origin_y * cos_rotation);
	
	// float p3_x = std::floor(sprite->position.x + origin_x * cos_rotation - origin_y * sin_rotation);
	// float p3_y = std::floor(sprite->position.y + origin_x * sin_rotation + origin_y * cos_rotation);

	// positions[0] = vec3(p0_x, p0_y, z_index);
	// positions[1] = vec3(p1_x, p1_y, z_index);
	// positions[2] = vec3(p2_x, p2_y, z_index);
	// positions[3] = vec3(p3_x, p3_y, z_index);

	Vector3 positions[4];
	positions[0] = vec3((float)std::floor(rect.x), (float)std::floor(rect.y) + (float)rect.height, z_index);
	positions[1] = vec3((float)std::floor(rect.x) + (float)rect.width, (float)std::floor(rect.y) + (float)rect.height, z_index);
	positions[2] = vec3((float)std::floor(rect.x) + (float)rect.width, (float)std::floor(rect.y), z_index);
	positions[3] = vec3((float)std::floor(rect.x), (float)std::floor(rect.y), z_index);

	float immediate_vertices[6][7] = 
	{
		{positions[0].x, positions[0].y, 1.0f, color.x, color.y, color.z, color.w },
		{positions[3].x, positions[3].y, 1.0f, color.x, color.y, color.z, color.w },
		{positions[2].x, positions[2].y, 1.0f, color.x, color.y, color.z, color.w },

		{positions[0].x, positions[0].y, 1.0f, color.x, color.y, color.z, color.w },
		{positions[2].x, positions[2].y, 1.0f, color.x, color.y, color.z, color.w },
		{positions[1].x, positions[1].y, 1.0f, color.x, color.y, color.z, color.w }
	};
	glBindBuffer(GL_ARRAY_BUFFER, immediate_vertex_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(immediate_vertices), immediate_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLCall(glBindVertexArray(immediate_vertex_array));

	glDrawArrays(GL_TRIANGLES, 0, 6);

}
void draw_rectangle(Rectangle rect, Vector4 color)
{

	//color = Vector4(color.x / 255, color.y / 255, color.z / 255, color.w / 255);
	// Vector3 positions[4];

	// float scaled_width = sprite->source_rect.width * sprite->scale.x;
	// float scaled_height = sprite->source_rect.height * sprite->scale.y;
	// float origin_x = -sprite->origin.x;
	// float origin_y = -sprite->origin.y;
	// float cos_rotation = cos(sprite->rotation);
	// float sin_rotation = sin(sprite->rotation);

	// float p0_x = std::floor(sprite->position.x + origin_x * cos_rotation - (origin_y + scaled_height) * sin_rotation);
	// float p0_y = std::floor(sprite->position.y + origin_x * sin_rotation + (origin_y + scaled_height) * cos_rotation);


	// float p1_x = std::floor(sprite->position.x + (origin_x + scaled_width) * cos_rotation - (origin_y + scaled_height) * sin_rotation);
	// float p1_y = std::floor(sprite->position.y + (origin_x + scaled_width) * sin_rotation + (origin_y + scaled_height) * cos_rotation);

	// float p2_x = std::floor(sprite->position.x + (origin_x + scaled_width) * cos_rotation - origin_y * sin_rotation);
	// float p2_y = std::floor(sprite->position.y + (origin_x + scaled_width) * sin_rotation + origin_y * cos_rotation);
	
	// float p3_x = std::floor(sprite->position.x + origin_x * cos_rotation - origin_y * sin_rotation);
	// float p3_y = std::floor(sprite->position.y + origin_x * sin_rotation + origin_y * cos_rotation);

	// positions[0] = vec3(p0_x, p0_y, z_index);
	// positions[1] = vec3(p1_x, p1_y, z_index);
	// positions[2] = vec3(p2_x, p2_y, z_index);
	// positions[3] = vec3(p3_x, p3_y, z_index);

	Vector3 positions[4];
	positions[0] = vec3((float)std::floor(rect.x), (float)std::floor(rect.y) + (float)rect.height, z_index);
	positions[1] = vec3((float)std::floor(rect.x) + (float)rect.width, (float)std::floor(rect.y) + (float)rect.height, z_index);
	positions[2] = vec3((float)std::floor(rect.x) + (float)rect.width, (float)std::floor(rect.y), z_index);
	positions[3] = vec3((float)std::floor(rect.x), (float)std::floor(rect.y), z_index);


	for (int i = 0; i < 4; i++)
	{
		
		verticesAttribs[verticeCount] = positions[i].x;
		verticesAttribs[verticeCount + 1] = positions[i].y;
		verticesAttribs[verticeCount + 2] = positions[i].z;
		verticesAttribs[verticeCount + 3] = 0.0f;
		verticesAttribs[verticeCount + 4] = 1.0f;
		verticesAttribs[verticeCount + 5] = 1.0f;
		verticesAttribs[verticeCount + 6] = color.x;
		verticesAttribs[verticeCount + 7] = color.y;
		verticesAttribs[verticeCount + 8] = color.z;
		verticesAttribs[verticeCount + 9] = color.w;
		verticeCount += 10;
	}
	z_index -= 0.000001f;
}
void draw_render_target(const RenderTarget &render_target, const Rectangle &rectangle, const Shader* shader)
{	

	Vector2 texCoords[4];
	texCoords[0] = vec2(0, 0);
	texCoords[1] = vec2(1, 0);
	texCoords[2] = vec2(1, 1);
	texCoords[3] = vec2(0, 1);
	Vector2 positions[4];
	positions[0] = vec2((float)rectangle.x, (float)rectangle.y + (float)rectangle.height);
	positions[1] = vec2((float)rectangle.x + (float)rectangle.width, (float)rectangle.y + (float)rectangle.height);
	positions[2] = vec2((float)rectangle.x + (float)rectangle.width, (float)rectangle.y);
	positions[3] = vec2((float)rectangle.x, (float)rectangle.y);

	// positions[0] = vec2(-1, -1);
	// positions[1] = vec2(1, -1);
	// positions[2] = vec2(1, 1);
	// positions[3] = vec2(-1, 1);
	//Color color(255, 255, 255, 255);
	for (int i = 0; i < 4; i++)
	{
		
		verticesAttribs[verticeCount] = positions[i].x;
		verticeCount++;
		verticesAttribs[verticeCount] = positions[i].y;
		verticeCount++;
		verticesAttribs[verticeCount] = z_index;
		verticeCount++;
		verticesAttribs[verticeCount] = texCoords[i].x;
		verticeCount++;
		verticesAttribs[verticeCount] = texCoords[i].y;
		verticeCount++;
		verticesAttribs[verticeCount] = 0;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
		verticesAttribs[verticeCount] = 1.0f;
		verticeCount++;
	}
	set_shader(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, render_target.texID);
	//@Cleanup should fix this to work with glSubBufferData, currently not sure why vram increases when using glSubBufferData
	//Updating the data in the vertex buffer for sprite batching
	GLCall(glBindVertexArray(vertex_array));
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticeCount * sizeof(float), verticesAttribs);
	glDrawElements(GL_TRIANGLES, ((verticeCount / 5) / 4) * 6, GL_UNSIGNED_INT, nullptr);

	for (int i = 0; i < verticeCount; i++)
	{  
		verticesAttribs[i] = 0;
	}
	verticeCount = 0;
	glBindTexture(GL_TEXTURE_2D, render_target.texID);
}
void fill_indices()
{
	//Fills the array of indicies in the correct pattern
	int numberOfIndicies = maxQuads * 6;
	int offset = 0;
	for (int i = 0; i < numberOfIndicies; i += 6)
	{
		indices[i] = offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = offset;
		offset += 4;
	}
}
void begin_render_batch()
{
	if (batch_begun)
	{
		log_error("end_render_batch not called for previous batch");
		assert(false);
	}
	//Should also include changing the blend mode
	batch_begun = true;

}
void end_render_batch(const Shader* shader)
{

	GLCall(glUseProgram(shader->program));
	GLCall(glBindVertexArray(vertex_array));
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticeCount * sizeof(float), verticesAttribs);
	glDrawElements(GL_TRIANGLES, ((verticeCount / 10) / 4) * 6, GL_UNSIGNED_INT, nullptr);

	for (int i = 0; i < verticeCount; i++)
	{  
		verticesAttribs[i] = 0;
	}
	verticeCount = 0;
	z_index = 0;
	batch_begun = false;
}
// void add_text_to_render(const Text& text)
// {
// 	text_to_render.push_back(text);
// }
// void draw_queued_text()
// {
// 	if (text_to_render.size() != 0)
// 	{
// 		for (Text text : text_to_render)
// 		{
// 			if (text.font == nullptr)
// 				draw_text(text.text, text.position);
// 			else draw_text(text.text, text.position, text.font);
// 		}
// 	}
// 	if (text_to_render.size() != 0)
// 		text_to_render.clear();		
// }
void set_default_font(BmFont* font)
{
	default_font = font;
}
void set_view_port(int x, int y, int width, int height)
{
	glViewport(0, 0, width, height);
}
void set_back_buffer(Window* window)
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	glViewport(0, 0, window->width, window->height);
}
void set_render_target(const RenderTarget &renderTarget)
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, renderTarget.rendererID));
	glViewport(0, 0, renderTarget.width, renderTarget.height);
}
// Currently only have one
// This will not work for more than onse UBO
void init_camera_ubo()
{
	glGenBuffers(1, &camera_ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, camera_ubo);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Matrix4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, camera_ubo, 0, 2 * sizeof(Matrix4));
}
unsigned int create_vertex_buffer(void* vertex_attributes_data, int size, int draw_hint)
{
	unsigned int new_vertex_buffer = 0;
	GLCall(glGenBuffers(1, &new_vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, new_vertex_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertex_attributes_data, draw_hint));	
	return new_vertex_buffer;
}
void set_vertex_buffer_sub_data(void *data)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data);
}
unsigned int create_vertex_array()
{
	return 1;
}
// void create_vertex_array_attribute(int attrib_num, int num_of_values, int size, const void* offset)
// {
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VtxPNT), 0);
// }
unsigned int create_index_buffer(void* indices_data, int size, int draw_hint)
{
	unsigned int new_index_buffer = 0;
	GLCall(glGenBuffers(1, &new_index_buffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_index_buffer));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,
						indices_data, draw_hint));		
	return new_index_buffer;
}
// void set_camera_ubo_data(Camera* camera)
// {
// 	glBindBuffer(GL_UNIFORM_BUFFER, camera_ubo);
// 	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(camera->proj), &camera->proj);
// 	// @Speed redundant matrix calculations
// 	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4), sizeof(camera->view), &camera->view);
// 	glBindBuffer(GL_UNIFORM_BUFFER, 0);		
//}
void add_shader_to_camera_ubo(Shader* shader, const char* name)
{
	glGetUniformBlockIndex(shader->program, name);
}
GLint check_available_gpu_memory_kb()
{
	GLint cur_avail_mem_kb = 0;
	glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, 
      &cur_avail_mem_kb);
	std::cout << "Current VRAM Available: " << cur_avail_mem_kb << std::endl;
	return cur_avail_mem_kb;
}
void set_shader(const Shader* shader)
{
	GLCall(glUseProgram(shader->program));
}
void clear_buffer(const Vector4 &color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void save_image(char* filepath, const RenderTarget& render_target, Window* window)
{

	// int width = render_target.width;
	// int height = render_target.height;

	// GLsizei nr_channels = 4;
	// GLsizei stride = nr_channels * width;
	// stride += (stride % 4) ? (4 - stride % 4) : 0;
	// GLsizei bufferSize = stride * height;
	// std::vector<char> buffer(bufferSize);
	// glPixelStorei(GL_PACK_ALIGNMENT, 4);
	// set_render_target(render_target);
	// glReadBuffer(GL_COLOR_ATTACHMENT0);
	// glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());
	// stbi_flip_vertically_on_write(true);
	// bool result = stbi_write_png(filepath, width, height, nr_channels, buffer.data(), stride);
	// set_back_buffer(window);
	// std::cout << result << std::endl;
}
}// namespace Tactics