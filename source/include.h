#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #include "glew.h"
    #include "glfw3.h"
    #include "glm.hpp"
    #include "gtc/matrix_transform.hpp"
    #include "gtc/type_ptr.hpp"


#elif defined(__linux__)
    #include "GL/glew.h"
    #include "GLFW/glfw3.h"
    #include "glm/glm.hpp"
    #include "glm/gtc/matrix_transform.hpp"
    #include "glm/gtc/type_ptr.hpp"


#endif