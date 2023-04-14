//
// Created by StevenRVE on 7-4-2023.
//

#include "patternGenerator.hpp"

PatternGenerator::PatternGenerator()
:   patternNumber(0),
    generator(randomDevice()),
    distribution(0,99),
    euclideanGenerator()
{

}

PatternGenerator::~PatternGenerator() = default;

void PatternGenerator::selectPattern(uint8_t index)
{
    switch (index)
    {
        case PATTERN_TYPE_RANDOM:
            generateRandomNumber();
            break;
        case PATTERN_TYPE_EUCLIDEAN:
            // generate euclidean
            break;
        case PATTERN_TYPE_NTH:
            // generate nth
            break;
        default:
            break;
    }
}

void PatternGenerator::setPattern(uint8_t newPatternNumber)
{
    if(newPatternNumber >= 0 && newPatternNumber < PATTERN_TYPE_COUNT)
    {
        this->patternNumber=newPatternNumber;
        selectPattern(patternNumber);
    }
}

uint8_t PatternGenerator::getPatternNumber() const
{
    return patternNumber;
}

uint32_t PatternGenerator::generateRandomNumber()
{
    uint32_t randomNum = distribution(generator);
    std::cout << randomNum << std::endl;
    return randomNum;
}

void PatternGenerator::generateEuclideanSequence(uint32_t step, uint32_t pulse, uint32_t rota) {
    euclideanGenerator.calcEuclideanSequence(step, pulse, rota);
}

uint32_t PatternGenerator::getEuclideanSequenceValue(uint32_t index) {
    return euclideanGenerator.getSequenceValue(index);
}