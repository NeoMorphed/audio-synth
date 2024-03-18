#ifndef SOUND_FUNCTIONS_H
#define SOUND_FUNCTIONS_H

namespace Tactics {


inline f64 inc_time_val(f64 t_sine, int wave_period)
{
    // Maybe we should just make wave_period a float?
    t_sine += TAU / (f32)wave_period;
    if (t_sine >= TAU) t_sine -= TAU;
    return t_sine;
}
static void output_sine_wave(Sample_Info info, f32 tone_hz = 440, f32 tone_volume = 0.5) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32* sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 sine_value = (float)sin(t_sine);
        f32 sample_value = (sine_value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
static void output_square_wave(Sample_Info info, f32 tone_hz = 440, f32 tone_volume = 0.5, bool phase_shift = false) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    f32 *sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
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
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
static void output_saw_wave(Sample_Info info, f32 tone_hz = 440, f32 tone_volume = 0.5) {
    static f64 t_sine = 0;
    int wave_period = (int)(info.samples_per_second / tone_hz);

    float slope = (1 - 0 / (TAU - 0));
    f32 *sample_out = info.samples;
    for (int sample_index = 0; sample_index < info.sample_count; sample_index++) {
        f32 value = 0; 
        float t_sine_range_1_0 = 0.0f + slope * ((float)t_sine - 0.0f);
        value = lerp(-1.0f, 1.0f, t_sine_range_1_0);
        //value = (float)sin(t_sine) * tone_hz - (float)floor(sin(t_sine) * tone_hz);
        //printf("%f\n", t_sine_range_1_0);
        f32 sample_value = (value * tone_volume);
        //f32 sample_value = (f32)(2 + 5 * sin((2 * M_PI) / 2 * 2) + 0.5);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        t_sine = inc_time_val(t_sine, wave_period);
    }
}
static void add_by_osc2(Globals* globals, Sample_Info info, f32 tone_hz = 440, f32 tone_volume = 0.5) {
static void amplitude_mod(Sample_Info info, f32 tone_hz = 440);
static void output_noise(Sample_Info info, f32 tone_volume = 0.5);
static void pan(Sample_Info info, f32 tone_hz = 440, float pan = 0);
static void pan_mod(Sample_Info info, f32 tone_hz = 440);




}//namespace Tactics
#endif