//
// Created by steve on 4-4-2023.
//

#include "circularBuffer.hpp"
#include <iostream>
#include <cstring>

CircularBuffer::CircularBuffer(uint32_t size) :
bufferSize(size)
{
    allocateBuffer();
}

CircularBuffer::~CircularBuffer()
{
    releaseBuffer();
}

// methods
void CircularBuffer::allocateBuffer()
{
    buffer = (float*)malloc(bufferSize * sizeof(float));
    memset(buffer, 0, bufferSize * sizeof(float));
}

void CircularBuffer::releaseBuffer()
{
    free(buffer);
}

void CircularBuffer::setBufferSize(unsigned int size)
{
    bufferSize = size;
    releaseBuffer();
    allocateBuffer();
}

void CircularBuffer::increaseReadHead()
{
    readHead++;
    wrapHead(readHead);
}

void CircularBuffer::increaseWriteHead()
{
    writeHead++;
    wrapHead(writeHead);
}

void CircularBuffer::wrapHead(unsigned int& head) const
{
    if (head >= bufferSize)
    {
        head -= bufferSize;
    }
}

void CircularBuffer::tick()
{
    increaseWriteHead();
    increaseReadHead();
}

void CircularBuffer::write(float value)
{
    buffer[writeHead] = value;
}

float CircularBuffer::read()
{
    return buffer[readHead];
}

void CircularBuffer::setDistanceReadWriteHead(unsigned int distance)
{
    distanceReadWriteHead = distance;
    readHead = writeHead - distanceReadWriteHead + bufferSize;
    wrapHead(readHead);
}

uint32_t CircularBuffer::getDistanceReadWriteHead() const
{
    return distanceReadWriteHead;
}

