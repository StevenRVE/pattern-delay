//
// Created by StevenRVE on 7-4-2023.
//

#ifndef SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP
#define SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP

#include <cstdint>
#include <array>

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

    void generatePattern();
    void setPattern(uint8_t newPatternNumber);
    uint8_t getPatternNumber() const;

private:
    PatternType patternType = PATTERN_TYPE_RANDOM;
    uint8_t patternNumber;

    std::array<bool,8> pattern { 0 };
};


#endif //SVE_PATTERN_DELAY_PATTERNGENERATOR_HPP
