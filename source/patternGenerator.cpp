//
// Created by StevenRVE on 7-4-2023.
//

#include "patternGenerator.hpp"

PatternGenerator::PatternGenerator() :
    patternNumber(0)
{

}

PatternGenerator::~PatternGenerator() = default;

void PatternGenerator::generatePattern()
{

}

void PatternGenerator::setPattern(uint8_t newPatternNumber)
{
    if(newPatternNumber >= 0 && newPatternNumber < PATTERN_TYPE_COUNT)
    {
        this->patternNumber=newPatternNumber;
    }
}

uint8_t PatternGenerator::getPatternNumber() const
{
    return patternNumber;
}
