#ifndef TASK3_HPP
#define TASK3_HPP

#include <vector>
#include <iostream>
#include <cmath>


std::vector<float> GetCircleCoords(const float angle_step = 0.1) {
    
    std::vector<float> circle = {0.0, 0.0, 0.0};

    for (float angle = 0; angle < 6.28; angle += angle_step){
        circle.push_back(0.9*cos(angle));   // x
        circle.push_back(0.9*sin(angle));   // y
        circle.push_back(0.0);              // z
    }

    return circle;
}
    
std::vector<unsigned int> GetCircleIndices(unsigned int N){
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < N/3; i++){
        indices.push_back(i);
    }
    
    indices.push_back(1); // closes the circle
    
    return indices;
}

std::vector<float> GetSpiralCoords(){
    std::vector<float> spiral = {0.0, 0.0, 0.0};

    float angle = 0.0;
    while (angle < 1.0) {
        spiral.push_back(angle*cos(4*2*3.14*angle));   // x
        spiral.push_back(angle*sin(4*2*3.14*angle));   // y
        spiral.push_back(0.0);              // z
        
        angle += 0.01;
    }

    return spiral;
}

std::vector<unsigned int> GetSpiralIndices(unsigned int N){
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < N/3; i++){
        indices.push_back(i);
    }
    
    return indices;
}

std::vector<float> GetSquareCoords(float w, float h){
    return {
        -w/2, -h/2, 0.0,
         w/2, -h/2, 0.0,
         w/2, h/2, 0.0,
         -w/2, h/2, 0.0,
    };
}

std::vector<unsigned int> GetSquareIndices(){
    return {
        0,1,2,
        2,3,0
    };
}



#endif // TASK2_HPP
