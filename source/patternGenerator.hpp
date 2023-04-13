//
// Created by StevenRVE on 7-4-2023.
//

#ifndef SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP
#define SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP

#include <iostream>
#include <cstdint>
#include <array>
#include <random>

class PatternGenerator {
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

private:
    PatternType patternType = PATTERN_TYPE_RANDOM;
    uint8_t patternNumber;

    std::random_device randomDevice;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution; // distribution in range [0, 99]

    std::array<bool,8> pattern { 0 };
};


#endif //SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP
