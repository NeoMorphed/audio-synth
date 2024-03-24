#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>

#include "core/Window.h"
#include "core/ErrorCheck.h"
#include "rendering/Renderer.h"
#include "input/Input.h"
#include "rendering/Shader.h"
#include "rendering/RenderTarget.h"
#include "rendering/Font.h"
#include "math/common_math.h"
#include "core/Rectangle.h"
#include "core/FrameTime.h"
#include "core/Assets.h"
#include "core/ScopeTimer.h"

//#include <endpointvolume.h>

#define TAU (M_PI * 2)

namespace Tactics {

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

enum Wave_Type {
    EXPONENT_WAVE,
    SINE_WAVE,
    SQUARE_WAVE,
    HALF_SQUARE_WAVE,
    TRIANGLE_WAVE,
    SAW_WAVE,
    WAVE_TYPE_COUNT
};
struct Globals 
{
    float* points;
    int point_count;
    float tone_hz;
    float amp_mod_hz;
    float tone_volume;
    float pan;
    float pan_mod_hz;
    float bot;
    float a;
    float b;
    float c;
    float d;
    float osc2_wave_percentage;
    Wave_Type wave_type;
    bool test;
    bool sine;
    bool square;
    bool triangle;
    bool saw;
    bool noise;
    bool half_square;
    bool pulse;
    bool abs;
    bool abs_add;
    bool play;
    bool osc2;
};
struct Sample_Info
{
    s32 samples_per_second;
    s32 sample_count;
    float* samples;
};

#include "sound_functions.cpp"

void init_imgui(Window* window);
DWORD audio_run(void* temp);

void check_for_music_keyboard_keys(Globals* globals);
void render_ui(Globals* globals);

int run()
{
    srand((unsigned int)time(NULL));
    Window* window = (Window*)malloc(sizeof(Window));
    FrameTime frame_time;
    init_window(window, 400, 200, 1920, 1080, "Synthesizer");
    init_renderer();
    init_imgui(window);

    RenderTarget render_target; 
    make_render_target(&render_target, 1920, 1080);

    init_assets();
    init_input();

    Matrix4 full_window_proj = ortho_matrix(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);
    Shader* text_shader = new Shader("res/shaders/text.shader");
    Shader* render_target_shader = new Shader("res/shaders/render_target.shader");
    Shader* line_shader = new Shader("res/shaders/line.shader");
    Font* font_64 = load_font("res/fonts/Bodo Amat.ttf", 64);

    Globals globals;
    globals.tone_hz = 440;
    globals.amp_mod_hz = 0;
    globals.tone_volume = 0.25f;
    globals.pan = 0.0f;
    globals.pan_mod_hz = 0;
    globals.bot = 1.0f;
    globals.a = 1.0f;
    globals.b = 1.0f;
    globals.c = 1.0f;
    globals.d = 1.0f;
    globals.osc2_wave_percentage = 100.0f;
    globals.wave_type = SINE_WAVE;
    globals.test = true;
    globals.sine = false;
    globals.square = false;
    globals.triangle = false;
    globals.saw = false;
    globals.noise = false;
    globals.abs = false;
    globals.abs_add = false;
    globals.half_square = true;
    globals.pulse = false;
    globals.play = false;
    globals.osc2 = false;
    globals.points = (float*)calloc(10000, sizeof(float));
    globals.point_count = 10000;

    // Start the audio thread.
    DWORD thread_id = 0;
    HANDLE handle = CreateThread(0, 0, audio_run, &globals, 0, &thread_id);
    SetThreadPriority(handle, THREAD_PRIORITY_TIME_CRITICAL);


    float test_points[10] = {1.0f, 6.0f, 2.0f, 20.0f, 100.0f, 2.0f, -5.0, -100.0f, 40.0f, 20.0f};
    float lastFrame = 0;
    while (!window->should_close)
    {   
        float current_frame = (float)glfwGetTime();
        frame_time.delta_time = (current_frame - lastFrame);
        lastFrame = current_frame;
        glfwPollEvents();
        update_input_states(window);
        update_window(window);

        if (key_down(KEY_ESCAPE)) break;
        check_for_music_keyboard_keys(&globals);
        render_target_shader->set_uniform_mat4f("proj", full_window_proj);
        text_shader->set_uniform_mat4f("proj", full_window_proj);
        line_shader->set_uniform_mat4f("proj", full_window_proj);
        text_shader->set_uniform_1f("time", current_frame);

        set_back_buffer(window);
        clear_buffer(vec4(0, 0, 0, 1));
        draw_lines_by_points(globals.points, globals.point_count, line_shader);
        //draw_true_type_text(font_64, text_shader, "Some text that moves./n And more text that moves!!>??", 
                                        //150.0f, 600.0f, 1, vec4(1.0f), current_frame);
        render_ui(&globals);
        glfwSwapBuffers(window->glfw_window);
        //memset(globals.points, 0, globals.point_count * sizeof(float));
    }
    return 0;
}

void render_ui(Globals* globals)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();
    ImGui::Begin("wave_form", NULL, ImGuiWindowFlags_None);

    ImGui::DragFloat("tone_hz", (float*)&globals->tone_hz, 1.0f);
    ImGui::DragFloat("amp_mod_hz", (float*)&globals->amp_mod_hz, 0.1f, 0.0f, 5000.0);
    ImGui::DragFloat("tone_volume", (float*)&globals->tone_volume, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat("pan", (float*)&globals->pan, 0.01f, -1.0f, 1.0f);
    ImGui::DragFloat("pan_mod_hz", (float*)&globals->pan_mod_hz, 0.1f, 0.0f, 5000.0f);
    //static int elem = SINE_WAVE;
    const char* wave_names[WAVE_TYPE_COUNT] = { "Exponent", "Sine", "Square", "Half-Square", "Triangle", "Saw" };
    const char* elem_name = 
            (globals->wave_type >= 0 && globals->wave_type < WAVE_TYPE_COUNT) ? wave_names[globals->wave_type] : "Unknown";

    ImGui::SliderInt("osc2 Wave Type", &(int)globals->wave_type, 0, WAVE_TYPE_COUNT - 1, elem_name);
    ImGui::SliderFloat("osc2 wave_percentage", &globals->osc2_wave_percentage, 0.0f, 100.0f);
    // ImGui::DragFloat("bot", (float*)&globals->bot, 0.01f, 0.01f);
    // ImGui::DragFloat("a", (float*)&globals->a, 0.01f, 0.01f);
    // ImGui::DragFloat("b", (float*)&globals->b, 0.01f, 0.01f);
    // ImGui::DragFloat("c", (float*)&globals->c, 0.01f, 0.01f);
    // ImGui::DragFloat("d", (float*)&globals->d, 0.01f, 0.01f);
    if(ImGui::Button("test")) {
        globals->test = true;
        globals->sine = false;
        globals->square = false;
        globals->triangle = false;
        globals->saw = false;
        globals->noise = false;
    }
    ImGui::SameLine(75);
    ImGui::Checkbox("test", &globals->test);
    if(ImGui::Button("sine")) {
        globals->test = false;
        globals->sine = true;
        globals->square = false;
        globals->triangle = false;
        globals->saw = false;
        globals->noise = false;
    }
    ImGui::SameLine(75);
    ImGui::Checkbox("sine", &globals->sine);
    if(ImGui::Button("square")) {
        globals->test = false;
        globals->sine = false;
        globals->square = true;
        globals->triangle = false;
        globals->saw = false;
        globals->noise = false;
    }
    ImGui::SameLine(75);
    ImGui::Checkbox("square", &globals->square);
    if(ImGui::Button("triangle")) {
        globals->test = false;
        globals->sine = false;
        globals->square = false;
        globals->triangle = true;
        globals->saw = false;
        globals->noise = false;
    }
    ImGui::SameLine(75);
    ImGui::Checkbox("triangle", &globals->triangle);
    if(ImGui::Button("saw")) {
        globals->test = false;
        globals->sine = false;
        globals->square = false;
        globals->triangle = false;
        globals->saw = true;
        globals->noise = false;
    }
    ImGui::SameLine(75);
    ImGui::Checkbox("saw", &globals->saw);
    if(ImGui::Button("noise")) {
        globals->test = false;
        globals->sine = false;
        globals->square = false;
        globals->triangle = false;
        globals->saw = false;
        globals->noise = true;
    }
    ImGui::SameLine(75);
    ImGui::Checkbox("noise", &globals->noise);
    ImGui::Checkbox("abs", &globals->abs);
    ImGui::Checkbox("abs_add", &globals->abs_add);
    ImGui::Checkbox("osc2", &globals->osc2);
    ImGui::Checkbox("half_square", &globals->half_square);
    ImGui::Checkbox("pulse", &globals->pulse);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
}
DWORD audio_run(void* temp)
{
    Globals* globals = (Globals*)temp;
	HRESULT hr;
    IMMDeviceEnumerator* enumerator = NULL;
    IMMDeviceCollection* devices = NULL;
    IMMDevice* recorder = NULL;
    IMMDevice* renderer = NULL;
    IMMDevice* endpoint = NULL;
    IPropertyStore* props = NULL;
    IAudioClient* recorderClient = NULL;
    IAudioClient* audio_client = NULL;
    IAudioRenderClient* render_client = NULL;
    IAudioCaptureClient* captureService = NULL;
    WAVEFORMATEX* format = NULL;

    //LPWSTR endpoint_id;


    //hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    hr = CoInitializeEx(NULL, COINIT_SPEED_OVER_MEMORY);
    assert(SUCCEEDED(hr));
    hr = CoCreateInstance(
        CLSID_MMDeviceEnumerator,
        NULL,
        CLSCTX_ALL,
        IID_IMMDeviceEnumerator,
        (void**)&enumerator
    );
    assert(SUCCEEDED(hr));
    // hr = enumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &devices);
    // assert(SUCCEEDED(hr));
    hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &renderer);
    assert(SUCCEEDED(hr));
    hr = enumerator->Release();
    // assert(SUCCEEDED(hr));

    hr = renderer->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&audio_client);
    assert(SUCCEEDED(hr));

    hr = audio_client->GetMixFormat(&format);
    assert(format->nChannels == 2);
    assert(format->wBitsPerSample == 32);
    assert(SUCCEEDED(hr));

    REFERENCE_TIME buffer_duration = 30 * 10000; // 30ms
    DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_NOPERSIST;
    hr = audio_client->Initialize(AUDCLNT_SHAREMODE_SHARED, flags, buffer_duration,
    								 0, format, NULL);
    assert(SUCCEEDED(hr));
    hr = audio_client->GetService(IID_IAudioRenderClient, (void**)&render_client);

    UINT32 buffer_frame_count; 
    hr = audio_client->GetBufferSize(&buffer_frame_count);
    assert(SUCCEEDED(hr));

    HANDLE h_refill_event = CreateEventEx(NULL, NULL, 0, EVENT_MODIFY_STATE | SYNCHRONIZE);
    hr = audio_client->SetEventHandle(h_refill_event);
    assert(SUCCEEDED(hr));
    
    // renderer->GetId(&endpoint_id);
    // renderer->OpenPropertyStore(STGM_READ, &props);
    // //assert(SUCCEEDED(hr));
    // PROPVARIANT var_name;
    // PropVariantInit(&var_name);
    // hr = props->GetValue(PKEY_Device_FriendlyName, &var_name);
    // assert(SUCCEEDED(hr));
    // if (var_name.vt != VT_EMPTY) {
    // 	printf("Endpoint: \"%S\" (%S)\n", var_name.pwszVal, endpoint_id);
    // }
    // printf("Mix format:\n");
    // printf("  Format Tag:           %d\n", format->wFormatTag);
    // printf("  Sample rate:          %d\n", format->nSamplesPerSec);
    // printf("  Avg bytes per second: %d\n", format->nAvgBytesPerSec);
    // printf("  Bits per sample:      %d\n", format->wBitsPerSample);
    // printf("  Block Align:          %d\n", format->nBlockAlign);
    // printf("  Channels:             %d\n", format->nChannels);
    // printf("  Audio Frame Size:     %d\n", format->nBlockAlign);

    hr = audio_client->Start();
    assert(SUCCEEDED(hr));

    while(true) {
    	WaitForSingleObject(h_refill_event, INFINITE);
        
        UINT32 frame_padding_count = 0;
    	hr = audio_client->GetCurrentPadding(&frame_padding_count);
    	assert(SUCCEEDED(hr));

        UINT32 sample_count = buffer_frame_count - frame_padding_count;
        if (sample_count > 0)
        {
            BYTE* audio_data = NULL;
            hr = render_client->GetBuffer(sample_count, &audio_data);
           switch (hr) {
                case AUDCLNT_E_BUFFER_ERROR:
                    printf("AUDCLNT_E_BUFFER_ERROR.\n");
                    exit(1);
                    break;
                case AUDCLNT_E_BUFFER_TOO_LARGE:
                    printf("AUDCLNT_E_BUFFER_TOO_LARGE.\n");
                    exit(1);
                    break;
                case AUDCLNT_E_BUFFER_SIZE_ERROR:
                    printf("AUDCLNT_E_BUFFER_SIZE_ERROR.\n");
                    exit(1);
                    break;
                case AUDCLNT_E_OUT_OF_ORDER:
                    printf("AUDCLNT_E_OUT_OF_ORDER.\n");
                    exit(1);
                    break;
                case AUDCLNT_E_DEVICE_INVALIDATED:
                    printf("AUDCLNT_E_DEVICE_INVALIDATED.\n");
                    exit(1);
                    break;
                case AUDCLNT_E_BUFFER_OPERATION_PENDING:
                    printf("AUDCLNT_E_BUFFER_OPERATION_PENDING.\n");
                    exit(1);
                    break;
                case AUDCLNT_E_SERVICE_NOT_RUNNING:
                    printf("AUDCLNT_E_SERVICE_NOT_RUNNING.\n");
                    exit(1);
                    break;
                case E_POINTER:
                    printf("E_POINTER.\n");
                    exit(1);
                    break;
            }
 
            Sample_Info sample_info;
            sample_info.samples_per_second = format->nSamplesPerSec;
            sample_info.sample_count = sample_count;
            sample_info.samples = (f32*)audio_data;
            if (globals->play) {
                if (globals->test)
                    output_test_wave(globals, sample_info, globals->tone_hz, globals->tone_volume, globals->abs);
                else if (globals->sine)
                    output_sine_wave(sample_info, globals->tone_hz, globals->tone_volume, globals->abs);
                else if (globals->square)
                    output_square_wave(sample_info, globals->tone_hz, 
                                            globals->tone_volume, globals->half_square, globals->pulse);
                else if (globals->triangle)
                    output_triangle_wave(sample_info, globals->tone_hz, globals->tone_volume, globals->abs);
                else if (globals->saw)
                    output_saw_wave(sample_info, globals->tone_hz, globals->tone_volume, globals->abs);
                else if (globals->noise)
                    output_noise(sample_info, globals->tone_volume);
                if (globals->osc2)
                    add_by_osc2(sample_info, globals->tone_hz, globals->tone_volume, globals->wave_type, 
                                            globals->osc2_wave_percentage / 100, globals->abs_add);
                amplitude_mod(sample_info, globals->amp_mod_hz);
                //pan(samples_per_second, sample_count, samples, 1, globals->pan);
                pan_mod(sample_info, globals->pan_mod_hz);
                memcpy(globals->points, audio_data, sample_count * 8);
                // for (int i = 0; i < sample_info.sample_count; i += 2) {
                //     globals->points[i] = sample_info.samples[i];
                // }
                globals->point_count = sample_count * 8;
                hr = render_client->ReleaseBuffer(sample_count, 0);
           }
            else hr = render_client->ReleaseBuffer(sample_count, AUDCLNT_BUFFERFLAGS_SILENT);
            //AUDCLNT_BUFFERFLAGS_SILENT
        }
    }
	return 0;
}

void check_for_music_keyboard_keys(Globals* globals)
{
    if (key_down(KEY_Z)) {
        globals->tone_hz = 130.8f; 
        globals->play = true;
    }
    else if (key_down(KEY_X)) {
        globals->tone_hz = 146.8f; 
        globals->play = true;
    }
    else if (key_down(KEY_C)) {
        globals->tone_hz = 164.8f; 
        globals->play = true;
    }
    else if (key_down(KEY_V)) {
        globals->tone_hz = 174.6f; 
        globals->play = true;
    }
    else if (key_down(KEY_B)) {
        globals->tone_hz = 196.0f; 
        globals->play = true;
    }
    else if (key_down(KEY_N)) {
        globals->tone_hz = 220.0f; 
        globals->play = true;
    }
    else if (key_down(KEY_M)) {
        globals->tone_hz = 246.9f; 
        globals->play = true;
    }
    else if (key_down(KEY_COMMA)) {
        globals->tone_hz = 261.6f; 
        globals->play = true;
    }
    else if (key_down(KEY_A)) {
        globals->tone_hz = 2 * 130.8f; 
        globals->play = true;
    }
    else if (key_down(KEY_S)) {
        globals->tone_hz = 2 * 146.8f; 
        globals->play = true;
    }
    else if (key_down(KEY_D)) {
        globals->tone_hz = 2 * 164.8f; 
        globals->play = true;
    }
    else if (key_down(KEY_F)) {
        globals->tone_hz = 2 * 174.6f; 
        globals->play = true;
    }
    else if (key_down(KEY_G)) {
        globals->tone_hz = 2 * 196.0f; 
        globals->play = true;
    }
    else if (key_down(KEY_H)) {
        globals->tone_hz = 2 * 220.0f; 
        globals->play = true;
    }
    else if (key_down(KEY_J)) {
        globals->tone_hz = 2 * 246.9f; 
        globals->play = true;
    }
    else if (key_down(KEY_K)) {
        globals->tone_hz = 2 * 261.6f; 
        globals->play = true;
    }
    else if (key_down(KEY_Q)) {
        globals->tone_hz = 100.6f; 
        globals->play = true;
    }
    else if (key_down(KEY_W)) {
        globals->tone_hz = 150.6f; 
        globals->play = true;
    }
    else globals->play = false;
}
void init_imgui(Window* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/Bodo Amat.ttf", 14.0f);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->glfw_window, true); 
    ImGui_ImplOpenGL3_Init("#version 150");
}   

}//namespace Audio_Synth

int main(int argc, char** argv)
{
    Tactics::run();
    return 0;
}