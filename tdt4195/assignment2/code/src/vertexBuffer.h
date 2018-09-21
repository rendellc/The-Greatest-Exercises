#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>

float randomFloat() {
    return static_cast<float>(rand())/static_cast<float>(RAND_MAX);
}

std::array<float,4> CreateRandomColor(){
    return {randomFloat(), randomFloat(), randomFloat(), randomFloat()};
}

class VertexBuffer {
private:
    std::vector<float> buffer;

public:
    void AddVertex(const std::array<float, 3>& coord, const std::array<float, 4>& color) {
        buffer.insert(buffer.end(), coord.cbegin(), coord.cend());
        buffer.insert(buffer.end(), color.cbegin(), color.cend());
    }
    
    float* GetRaw() const {
        return const_cast<float*>(&buffer.front());
    }
    
    size_t GetCoordOffset() const {
        return 0;
    }
    
    size_t GetColorOffset() const {
        return 3*sizeof(float);
    }
    
    size_t GetStride() const {
        return (3+4)*sizeof(float);
    }
    
    size_t GetSizeInBytes() const {
        return buffer.size()*sizeof(float);
    }
};

#endif // VERTEX_BUFFER_H
