//
// Created by StevenRVE on 4-4-2023.
//

#include "delayLine.hpp"



DelayLine::DelayLine(double sampleRate, uint32_t size) :
sampleRate(sampleRate),
bufferSize(sampleRate * size)
{
    std::cout << "DelayLine constructor" << "\n";
    allocateBuffer();
}

DelayLine::~DelayLine()
{
    std::cout << "DelayLine destructor" << "\n";
    releaseBuffer();
}

// methods
void DelayLine::allocateBuffer()
{
    std::cout << "Allocating buffer..." << "\n";
    buffer = new float[bufferSize]();
    std::fill_n(buffer, bufferSize, 0.0f);
}

void DelayLine::releaseBuffer()
{
    std::cout << "Releasing buffer...\n";
    delete[] buffer;
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

void DelayLine::setDistanceReadWriteHead(uint32_t distance)
{
    if (distance >= bufferSize)
    {
        distance = bufferSize - 1;
    }

    distanceReadWriteHead = distance * (sampleRate / 1000);
    std::cout << "distanceReadWriteHead: " << distanceReadWriteHead << "\n";
    readHead = writeHead - distanceReadWriteHead + bufferSize;
    wrapHead(readHead);
}

uint32_t DelayLine::getDistanceReadWriteHead() const
{
    return distanceReadWriteHead;
}
