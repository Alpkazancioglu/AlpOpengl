#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "glew.h"
    #include "glfw3.h"

#elif defined(__linux__)
    #include "GL/glew.h"
    #include "GLFW/glfw3.h"


#endif