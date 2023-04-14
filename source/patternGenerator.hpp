//
// Created by StevenRVE on 7-4-2023.
//

#ifndef SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP
#define SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP

// libs
#include <iostream>
#include <cstdint>
#include <array>
#include <random>

// classes
#include "euclideanGenerator.hpp"
#include "observerPattern/observer.hpp"
#include "clock.hpp"

class PatternGenerator : public Observer
{
public:
    enum PatternType{
        PATTERN_TYPE_RANDOM,
        PATTERN_TYPE_EUCLIDEAN,
        PATTERN_TYPE_NTH,
        PATTERN_TYPE_COUNT
    };

    PatternGenerator();

    ~PatternGenerator();

    void selectPattern(uint8_t index);
    void setPattern(uint8_t newPatternNumber);
    uint8_t getPatternNumber() const;

    uint32_t generateRandomNumber();

    void generateEuclideanSequence(uint32_t step, uint32_t pulse, uint32_t rota);
    uint32_t getEuclideanSequenceValue(uint32_t stepIndex);

private:
    Clock& clock;

    PatternType patternType = PATTERN_TYPE_RANDOM;
    uint8_t patternNumber;

    // random
    std::random_device randomDevice;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution; // distribution in range [0, 99]

    // euclidean
    EuclideanGenerator euclideanGenerator;

    std::array<bool,16> pattern { 0 };
};


#endif //SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP
