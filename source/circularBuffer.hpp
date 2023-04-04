//
// Created by steve on 4-4-2023.
//

#ifndef SVE_PATTERN_DELAY_CIRCULARBUFFER_HPP
#define SVE_PATTERN_DELAY_CIRCULARBUFFER_HPP

#include <cstdint>

class CircularBuffer {
public:
    // constructor and destructor
    explicit CircularBuffer(uint32_t size);

    ~CircularBuffer();

    // methods
    void allocateBuffer();

    void releaseBuffer();

    void increaseReadHead();

    void increaseWriteHead();

    void wrapHead(uint32_t& head) const;

    void tick();

    void write(float value);

    float read();

    // setters and getters
    void setBufferSize(uint32_t size);

    void setDistanceReadWriteHead(uint32_t distance);

    uint32_t getDistanceReadWriteHead() const;

private:
    // variables
    float* buffer = nullptr;
    uint32_t bufferSize;
    uint32_t readHead;
    uint32_t writeHead;
    uint32_t distanceReadWriteHead;

};


#endif //SVE_PATTERN_DELAY_CIRCULARBUFFER_HPP
