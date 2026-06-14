cmake_minimum_required(VERSION 3.28.3)
project(Ooniverse)

# Dependencies
find_package( OpenGL REQUIRED )
find_package( glfw3 REQUIRED )

# Variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${SRC_DIR}/main.c)

add_library(glad STATIC ${SRC_DIR}/glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC /include)
# PUBLIC means that ${PROJECT_NAME} ***EXCLUDING its dependencies*** can access the directory
# PRIVATE means that ${PROJECT_NAME} ***and its dependencies*** can access the directory

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    glad
    ${CMAKE_DL_LIBS} # Needed for glad - https://stackoverflow.com/a/56842079/2394163
)
