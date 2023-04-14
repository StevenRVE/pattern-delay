#include "clock.hpp"

Clock::Clock()
{
    counters.fill(0.0);
    beatLengths.fill(0.0);
    beatEnds.fill(false);
}

Clock::~Clock()
{

}

void Clock::updateTimePosition(double tick, double ticksPerBeat, double bpm, uint32_t frames)
{
    framesBlockSize = frames;
    beatsPerMinute = bpm;

    calcBeatLengths();

    tickCounters();

    for(uint8_t i = 0; i < beatEnds.size(); i++)
    {
        if(counters[i] >= (beatLengths[i] - 1))
        {
            beatEnds[i] = true;
        } else
        {
            beatEnds[i] = false;
        }
    }

    notify();
}

// getters

double Clock::getBPM() const
{
    return beatsPerMinute;
}

uint32_t Clock::getFramesBlockSize() const
{
    return framesBlockSize;
}

bool Clock::getBeatEnd(uint8_t divisionIndex)
{
    return beatEnds[divisionIndex];
}

double Clock::getCounter(uint8_t divisionIndex)
{
    return counters[divisionIndex];
}

// setters
void Clock::setSampleRate(double newSampleRate)
{
    sampleRate = newSampleRate;
}

void Clock::calcBeatLengths()
{
    for(uint8_t i = 0; i < divisionValues.size(); i++)
    {
        setBeatLength(divisionValues[i], i);
    }
}

// methods
void Clock::setBeatLength(double division, uint8_t divisionIndex)
{
    double secondsPerBeat = 60.0 / (beatsPerMinute / division);
    double framesPerBeat  = sampleRate * secondsPerBeat;
    double beatLength     = framesPerBeat / (double)framesBlockSize;

    beatLengths[divisionIndex] = beatLength;
}

void Clock::tickCounters()
{
    for(uint8_t i = 0; i < counters.size(); i++)
    {
        counters[i]++;
        wrapCounter(i);
    }
}

void Clock::wrapCounter(uint8_t divisionIndex)
{
    if(endOfBeat(divisionIndex))
    {
        counters[divisionIndex] = 0;
    }
}

bool Clock::endOfBeat(uint8_t divisionIndex)
{
    return counters[divisionIndex] > beatLengths[divisionIndex];
}
