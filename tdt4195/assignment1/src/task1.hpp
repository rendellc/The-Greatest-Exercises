#ifndef TASK1_HPP
#define TASK1_HPP

#include "program.hpp"

#define GL_CALL(statement) {\
    statement;\
    printGLError();\
}


unsigned int SetupVAO(float* points, size_t n_points, unsigned int* indices, size_t n_indices) {
    unsigned int vaoID; 
    GL_CALL(glGenVertexArrays(1, &vaoID));
    GL_CALL(glBindVertexArray(vaoID));
    
    unsigned int bufferID; 
    GL_CALL(glGenBuffers(1, &bufferID));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, n_points*sizeof(*points), points, GL_STATIC_DRAW));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GL_CALL(glEnableVertexAttribArray(0));
    
    unsigned int indexID;
    GL_CALL(glGenBuffers(1, &indexID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices*sizeof(*indices), indices, GL_STATIC_DRAW));
    
    return vaoID;
}

std::array<float, 33> Get5TrianglesCoords(){
    return std::array<float, 33>({
        // x, y, z
        0.1, 0.6, 0.0,
        0.5, 0.5, 0.0,
        0.0, 0.0, 0.0,
        -0.3, 0.2, 0.0,
        -1.0, 0.0, 0.0,
        -0.5, -0.7, 0.0,
        0.8, -0.2, 0.0,
        0.4, -0.7, 0.0,
        0.2, -0.8, 0.0,
        0.5, -0.9, 0.0,
        -0.1, -0.4, 0.0,
    });
}

std::array<unsigned int, 30> Get5TrianglesIndices(){
    return std::array<unsigned int, 30>({
        1,0,2,
        2,3,4,
        2,4,5,
        2,10,6,
        7,8,9
    });
}

#endif // TASK1_HPP
