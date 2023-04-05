//
// Created by steve on 4-4-2023.
//

#include "delayLine.hpp"
#include <iostream>
#include <cstring>

DelayLine::DelayLine(uint32_t size) :
bufferSize(size)
{
    allocateBuffer();
}

DelayLine::~DelayLine()
{
    releaseBuffer();
}

// methods
void DelayLine::allocateBuffer()
{
    buffer = (float*)malloc(bufferSize * sizeof(float));
    memset(buffer, 0, bufferSize * sizeof(float));
}

void DelayLine::releaseBuffer()
{
    free(buffer);
}

void DelayLine::setBufferSize(unsigned int size)
{
    bufferSize = size;
    releaseBuffer();
    allocateBuffer();
}

void DelayLine::increaseReadHead()
{
    readHead++;
    wrapHead(readHead);
}

void DelayLine::increaseWriteHead()
{
    writeHead++;
    wrapHead(writeHead);
}

void DelayLine::wrapHead(unsigned int& head) const
{
    if (head >= bufferSize)
    {
        head -= bufferSize;
    }
}

void DelayLine::tick()
{
    increaseWriteHead();
    increaseReadHead();
}

void DelayLine::write(float value)
{
    buffer[writeHead] = value;
}

float DelayLine::read()
{
    return buffer[readHead];
}

void DelayLine::setDistanceReadWriteHead(unsigned int distance)
{
    distanceReadWriteHead = distance;
    readHead = writeHead - distanceReadWriteHead + bufferSize;
    wrapHead(readHead);
}

uint32_t DelayLine::getDistanceReadWriteHead() const
{
    return distanceReadWriteHead;
}

