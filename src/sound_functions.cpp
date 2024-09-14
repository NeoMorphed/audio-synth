//#include "sound_functions.h"
#include "math/common_math.h"


// I'm just lazy right now. We will put this back when we put into header file.
//namespace Tactics {


inline f64 inc_time_val(f64 t_sine, int wave_period)
{
    // Maybe we should just make wave_period a float?
    t_sine += TAU / (f32)wave_period;
    if (t_sine >= TAU) t_sine -= TAU;
    return t_sine;
}
void output_test_wave(Globals* globals, Sample_Info info, f32 tone_hz, f32 tone_volume, bool abs_modifier) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);
    f64 _2_3 = (4 * PI) / 3;
    f64 _1_2   = PI / 2;
    f32* sample_out = info.samples;
    float slope = (float)(((-1) - (1)) / (TAU - 0));
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 value = 0; 
        //printf("%f\n", t_sine);
        //float t_sine_range_1_0 = 0.0f + slope * ((float)t_sine - 0.0f);
        //value = (float)asin(t_sine_range_1_0) * (float)sin(t_sine_range_1_0);
        //else value = (float)asin(t_sine) * -(float)sin(t_sine);
        if (t_sine <= PI / 2) value = (float)pow((t_sine / 3.0f) - t_sine, 2.0);
        else if (t_sine > PI / 2 && t_sine <= PI) value = (float)pow(((PI - t_sine) / 3.0f) - (PI - t_sine), 2.0f);
        else if (t_sine > PI && t_sine <= (3 * PI) / 2) value = -(float)pow(((t_sine - PI) / 3.0f) - (t_sine - PI), 2.0);
        else if (t_sine > (3 * PI) / 4 && t_sine <= TAU) value = -(float)pow(((TAU - t_sine) / 3.0f) - (TAU - t_sine), 2.0f);
        if (abs_modifier) value = abs(value);
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void output_sine_wave(Sample_Info info, f32 tone_hz, f32 tone_volume, bool abs_modifier) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32* sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine);
        if (abs_modifier) sine_value = abs(sine_value);
        f32 sample_value = (sine_value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void output_square_wave(Sample_Info info, f32 tone_hz, f32 tone_volume) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32* sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 value = 0; 

        float sine_value = 1.0f * (float)sin(t_sine + 0.0f);
        if (sine_value > 0) value = 1.0f;
        else if (sine_value < 0) value = -1.0f;
        else value = 0.0f;
        
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void output_half_square_wave(Sample_Info info, f32 tone_hz, f32 tone_volume) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32* sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 value = 0; 
        
        if (t_sine <= PI / 2) value = 1;
        else if (t_sine > (3 * PI) / 2) value = 0;
        
        f32 sample_value = (value * tone_volume);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void output_triangle_wave(Sample_Info info, f32 tone_hz, f32 tone_volume, bool abs_modifier) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    //float slope = (float)((1 - 0) / ((TAU - 0)));
    float slope1 = (float)((1 - 0) / ((PI/2 - 0)));
    float slope2 = (float)((1 - 0) / (((3 * PI) / 2) - PI/2));
    float slope3 = (float)((1 - 0) / (TAU - (3 * PI) / 2));
    //slope = (output_end - output_start) / (input_end - input_start)
    //output = output_start + slope * (input - input_start)
    f32* sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 value = 0; 
        value = 1.0f * (2 / PI) * (float)asin(sin(t_sine + 0.0f));
        // Interesting sound for sound effects???
        //value = 1.0f * (2 / PI) * (float)asin(sin(t_sine * t_sine + 0.0f));
        //value = 1.0f * (2 / PI) * (float)((asin(sin(t_sine * t_sine ))) / (float)sin(t_sine * t_sine)) * (float)sin(t_sine);
        //value = 1.0f * (2 / PI) * (float)asin(sin(t_sine * t_sine + 2 / t_sine));
        if (abs_modifier) value = abs(value);
        f32 sample_value = (value * tone_volume);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void output_saw_wave(Sample_Info info, f32 tone_hz, f32 tone_volume, bool abs_modifier) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    float slope = (float)((1 - 0) / (TAU - 0));
    f32 *sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 value = 0; 
        float t_sine_range_1_0 = 0.0f + slope * ((float)t_sine - 0.0f);
        value = lerp(1.0f, -1.0f, t_sine_range_1_0);
        //value = (float)sin(t_sine) * tone_hz - (float)floor(sin(t_sine) * tone_hz);
        if (abs_modifier) value = abs(value);
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}

void add_by_osc2(Sample_Info info, f32 tone_hz, f32 tone_volume, Wave_Type type, float percentage, bool abs_modifier) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32 *sample_out = info.samples;
    float slope = (float)((1 - 0) / (TAU - 0));
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        float value = 0;
        if (type == EXPONENT_WAVE) {
            if (t_sine <= PI / 2) value = (float)pow((t_sine / 3.0f) - t_sine, 2.0);
            else if (t_sine > PI / 2 && t_sine <= PI) value = (float)pow(((PI - t_sine) / 3.0f) - (PI - t_sine), 2.0f);
            else if (t_sine > PI && t_sine <= (3 * PI) / 2) value = -(float)pow(((t_sine - PI) / 3.0f) - (t_sine - PI), 2.0);
            else if (t_sine > (3 * PI) / 4 && t_sine <= TAU) value = -(float)pow(((TAU - t_sine) / 3.0f) - (TAU - t_sine), 2.0f);
        }
        else if (type == SINE_WAVE) value = (float)sin(t_sine);
        else if (type == SQUARE_WAVE) {
            float sine_value = 1.0f * (float)sin(t_sine + 0.0f);
            if (sine_value > 0) value = 1.0f;
            else if (sine_value < 0) value = -1.0f;
            else value = 0.0f;
        }
        else if (type == HALF_SQUARE_WAVE) {
            if (t_sine <= PI / 2) value = 1;
            else if (t_sine > (3 * PI) / 2) value = 0;
        }
        else if (type == TRIANGLE_WAVE) value = 1.0f * (2 / PI) * (float)asin(sin(t_sine + 0.0f));
        else if (type == SAW_WAVE) {
            float t_sine_range_1_0 = 0.0f + slope * ((float)t_sine - 0.0f);
            value = lerp(1.0f, -1.0f, t_sine_range_1_0);
        }
        if (abs_modifier) value = abs(value);
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = *sample_out + (sample_value * percentage);
        *sample_out++ = *sample_out + (sample_value * percentage);
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void amplitude_mod(Sample_Info info, f32 tone_hz = 440) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32 *sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine);
        f32 sample_value = (f32)sine_value * 0.5f + 0.5f;
        *sample_out++ = *sample_out * sample_value;
        *sample_out++ = *sample_out * sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
void output_noise(Sample_Info info, f32 tone_volume = 0.5)
{
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        *info.samples++ = (float)(rand()/(float)(RAND_MAX/0.5f)) * tone_volume;
        *info.samples++ = (float)(rand()/(float)(RAND_MAX/0.5f)) * tone_volume;
    }
}
void pan(Sample_Info info, f32 tone_hz = 440, float pan = 0)
{
    f32 *sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        float volume_left = 1.0f;
        float volume_right = 1.0f;
        if (pan > 0) volume_left = 1.0f - pan;
        else if (pan < 0) volume_right = 1.0f - (-pan);
        *sample_out++ = *sample_out * volume_left;
        *sample_out++ = *sample_out * volume_right;
    }
}
void pan_mod(Sample_Info info, f32 tone_hz = 440)
{
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32 *sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 pan = (float)sin(t_sine);
        if (tone_hz == 0) pan = 0.0f;
        float volume_left = 1.0f;
        float volume_right = 1.0f;
        if (pan > 0) volume_left = 1.0f - pan;
        else if (pan < 0) volume_right = 1.0f - (-pan);
        *sample_out++ = *sample_out * volume_left;
        *sample_out++ = *sample_out * volume_right;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}

//}//namespace Tactics