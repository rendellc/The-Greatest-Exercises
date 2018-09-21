#ifndef TASK4_HPP
#define TASK4_HPP

#include "program.hpp"
#include "vertexBuffer.h"

#define GL_CALL(statement) {\
    statement;\
    printGLError();\
}


VertexBuffer Task4bVertices(){
    VertexBuffer vertices;
    vertices.AddVertex({-5, -5, -10}, CreateRandomColor());
    vertices.AddVertex({5, -5, -10}, CreateRandomColor());
    vertices.AddVertex({0, 10, -10}, CreateRandomColor());
    
    vertices.AddVertex({-5, -5, -30}, CreateRandomColor());
    vertices.AddVertex({5, -5, -30}, CreateRandomColor());
    vertices.AddVertex({0, 10, -30}, CreateRandomColor());
    

    vertices.AddVertex({0.5, 0.5, 0.5}, CreateRandomColor());
    vertices.AddVertex({0.75, 0.5, 0.7}, CreateRandomColor());
    vertices.AddVertex({0.5, 0.75, 0.9}, CreateRandomColor());
    
    return std::move(vertices);
}

std::array<unsigned int,30> Task4bIndices(){
    return {
        0,1,2,
        3,4,5,
        6,7,8
    };
}

#endif // TASK4_HPP
