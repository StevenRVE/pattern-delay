#ifndef _H_CLOCK_
#define _H_CLOCK_

// classes
#include "observerPattern/subject.hpp"

// libs
#include <iostream>
#include <cstdint>
#include <array>
#include <cstring>

class Clock : public Subject
{
public:
    Clock();
    ~Clock() override;

    void updateTimePosition(double tick, double ticksPerBeat, double bpm, uint32_t frames);

    // getters
    double getBPM() const;
    uint32_t getFramesBlockSize() const;
    bool getBeatEnd(uint8_t divisionIndex);
    double getCounter(uint8_t divisionIndex);

    // setters
    void setSampleRate(double newSampleRate);

    // methods
    void calcBeatLengths();
    void setBeatLength(double division, uint8_t divisionIndex);
    void tickCounters();
    void wrapCounter(uint8_t divisionIndex);
    bool endOfBeat(uint8_t divisionIndex);

private:
    double beatsPerMinute = 120;
    uint32_t framesBlockSize = 128;

    // time
    double sampleRate = 48000;

    std::array<double, 13> counters{};
    std::array<double, 13> beatLengths{};
    std::array<bool, 13> beatEnds{};

    std::array<double, 13> divisionValues{
        4.0,         // "1/1"
        2.0,         // "1/2"
        1.333,       // "1/2T"
        1.0,         // "1/4"
        1.5,         // "1/4."
        0.666,       // "1/4T"
        0.5,         // "1/8"
        0.725,       // "1/8."
        0.333,       // "1/8T"
        0.25,        // "1/16"
        0.375,       // "1/16."
        0.166,       // "1/16T"
        0.125        // "1/32"
    };
};

#endif // _H_CLOCK_
