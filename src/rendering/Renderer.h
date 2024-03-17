#ifndef RENDERER_H
#define RENDERER_H

namespace Tactics
{
	struct Vector2;
	union Vector4;
	struct Texture;
	struct Rectangle;
	struct RenderTarget;
	struct Sprite;
	struct Shader;
	struct Window;
	struct Matrix;
	struct BmFont;
	struct Font;
	struct Camera;


	void 			init_renderer();
	void 			draw_sprite(Sprite* sprite);
	void 			draw_sprite(Texture* texture, Vector2 position, Rectangle sourceRect);
	void 			draw_text(std::string text, Vector2 position, Vector4 color);
	void 			draw_text(std::string text, Vector2 position, BmFont* font);
	void 			draw_true_type_text(Font* font, Shader* shader, std::string text, float x, float y,
											 float scale, Vector4 color);
	void 			draw_render_target(const RenderTarget &renderTarget, const Rectangle &rectangle, const Shader* shader);
	void 			begin_render_batch();
	void 			end_render_batch(const Shader* shader);
	void 			draw_immediate_rectangle(Rectangle rect, Vector4 color, Shader* shader);
	void 			draw_rectangle(Rectangle rectangle, Vector4 color);
	void 			draw_queued_text();
	void 			set_default_font(BmFont* font);
	void 			set_view_port(int x, int y, int width, int height);
	void            set_back_buffer(Window* window);
	void 			set_render_target(const RenderTarget &renderTarget);
	
	void 			init_camera_ubo();
	void 			set_camera_ubo_data(Camera* camera);
	void 			add_shader_to_camera_ubo(Shader* shader, const char* name);
	unsigned int 	create_vertex_buffer(void* vertex_attributes, int size, int draw_hint = GL_STATIC_DRAW);
	void 			set_vertex_buffer_sub_data(void* data);
	unsigned int 	create_vertex_array();
	unsigned int 	create_index_buffer(void* indices, int size, int draw_hint = GL_STATIC_DRAW);
	GLint 			check_available_gpu_memory_kb();
	void 			set_shader(const Shader* shader);
	void 			clear_buffer(const Vector4 &color);
	void 			save_image(char* filepath, const RenderTarget& render_target, Window* window);
	//enum BlendFunc = {Additive};
	// struct TextToRender
	// {
	// 	std::string text;
	// 	Vector2 position;
	// 	BmFont* font = nullptr;
	// 	Text(std::string text, Vector2 position);
	// 	Text(std::string text, Vector2 position, BmFont* font);
	// };
}

#endif