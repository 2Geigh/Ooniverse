#include <string.h>
#define GLFW_INCLUDE_NONE
#include "../include/GLFW/glfw3.h"
#include "../include/glad/glad.h"
#include <stdio.h>
#include <stdlib.h>

struct Screen {
  int width;
  int height;
  char title[16];
};

char *get_shader_content(const char *filename) {

  FILE *fp;
  long size = 0;
  char *shaderContent;

  // Read file to get size
  // in "rb", r is "read" and b is "open in binary mode" (no byte conversions
  // (e.g., translation of newlines))
  fp = fopen(filename, "rb");
  if (fp == NULL) {
    return "";
  }

  // Get size of file
  fseek(fp, 0L, SEEK_END); // Aligns the file for reading
  size =
      ftell(fp) +
      1; // Gets length of file based on current position indicator (SEEK_END)
  fclose(fp);

  // Read file for content
  fp = fopen(filename, "r");
  shaderContent = memset(
      malloc(size), '\0',
      size); // memset fills a block of memory with a specified value (pointer
             // to memory block, value to fill, number of bytes to fill)
  fread(shaderContent, 1, size - 1, fp);
  fclose(fp);

  return shaderContent;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  (void)window;
}

int main(void) {
  struct Screen viewport = {
      .width = 500,
      .height = 300,
      .title = "Ooniverse",
  };

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MacOS

  GLFWwindow *window = glfwCreateWindow(viewport.width, viewport.height,
                                        viewport.title, NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    return -1;
  }

  glViewport(0, 0, viewport.width, viewport.height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glad_glClearColor(0.1f, 0.3f, 0.9f, 1.0f);
    glad_glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents(); // checks for events (e.g. keyboard or mouse inputs)
  }

  glfwTerminate();
  return 0;
}
