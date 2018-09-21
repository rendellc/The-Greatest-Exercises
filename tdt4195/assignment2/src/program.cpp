// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
    
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "vertexBuffer.h"
#include "mycamera.hpp"
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

#include <array>
#include <cstdlib>


void runProgram(GLFWwindow* window)
{
    // System setup
    srand(static_cast<unsigned>(time(0)));
    
    // Enable depth (Z) buffer (accept "closest" fragment)
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    //glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    //GL_CALL(glEnable(GL_CULL_FACE));
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Set default colour after clearing the colour buffer
    glClearColor(0.1, 0.1, 0.1, 1.0f);

    // Get info about window
    int screen_w, screen_h;
    glfwGetWindowSize(window, &screen_w, &screen_h);
    glfwSetWindowTitle(window, "r: 0.0, g: 0.0, b:0.0, draw order: b->g->r");

    
    // Set up your scene here (create Vertex Array Objects, etc.)
    VertexBuffer vertices = Task2Vertices();
    auto indices = Task2Indices();
    const auto VAO = SetupVAO(vertices, indices.data(), indices.size());
    
    Gloom::Shader shaders;
    shaders.makeBasicShader("../gloom/shaders/simple.vert", "../gloom/shaders/simple.frag");
    GL_CALL(glUseProgram(shaders.get()));
    
    // uniform related
    float val = 0;
    float step = 0.01;
    glm::mat4 projection = glm::perspective(glm::radians(45.f), 1.3f, 1.f, 100.f);
    
    MyCamera camera;
    
    glm::vec4 testing = {0.f, 0.f, -30.f, 1.f};
    
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update uniforms
        if (fabs(val) > 0.5) {
            step = -step;
        }
        val += step;
        //GL_CALL(glUniform1f(2, val)); // Task 3
        
        
        //std::cout << camera.x << " " << camera.y << " " << camera.z << " " << camera.pitch << " " << camera.yaw << std::endl;
        
        
        
        glm::mat4x4 cameraMatrix = glm::translate(glm::vec3(-camera.x, -camera.y, -camera.z)) * glm::yawPitchRoll(-camera.yaw, -camera.pitch, 0.f);
        
        glm::mat4x4 u_Transform = projection * cameraMatrix;
        
        auto t = u_Transform * testing;
        std::cout << t.x/t.w << " " << t.y/t.w << " " << t.z/t.w << " " << t.w/t.w << std::endl;
        
        //GL_CALL(glUniformMatrix4fv(2, 1, false, glm::value_ptr(u_Transform)));

        // Draw your scene here
        GL_CALL(glBindVertexArray(VAO));
        GL_CALL(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0));

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window, &camera);

        // Flip buffers
        glfwSwapBuffers(window);
    }
}

void handleKeyboardInput(GLFWwindow* window, MyCamera* camera)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera->moveZ(-0.1);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera->moveZ(0.1);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->moveX(-0.1);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->moveX(0.1);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->moveY(0.1);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->moveY(-0.1);
    }
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        camera->changePitch(-0.01);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        camera->changePitch(0.01);
    }
    else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        camera->changeYaw(-0.01);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        camera->changeYaw(0.01);
    }

}
