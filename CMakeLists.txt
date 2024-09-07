cmake_minimum_required(VERSION 3.10)

project(AlpOpengl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SRC source/*.h source/*.hpp source/*.cpp source/shaders/* )
add_executable(AlpOpengl source/Main.cpp ${SRC})
include_directories(include/glm  source) 

if(WIN32)
    foreach(FILE ${SRC}) 
        get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

        string(REPLACE "/" "\\" GROUP "${GROUP}")

        if ("${FILE}" MATCHES ".\.cpp")
        set(GROUP "Source Files${GROUP}")
        elseif("${FILE}" MATCHES ".\.h" OR "${FILE}" MATCHES ".\.hpp")
        set(GROUP "Header Files${GROUP}")
        endif()

        source_group("${GROUP}" FILES "${FILE}")
    endforeach()

    set_target_properties(
        AlpOpengl PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "$(SolutionDir)..\\source")

    include_directories(external/glfw-3.3.7.bin.WIN64/glfw-3.3.7.bin.WIN64/include/GLFW external/glew-2.1.0-win32/glew-2.1.0/include/GL)
    target_link_libraries(AlpOpengl ${CMAKE_SOURCE_DIR}/external/glfw-3.3.7.bin.WIN64/glfw-3.3.7.bin.WIN64/lib-vc2022/glfw3.lib 
                                     ${CMAKE_SOURCE_DIR}/external/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64/glew32.lib
                                     opengl32.lib)

elseif(UNIX)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)
        


    target_link_libraries(AlpOpengl PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
        
    )
endif()
