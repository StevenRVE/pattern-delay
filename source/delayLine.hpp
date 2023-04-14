//
// Created by StevenRVE on 4-4-2023.
//

#ifndef SVE_PATTERN_DELAY_DELAYLINE_HPP
#define SVE_PATTERN_DELAY_DELAYLINE_HPP

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>

class DelayLine {
public:
    // constructor and destructor

    DelayLine(double sampleRate, uint32_t size);

    ~DelayLine();

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
    double sampleRate = 44100;
    float* buffer = nullptr;
    uint32_t bufferSize;
    uint32_t readHead = 0;
    uint32_t writeHead = 0;
    uint32_t distanceReadWriteHead = 0;

};


#endif //SVE_PATTERN_DELAY_DELAYLINE_HPP
