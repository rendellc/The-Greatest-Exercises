// Local headers
#include "program.hpp"
#include "mycamera.hpp"
#include "OBJLoader.hpp" 
#include "floats.hpp" 
#include "toolbox.hpp" 
#include "sceneGraph.hpp" 
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cmath>
#include <algorithm>

#define GL_CALL(statement) {\
    statement;\
    printGLError();\
}

unsigned int SetupVAO(float4* points, float4* colors, size_t n_points, unsigned int* indices, size_t n_indices) {
    unsigned int vaoID; 
    GL_CALL(glGenVertexArrays(1, &vaoID));
    GL_CALL(glBindVertexArray(vaoID));
    
    unsigned int bufferID[2]; 
    GL_CALL(glGenBuffers(2, bufferID));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID[0]));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, 4*n_points*sizeof(float), points, GL_STATIC_DRAW));
    GL_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GL_CALL(glEnableVertexAttribArray(0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID[1]));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, 4*n_points*sizeof(float), colors, GL_STATIC_DRAW));
    GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GL_CALL(glEnableVertexAttribArray(1));
    
    unsigned int indexID;
    GL_CALL(glGenBuffers(1, &indexID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices*sizeof(*indices), indices, GL_STATIC_DRAW));
    
    return vaoID;
}

unsigned int SetupVAO(Mesh& mesh) {
    return SetupVAO(
        &mesh.vertices.front(), &mesh.colours.front(), mesh.vertices.size(),
        &mesh.indices.front(), mesh.indices.size());
}

SceneNode* SetupSceneNode(Mesh& mesh) {
    const auto vaoID = SetupVAO(mesh);
    SceneNode* node = createSceneNode();
    node->vertexArrayObjectID = vaoID;
    node->VAOIndexCount = mesh.indices.size();

    return node;
}

void visitSceneNode(SceneNode* graph, glm::mat4 transformationThusFar, const MyCamera& camera) {
  // Transformations
  graph->currentTransformationMatrix = transformationThusFar 
    * glm::translate(glm::mat4(), {graph->position.x, graph->position.y, graph->position.z})
    * glm::translate(glm::mat4(), {graph->referencePoint.x, graph->referencePoint.y, graph->referencePoint.z})
    * glm::eulerAngleYXZ(graph->rotation.y, graph->rotation.x, graph->rotation.z)
    * glm::translate(glm::mat4(), {-graph->referencePoint.x, -graph->referencePoint.y, -graph->referencePoint.z});

  glm::mat4 mvp = glm::perspective(glm::radians(90.f), 4.f/3.f, 0.1f, 1000.f) 
    * glm::lookAt(glm::vec3(camera.x, camera.y, camera.z), glm::vec3(40, 0, 20), glm::vec3(0,1,0))
    * graph->currentTransformationMatrix;
  
  // Scene rendering
  GL_CALL(glUniformMatrix4fv(0, 1, false, glm::value_ptr(mvp)));
  GL_CALL(glBindVertexArray(graph->vertexArrayObjectID)); GL_CALL(glDrawElements(GL_TRIANGLES, graph->VAOIndexCount, GL_UNSIGNED_INT, (void*)0));

  for (SceneNode* child : graph->children) {
    visitSceneNode(child, graph->currentTransformationMatrix, camera);
  }
}

template<typename T>
int signof(T t) {
  return (T(0) < t) - (t < T(0));
}

void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    // Set up shader
    Gloom::Shader shaders;
    shaders.makeBasicShader("../gloom/shaders/simple.vert", "../gloom/shaders/simple.frag");
    GL_CALL(glUseProgram(shaders.get()));

    // Set up your scene here (create Vertex Array Objects, etc.)
    MyCamera camera;
    camera.setX(90.f);
    camera.setY(50.f);
    camera.setZ(50.f);

    // Setup meshes
    MinecraftCharacter character = loadMinecraftCharacterModel("../gloom/res/steve.obj");
    constexpr float tileWidth = 8.f;
    Mesh chessboard = generateChessboard(10, 7, tileWidth, {0.4, 0.4, 0.4, 1.0}, {0.6, 0.6, 0.6, 1.f});

    SceneNode* root = SetupSceneNode(chessboard);
    SceneNode* leftLeg = SetupSceneNode(character.leftLeg);
    SceneNode* rightLeg = SetupSceneNode(character.rightLeg);
    SceneNode* leftArm = SetupSceneNode(character.leftArm);
    SceneNode* rightArm = SetupSceneNode(character.rightArm);
    SceneNode* torso = SetupSceneNode(character.torso);
    SceneNode* head = SetupSceneNode(character.head);

    addChild(root, torso);
    torso->referencePoint = float3(0.f, 18.f, 0.f);
    addChild(torso, head);
    head->referencePoint = float3(0.f, 10.f, 0.f);
    addChild(torso, leftArm);
    leftArm->referencePoint = float3(-6.f, 23.f, 0.f);
    addChild(torso, rightArm);
    rightArm->referencePoint = float3(6.f, 23.f, 0.f);
    addChild(torso, leftLeg);
    leftLeg->referencePoint = float3(-2.f, 10.f, 0.f);
    addChild(torso, rightLeg);
    rightLeg->referencePoint = float3(2.f, 10.f, 0.f);
    
    // Setup path
    Path path("../gloom/pathFiles/coordinates_0.txt");

    // Rendering Loop
    double t = getTimeDeltaSeconds();
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw scene
        const float speed = 5.5f;
        const float2 goalPos = path.getCurrentWaypoint(tileWidth);

        const double dt = getTimeDeltaSeconds();
        t += dt;
        const float2 charPos = {torso->position.x, torso->position.z};
        const float2 diff = goalPos - charPos;

        const float diffYaw = atan2(diff.y, diff.x);
        const float errorYaw = torso->rotation.y - diffYaw;
        
        torso->rotation.y -= dt*errorYaw;

        if (errorYaw < 0.2) {
          torso->position.x += dt*speed*signof(diff.x);
          torso->position.z += dt*speed*signof(diff.y);
        }

        if (path.hasWaypointBeenReached(charPos, tileWidth)) {
          path.advanceToNextWaypoint();
          std::cout << "(" << goalPos.x << ", " << goalPos.y << ") waypoint reached, next waypoint (" 
            << path.getCurrentWaypoint(tileWidth).x << ", " << path.getCurrentWaypoint(tileWidth).y << ")" << std::endl;
        }

        torso->rotation.x = 0.05*sin(0.5*speed*t);
        const float legSpeed = 1.57;
        leftLeg->rotation.x = 0.6 * sin(legSpeed*t);
        rightLeg->rotation.x = -0.6 * sin(legSpeed*t);
        head->rotation.x = 0.1 * sin(t)*sin(t);
        leftArm->rotation.y = 0.2*sin(1.3*t);
        leftArm->rotation.x = 0.6*sin(3*t);
        rightArm->rotation.y = 0.2*sin(1.3*t);
        rightArm->rotation.x = 0.6*cos(3*t);

        visitSceneNode(root, glm::mat4(1.f), camera);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window, &camera);

        // Flip buffers
        glfwSwapBuffers(window);
    }
}


void handleKeyboardInput(GLFWwindow* window, MyCamera* camera)
{
    constexpr float step = 0.6;
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera->moveZ(step);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera->moveZ(-step);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera->moveX(-step);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera->moveX(step);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera->moveY(step);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera->moveY(-step);
    }
}
