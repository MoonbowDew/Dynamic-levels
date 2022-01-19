#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "custom/Scene.h"
#include "custom/Profiler.h"

//static void cursor_pos_callback(GLFWwindow* window, double xposMouse, double yposMouse);


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // mode
    void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods); // read mouse clicks

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Fallout of Dew", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* Check if Glew works fine*/
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    /* Print out OpenGL Version*/
    std::cout << glGetString(GL_VERSION) << std::endl;


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    //glfwSetCursorPosCallback(window, Scene::cursor_pos_callback);
    

    Renderer renderer;


    Scene game;

    // Enable depth test
    //glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    //glDepthFunc(GL_LESS);

    glfwSetKeyCallback(window, Scene::key_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        /* Render here */
        renderer.Clear();
        {
            LOG_DURATION("OnUpdate")
        game.OnUpdate(window, 0.0f);
        }
        {
            LOG_DURATION("OnRender")
            game.OnRender(window);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }
    //delete game;
    glfwTerminate();
    return 0;
}

