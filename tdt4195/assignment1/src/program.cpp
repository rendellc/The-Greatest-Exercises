// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"

#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"

#include <array>

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
    

    // Get info about window
    int screen_w, screen_h;
    glfwGetWindowSize(window, &screen_w, &screen_h);

    // Define some geometry data
    auto coords = GetSquareCoords(1.9, 1.9);
    auto indices = GetSquareIndices();
    
    // Set up your scene here (create Vertex Array Objects, etc.)
    const auto VAO = SetupVAO(coords.data(), coords.size(), indices.data(), indices.size());
    
    Gloom::Shader shaders;
    shaders.makeBasicShader("../gloom/shaders/simple.vert", "../gloom/shaders/triangle.frag");
    GL_CALL(glUseProgram(shaders.get()));
    
    std::cout << "u_Color: " << glGetUniformLocation(shaders.get(), "u_Color") << std::endl;

    float green = 0.0;
    float step = 0.01;
    
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        // Set uniform
        GL_CALL(glUniform4f(glGetUniformLocation(shaders.get(), "u_Color"), 0.1, green, 0.1, 1.0));
        GL_CALL(glUniform2f(glGetUniformLocation(shaders.get(), "u_Screensize"), (float)screen_w, (float)screen_h));
        green += step;
        if (green  > 1.0 || green < 0.0){
            step *= -1;
        }

        // Draw your scene here
        GL_CALL(glBindVertexArray(VAO));
        GL_CALL(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0));
        //GL_CALL(glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_INT, (void*)0));
        //GL_CALL(glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_INT, (void*)0));

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
    }
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
