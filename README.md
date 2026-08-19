
# Real-Time Audio Synthesizer

The synthezier interface directly with Windows Core Audio apis, using MMDevice API for discovering audio endpoints and WASAPI for initializing the audio render client and providing the buffers for rendering into. The audio samples are generated in code and copied into the provided buffers.

## Features
- Generation of sine, triangle, square, and saw waves in code.
- Volume control
- Panning
- Amplitude modulation
- Combining two waves together
- Play keyboard notes using keys on the keyboard
- Imgui for user interface controls

## Technical Description
Audio processing runs on a dedicated thread with time-critical priority, while the main thread handles UI and waveform visualization. The MMDevice API is used to obtain the default audio endpoint, and WASAPI provides audio buffers through event-driven notifications. The audio thread generates waveform samples and writes them directly into the provided buffers, applying effects and parameter adjustments as needed. The main thread renders the generated waveform and exposes synthesizer controls through ImGui.

## Requirements
- Visual Studio 2022 build tools

## Build
- Run build.bat while in developer command prompt in terminal or after running vcvarsall.bat

## Third-Party Libraries
This project stands on the shoulders of these fantastic open-source libraries:
* [GLFW](https://glfw.org) - Window management and input (zlib License)
* [Dear ImGui](https://github.com) - Graphical user interface (MIT License)
* [stb_image](https://github.com/nothings/stb) - Image loading (Public Domain / MIT)
