#ifndef TASK1_HPP
#define TASK1_HPP

#include "program.hpp"
#include "vertexBuffer.h"

#define GL_CALL(statement) {\
    statement;\
    printGLError();\
}


unsigned int SetupVAO(const VertexBuffer& vertices, unsigned int* indices, size_t n_indices) {
    unsigned int vaoID; 
    GL_CALL(glGenVertexArrays(1, &vaoID));
    GL_CALL(glBindVertexArray(vaoID));
    
    // vertex buffer
    unsigned int bufferID; 
    GL_CALL(glGenBuffers(1, &bufferID));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.GetSizeInBytes(), vertices.GetRaw(), GL_STATIC_DRAW));
    

    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.GetStride(), (void*)vertices.GetCoordOffset()));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertices.GetStride(), (void*)vertices.GetColorOffset()));
    GL_CALL(glEnableVertexAttribArray(1));
    
    unsigned int indexID;
    GL_CALL(glGenBuffers(1, &indexID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices*sizeof(*indices), indices, GL_STATIC_DRAW));
    
    return vaoID;
}

VertexBuffer Task1Vertices(){
    VertexBuffer vertices;
    for (int row = 0; row < 5; row++) {
        int n_cols = 5 - row;
        for (int i = 0; i < n_cols; i++){
            std::array<float, 3> coord;
            coord[0] = -0.5 + 0.125*static_cast<float>(row) + 0.25*static_cast<float>(i);
            coord[1] = -0.5 + 0.25*static_cast<float>(row);
            coord[2] = 0.0;
            
            vertices.AddVertex(coord, CreateRandomColor());
        }
    }
    
    return std::move(vertices);
}

std::array<unsigned int,30> Task1Indices(){
    return {
        0,1,5,
        1,2,6,
        2,3,7,
        3,4,8,
        5,6,9,
        6,7,10,
        7,8,11,
        9,10,12,
        10,11,13,
        12,13,14
    };
}

#endif // TASK1_HPP
