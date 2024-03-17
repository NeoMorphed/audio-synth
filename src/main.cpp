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

//#define TWO_PI (3.14159265359f*2.0f)


// static inline float sin01(float alpha) {
//     return 0.5f*(float)sin(alpha) + 0.5f;
// }

// static inline float sin_minmax_Hz(float min, float max, float freq_Hz, float t) {
//     return (max - min) / 2.0f * sin01(t * freq_Hz * TWO_PI);
// }

// #define REFTIMES_PER_SEC  10000000
// #define REFTIMES_PER_MILLISEC  10000
struct Globals 
{
    float tone_hz;
    float amp_mod_hz;
    float tone_volume;
    float pan;
    float pan_mod_hz;
    float bot;
    bool sine;
    bool square;
    bool saw;
    bool noise;
    bool square_phase_shift;
    bool play;
    bool osc2;
};

static void output_sine_wave(s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440, f32 tone_volume = 0.5) {
    static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine);
        f32 sample_value = (sine_value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;

        t_sine += TAU / (f32)wave_period;
        if (t_sine >= TAU) {
            t_sine -= TAU;
        }
    }
}
static void output_square_wave(s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440, f32 tone_volume = 0.5, bool phase_shift = false) {
    static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        f32 value = 0; 
        if (phase_shift) {
            if (t_sine < PI / 2) value = 1;
            else if (t_sine > (3 * PI) / 2) value = 0;
        }
        else {
            if (t_sine < PI) value = 1;
            else if (t_sine > PI) value = 0;
        }
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;

        t_sine += TAU / (f32)wave_period;
        if (t_sine >= TAU) {
            t_sine -= TAU;
        }
    }
}
static void output_saw_wave(s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440, f32 tone_volume = 0.5) {
    static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    float slope = (1 - 0 / (TAU - 0));
    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        f32 value = 0; 
        float t_sine_range_1_0 = 0.0f + slope * ((float)t_sine - 0.0f);
        value = lerp(-1.0f, 1.0f, t_sine_range_1_0);
        //printf("%f\n", t_sine_range_1_0);
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;

        t_sine += TAU / (f32)wave_period;
        if (t_sine >= TAU) {
            t_sine -= TAU;
        }
    }
}
static void add_by_osc2(Globals* globals, s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440, f32 tone_volume = 0.5) {
    static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine * globals->bot);
        f32 sample_value = (sine_value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = *sample_out + sample_value;
        *sample_out++ = *sample_out + sample_value;

        t_sine += TAU / (f32)wave_period;
        if (t_sine >= TAU) {
            t_sine -= TAU;
        }
    }
}
static void amplitude_mod(s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440) {
    static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine);
        f32 sample_value = (f32)sine_value * 0.5f + 0.5f;
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = *sample_out * sample_value;
        *sample_out++ = *sample_out * sample_value;
        t_sine += TAU / wave_period;
        if (t_sine >= TAU) {
            t_sine -= TAU;
        }

    }
}
static void output_noise(s32 sample_count, f32* samples, f32 tone_volume = 0.5)
{
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        *samples++ = (float)(rand()/(float)(RAND_MAX/0.5f)) * tone_volume;
        *samples++ = (float)(rand()/(float)(RAND_MAX/0.5f)) * tone_volume;
    }
}
static void pan(s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440, float pan = 0)
{
    //static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        //f32 sine_value = (float)sin(t_sine);
        //f32 sample_value = (f32)sine_value * 0.5f + 0.5f;
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        float volume_left = 1.0f;
        float volume_right = 1.0f;
        if (pan > 0) volume_left = 1.0f - pan;
        else if (pan < 0) volume_right = 1.0f - (-pan);
        *sample_out++ = *sample_out * volume_left;
        *sample_out++ = *sample_out * volume_right;
        // t_sine += TAU / wave_period;
        // if (t_sine >= TAU) {
        //     t_sine -= TAU;
        // }

    }
}
static void pan_mod(s32 samples_per_second, s32 sample_count, f32 *samples, f32 tone_hz = 440)
{
    static f64 t_sine = 0;
    int wave_period = (int)(samples_per_second / tone_hz);

    f32 *sample_out = samples;
    for (int sample_index = 0; sample_index < sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine);
        f32 pan = (f32)sine_value;
        if (tone_hz == 0) pan = 0.0f;
        float volume_left = 1.0f;
        float volume_right = 1.0f;
        if (pan > 0) volume_left = 1.0f - pan;
        else if (pan < 0) volume_right = 1.0f - (-pan);
        *sample_out++ = *sample_out * volume_left;
        *sample_out++ = *sample_out * volume_right;
        t_sine += TAU / wave_period;
        if (t_sine >= TAU) {
            t_sine -= TAU;
        }

    }
}

void init_imgui(Window* window);
DWORD audio_run(void* variables);

void check_for_music_keyboard_keys(Globals* globals);

int run()
{
    srand((unsigned int)time(NULL));
    Window* window = (Window*)malloc(sizeof(Window));
    FrameTime frame_time;
    init_window(window, 400, 200, 1920, 1080, "GB Emulator");
    init_renderer();
    init_imgui(window);

    Vector2 render_target_size = vec2(1920, 1080);
    RenderTarget render_target; 
    make_render_target(&render_target, (int)render_target_size.x, (int)render_target_size.y);

    init_assets();
    init_input();

    Matrix4 full_window_proj = ortho_matrix(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);
    Shader* text_shader = new Shader("res/shaders/text.shader");
    Shader* render_target_shader = new Shader("res/shaders/render_target.shader");

    Globals globals;
    globals.tone_hz = 440;
    globals.amp_mod_hz = 0;
    globals.tone_volume = 0.25f;
    globals.pan = 0.0f;
    globals.pan_mod_hz = 0;
    globals.bot = 1.0f;
    globals.sine = true;
    globals.square = false;
    globals.saw = false;
    globals.noise = false;
    globals.square_phase_shift = true;
    globals.play = false;
    globals.osc2 = false;

    DWORD thread_id = 0;
    HANDLE handle = CreateThread(0, 0, audio_run, &globals, 0, &thread_id);
    SetThreadPriority(handle, THREAD_PRIORITY_TIME_CRITICAL);
    //WaitForSingleObject(handle, INFINITE);

    float lastFrame = 0;
    while (!window->should_close)
    {
        float currentFrame = (float)glfwGetTime();
        frame_time.delta_time = (currentFrame - lastFrame);
        lastFrame = currentFrame;
        glfwPollEvents();
        update_input_states(window);
        update_window(window);

        if (key_down(KEY_ESCAPE)) break;
        check_for_music_keyboard_keys(&globals);
        //basic_shader->set_uniform_mat4f("proj", full_window_proj);
        //basic_shader->set_uniform_mat4f("view", identity_matrix());
        render_target_shader->set_uniform_mat4f("proj", full_window_proj);
        text_shader->set_uniform_mat4f("proj", full_window_proj);

        // if (globals.sine) {
        //     globals.noise = false;
        //     globals.square = false;
        // }
        // else if (globals.square) {
        //     globals.noise = false;
        //     globals.sine = false;
        // }
        // else if (globals.sine) {
        //     globals.square = false;
        //     globals.sine = false;
        // }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("wave_form", NULL, ImGuiWindowFlags_None);

        ImGui::DragFloat("tone_hz", (float*)&globals.tone_hz, 1.0f);
        ImGui::DragFloat("amp_mod_hz", (float*)&globals.amp_mod_hz, 0.1f);
        ImGui::DragFloat("tone_volume", (float*)&globals.tone_volume, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("pan", (float*)&globals.pan, 0.01f, -1.0f, 1.0f);
        ImGui::DragFloat("pan_mod_hz", (float*)&globals.pan_mod_hz, 0.1f);
        ImGui::DragFloat("bot", (float*)&globals.bot, 0.01f, 0.01f);
        ImGui::Checkbox("sine", &globals.sine);
        ImGui::Checkbox("square", &globals.square);
        ImGui::Checkbox("saw", &globals.saw);
        ImGui::Checkbox("noise", &globals.noise);
        ImGui::Checkbox("osc2", &globals.osc2);
        ImGui::Checkbox("square_phase_shift", &globals.square_phase_shift);

        ImGui::End();
        //set_render_target(render_target);
        set_back_buffer(window);
        clear_buffer(vec4(0, 0, 0, 1));
        //clear_buffer(vec4(0, 0, 0, 1));
        //draw_render_target(render_target, Rectangle(0, 0, 1920, 1080), render_target_shader);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
        glfwSwapBuffers(window->glfw_window);
    }
    return 0;
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
            auto samples_per_second = format->nSamplesPerSec;
            f32* samples = (f32*)audio_data;
            // if (globals->play) output_test_sine_wave_f32(samples_per_second, sample_count, samples, globals->tone_hz, globals->tone_volume);
            // else output_triangle_wave(samples_per_second, sample_count, samples, globals->tone_hz, globals->tone_volume);
            //if (globals->play && !globals->both) {
            if (globals->play) {
                if (globals->sine)
                    output_sine_wave(samples_per_second, sample_count, samples, globals->tone_hz, globals->tone_volume);
                else if (globals->square)
                    output_square_wave(samples_per_second, sample_count, samples, globals->tone_hz, 
                                            globals->tone_volume, globals->square_phase_shift);
                else if (globals->saw)
                    output_saw_wave(samples_per_second, sample_count, samples, globals->tone_hz, globals->tone_volume);
                else if (globals->noise)
                    output_noise(sample_count, samples, globals->tone_volume);
                if (globals->osc2)
                    add_by_osc2(globals, samples_per_second, sample_count, samples, globals->tone_hz, globals->tone_volume);
                amplitude_mod(samples_per_second, sample_count, samples, globals->amp_mod_hz);
                //pan(samples_per_second, sample_count, samples, 1, globals->pan);
                pan_mod(samples_per_second, sample_count, samples, globals->pan_mod_hz);
                hr = render_client->ReleaseBuffer(sample_count, 0);
            }
            else hr = render_client->ReleaseBuffer(sample_count, AUDCLNT_BUFFERFLAGS_SILENT);
            //}
            // else if (globals->both && globals->play) {
            //     output_triangle_wave(samples_per_second, sample_count, samples, globals->tone_hz, globals->tone_volume);
            //     hr = render_client->ReleaseBuffer(sample_count, 0);
            // }
            //else hr = render_client->ReleaseBuffer(sample_count, AUDCLNT_BUFFERFLAGS_SILENT);
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