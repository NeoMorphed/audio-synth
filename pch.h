#include <assert.h>
#include <windows.h>
#include <initguid.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Typedefs.h"
#include "vendor/stb_image/stb_image.h"
#include <unordered_map>
#include "input/KeyCodes.h"
#include "input/MouseButtonCodes.h"
#include "input/GamepadButtonCodes.h"
#include <math.h>
#include "core/Log.h"