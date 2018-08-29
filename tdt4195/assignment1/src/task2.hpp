
#ifndef TASK2_HPP
#define TASK2_HPP

std::array<float, 9> GetTask2aCoords() {
    return std::array<float, 9>({
        // x, y, z
        0.6, -0.8, -1.2,
        0.0, 0.4, 0.0,
        -0.8, 0.0, 1.2
    });
}

std::array<unsigned int, 9> GetTask2aIndices(){
    return std::array<unsigned int, 9>({
        0,1,2,
        3,4,5,
        6,7,8
    });
}


#endif // TASK2_HPP
