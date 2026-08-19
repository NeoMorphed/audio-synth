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
#include "math/common_math.h"
#include "core/Rectangle.h"
#include "core/FrameTime.h"
#include "core/ScopeTimer.h"

//#include <endpointvolume.h>


// @Cleanup We should figure out a better way to communicate between threads when it comes to setting values
// in the globals struct.
// @Bug When combining 2 waveforms, the wave changes depending on when the button to combine them is pressed.
// We need to reset the timers on all the wave generators whenever we enable or disable combining.

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
    NOISE_WAVE,
    WAVE_TYPE_COUNT
};
// @TODO: Pack the bools into a u32 to shrink the struct size.
struct Globals 
{
    float* points;
    int point_count;
    float tone_hz;
    float amp_mod_hz;
    float tone_volume;
    float pan;
    float pan_mod_hz;
    float osc2_wave_percentage;
    Wave_Type osc2_wave_type;
    Wave_Type osc1_wave_type;
    bool abs;
    bool abs_add;
    bool play;
    bool osc2;
    bool pan_mod;
    bool osc2_just_pressed;
};
struct Sample_Info
{
    s32 samples_per_second;
    s32 sample_count;
    float* samples;
};

// We do this for now since we use the globals struct in the functions in this file. 
// We should find a better way to do this
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

    init_input();

    Matrix4 full_window_proj = ortho_matrix(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);
    Shader* text_shader = new Shader("res/shaders/text.shader");
    Shader* render_target_shader = new Shader("res/shaders/render_target.shader");
    Shader* line_shader = new Shader("res/shaders/line.shader");

    Globals globals;
    globals.tone_hz = 440;
    globals.amp_mod_hz = 0;
    globals.tone_volume = 0.25f;
    globals.pan = 0.0f;
    globals.pan_mod_hz = 0;
    globals.osc1_wave_type = SINE_WAVE;
    globals.osc2_wave_percentage = 100.0f;
    globals.osc2_wave_type = SINE_WAVE;
    globals.abs = false;
    globals.abs_add = false;
    globals.play = false;
    globals.osc2 = false;
    globals.pan_mod = false;
    globals.osc2_just_pressed = false;
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

    ImGui::Checkbox("pan_mod", &globals->pan_mod);

    ImGui::DragFloat("tone_hz", (float*)&globals->tone_hz, 1.0f);
    ImGui::DragFloat("amp_mod_hz", (float*)&globals->amp_mod_hz, 0.1f, 0.0f, 5000.0);
    ImGui::DragFloat("tone_volume", (float*)&globals->tone_volume, 0.01f, 0.0f, 1.0f);
    if (!globals->pan_mod) {
        ImGui::DragFloat("pan", (float*)&globals->pan, 0.01f, -1.0f, 1.0f);
    } else {
        ImGui::DragFloat("pan_mod_hz", (float*)&globals->pan_mod_hz, 0.1f, 0.0f, 5000.0f);
    }


    // @Cleanup Remove terenary operator. I don't normally like to use it.
    const char* osc1_wave_names[WAVE_TYPE_COUNT] = { "Exponent", "Sine", "Square", "Half-Square", "Triangle", "Saw", "Noise" };
    const char* osc1_elem_name = 
            (globals->osc1_wave_type >= 0 && globals->osc1_wave_type < WAVE_TYPE_COUNT) 
                ? osc1_wave_names[globals->osc1_wave_type] : "Unknown";

    ImGui::SliderInt("osc_1 Wave Type", &(int)globals->osc1_wave_type, 0, WAVE_TYPE_COUNT - 1, osc1_elem_name);

    const char* wave_names[WAVE_TYPE_COUNT] = { "Exponent", "Sine", "Square", "Half-Square", "Triangle", "Saw", "Noise" };
    const char* elem_name = 
            (globals->osc2_wave_type >= 0 && globals->osc2_wave_type < WAVE_TYPE_COUNT) 
                ? wave_names[globals->osc2_wave_type] : "Unknown";

    ImGui::SliderInt("osc_2 Wave Type", &(int)globals->osc2_wave_type, 0, WAVE_TYPE_COUNT - 1, elem_name);
    ImGui::SliderFloat("osc_2 wave_percentage", &globals->osc2_wave_percentage, 0.0f, 100.0f);

    ImGui::Checkbox("abs", &globals->abs);
    ImGui::Checkbox("abs_add", &globals->abs_add);
    bool temp = globals->osc2;
    ImGui::Checkbox("osc2", &globals->osc2);
    if (temp != globals->osc2) {
        globals->osc2_just_pressed = true;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
}


struct Wave_Positions
{
    f64 exponent;
    f64 sine;
    f64 square;
    f64 half_square;
    f64 triangle;
    f64 saw;
    f64 osc2;
    f64 amp_mod;
    f64 pan_mod;
};
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
    printf("Mix format:\n");
    printf("  Format Tag:           %d\n", format->wFormatTag);
    printf("  Sample rate:          %d\n", format->nSamplesPerSec);
    printf("  Avg bytes per second: %d\n", format->nAvgBytesPerSec);
    printf("  Bits per sample:      %d\n", format->wBitsPerSample);
    printf("  Block Align:          %d\n", format->nBlockAlign);
    printf("  Channels:             %d\n", format->nChannels);
    printf("  Audio Frame Size:     %d\n", format->nBlockAlign);

    hr = audio_client->Start();
    assert(SUCCEEDED(hr));


    Wave_Positions wave_positions[sizeof(Wave_Positions) / 8];
    memset(wave_positions, 0, sizeof(f64) * (sizeof(Wave_Positions) / 8));
    

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
            // if (globals->osc2_just_pressed == true) {
            //     memset(&wave_positions, 0, sizeof(Wave_Positions) / 8);
            //     globals->osc2_just_pressed = false;
            // }
            if (globals->play) {
                if (globals->osc1_wave_type == EXPONENT_WAVE)
                    output_test_wave(globals, sample_info, &wave_positions->exponent);
                else if (globals->osc1_wave_type == SINE_WAVE)
                    output_sine_wave(globals, sample_info, &wave_positions->sine);
                else if (globals->osc1_wave_type == HALF_SQUARE_WAVE)
                    output_half_square_wave(globals, sample_info, &wave_positions->half_square);
                else if (globals->osc1_wave_type == SQUARE_WAVE)
                    output_square_wave(globals, sample_info, &wave_positions->square);
                else if (globals->osc1_wave_type == TRIANGLE_WAVE)
                    output_triangle_wave(globals, sample_info, &wave_positions->triangle);
                else if (globals->osc1_wave_type == SAW_WAVE)
                    output_saw_wave(globals, sample_info, &wave_positions->saw);
                else if (globals->osc1_wave_type == NOISE_WAVE)
                    output_noise(globals, sample_info);
                if (globals->osc2)
                    add_by_osc2(globals, sample_info, &wave_positions->osc2);
                if (globals->amp_mod_hz != 0.0f) {
                    amplitude_mod(globals, sample_info, &wave_positions->amp_mod);
                }
                if (!globals->pan_mod) {
                    pan(globals, sample_info);
                } else {
                    pan_mod(globals, sample_info, &wave_positions->pan_mod);
                }
                
                // For rendering the waveform
                globals->point_count = sample_count * 8;
                memcpy(globals->points, audio_data, globals->point_count);

                hr = render_client->ReleaseBuffer(sample_count, 0);
           }
            else hr = render_client->ReleaseBuffer(sample_count, AUDCLNT_BUFFERFLAGS_SILENT);
            //AUDCLNT_BUFFERFLAGS_SILENT
        }
    }
	return 0;
}

// A bit messy. Maybe a hashmap or look up table.
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