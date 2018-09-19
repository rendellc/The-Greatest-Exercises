#ifndef TASK2_HPP
#define TASK2_HPP

#include "vertexBuffer.h"

VertexBuffer Task2Vertices() {
    VertexBuffer vs;
    vs.AddVertex({-0.1, -0.4, -0.5}, {1,0,0,0.3});
    vs.AddVertex({-0.4, -0.1, -0.5}, {1,0,0,0.3});
    vs.AddVertex({ 0.1,  0.1, -0.5}, {1,0,0,0.3});
    
    vs.AddVertex({ 0.1, -0.4, 0.0}, {0,1,0,0.3});
    vs.AddVertex({ 0.4, -0.1, 0.0}, {0,1,0,0.3});
    vs.AddVertex({-0.1,  0.1, 0.0}, {0,1,0,0.3});

    vs.AddVertex({ 0.4,  0.4, 0.5}, {0,0,1,0.3});
    vs.AddVertex({-0.4,  0.4, 0.5}, {0,0,1,0.3});
    vs.AddVertex({ 0.0, -0.1, 0.5}, {0,0,1,0.3});
    
    return std::move(vs);
}

std::array<unsigned int, 9> Task2Indices(){
    return {
        6,7,8,
        3,4,5,
        0,2,1,
    };
}

#endif // TASK2_HPP
