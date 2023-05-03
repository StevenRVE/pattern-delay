#include "sve-pattern-delay.hpp"

START_NAMESPACE_DISTRHO

   /**
      Plugin class constructor.
      You must set all parameter values to their defaults, matching the value in initParameter().
    */
PatternDelay::PatternDelay()
:   Plugin(PARAM_COUNT, 0, 0),
    delayLineClean(getSampleRate(), 2),
    delayLineFX(getSampleRate(), 2),
    pattern(delayTimeFX, getSampleRate())
{
    /**
      Initialize all our parameters to their defaults.
      In this example all parameters have 0 as default, so we can simply zero them.
    */
    pattern.generateEuclideanSequence(0,0,0);
}


// -------------------------------------------------------------------
// Init
// -------------------------------------------------------------------

/**
  Initialize the parameter @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PatternDelay::initParameter(uint32_t index, Parameter& parameter)
{
    if (index >= PARAM_COUNT) { return; }

    struct ParamProps
    {
        bool automatable, boolean, integer, logarithmic, output, trigger;
        float min, max, def;
        const char* name;
        const char* symbol;
    };

    const auto setParamProps = [](auto& param, ParamProps props)
    {
        if(props.automatable){ param.hints = kParameterIsAutomatable;}
        if(props.boolean){param.hints = kParameterIsBoolean;}
        if(props.integer){param.hints = kParameterIsInteger;}
        if(props.logarithmic){param.hints = kParameterIsLogarithmic;}
        if(props.output){param.hints = kParameterIsOutput;}
        if(props.trigger){param.hints = kParameterIsTrigger | kParameterIsBoolean;}
        param.ranges.min = props.min;
        param.ranges.max = props.max;
        param.ranges.def = props.def;
        param.name = props.name;
        param.symbol = props.symbol;
    };
    
    const auto createPatternList = []
    {
        ParameterEnumerationValue* const patternList = new ParameterEnumerationValue[3];
        patternList[0].label = "Random";
        patternList[0].value = 0;
        patternList[1].label = "Euclidean";
        patternList[1].value = 1;
        patternList[2].label = "Nth";
        patternList[2].value = 2;
        return patternList;
    };

    switch (index)
    {
        // MASTER PARAMS
        case PARAM_FEEDBACK_CLEAN:
            setParamProps(parameter, { .automatable=true, .min=0.0f, .max=0.9f, .def=0.5f, .name="Feedback Clean", .symbol="feedbackClean"});
            break;
        case PARAM_DELAYTIME_CLEAN:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=100, .max=2000, .def=500, .name="Delay Time Clean", .symbol="delayTimeClean"});
            delayLineClean.setDistanceReadWriteHead(delayTimeClean);
            break;
        case PARAM_FEEDBACK_FX:
            setParamProps(parameter, { .automatable=true, .min=0.0f, .max=0.9f, .def=0.5f, .name="Feedback", .symbol="feedbackFX"});
            break;
        case PARAM_DELAYTIME_FX:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=100, .max=2000, .def=500, .name="Delay Time FX", .symbol="delayTimeFX"});
            delayLineFX.setDistanceReadWriteHead(delayTimeFX);
            break;
        case PARAM_PATTERN_TYPE:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=2, .def=0, .name="Pattern Type", .symbol="patternType"});
            parameter.enumValues.count = 3;
            parameter.enumValues.restrictedMode = true;
            parameter.enumValues.values = createPatternList();
            break;
        case PARAM_RANDOM_CHANCE:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=100, .def=50, .name="Random Chance", .symbol="randomChance"});
            pattern.setRandomChance(50);
            break;
        case PARAM_EUC_STEPS:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=16, .def=0, .name="Euclidean Steps", .symbol="eucSteps"});
            break;
        case PARAM_EUC_PULSE:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=16, .def=0, .name="Euclidean Pulse", .symbol="eucPulse"});
            break;
        case PARAM_EUC_ROTATION:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=15, .def=0, .name="Euclidean Rotation", .symbol="eucRotation"});
            break;
        case PARAM_NTH:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=16, .def=0, .name="N-th", .symbol="nth"});
            break;
        case PARAM_NTH_ROTATION:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=0, .max=15, .def=0, .name="N-th Rotation", .symbol="nthRotation"});
            break;
        default:
            break;
    }
}

// -------------------------------------------------------------------
// Internal data
// -------------------------------------------------------------------

/**
  Get the current value of a parameter.
  The host may call this function from any context, including realtime processing.
*/
float PatternDelay::getParameterValue(uint32_t index) const
{
    switch (index)
    {
        // Delay Clean
        case PARAM_FEEDBACK_CLEAN:
            return feedbackClean;
        case PARAM_DELAYTIME_CLEAN:
            return delayTimeClean;
        // Delay FX
        case PARAM_FEEDBACK_FX:
            return feedbackFX;
        case PARAM_DELAYTIME_FX:
            return delayTimeFX;
        // Pattern
        case PARAM_PATTERN_TYPE:
            return patternType;
        case PARAM_RANDOM_CHANCE:
            return randomChance;
        case PARAM_EUC_STEPS:
            return eucSteps;
        case PARAM_EUC_PULSE:
            return eucPulse;
        case PARAM_EUC_ROTATION:
            return eucRota;
        case PARAM_NTH:
            return nth;
        case PARAM_NTH_ROTATION:
            return nthRota;
        default:
            return 0;
    }
}

/**
  Change a parameter value.
  The host may call this function from any context, including realtime processing.
  When a parameter is marked as automable, you must ensure no non-realtime
  operations are performed.
*/
void PatternDelay::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    // MASTER PARAMS
    case PARAM_FEEDBACK_CLEAN:
        this->feedbackClean = value;
        break;
    case PARAM_DELAYTIME_CLEAN:
        this->delayTimeClean = value;
        delayLineClean.setDistanceReadWriteHead(delayTimeClean);
        break;
    case PARAM_FEEDBACK_FX:
        this->feedbackFX = value;
        break;
    case PARAM_DELAYTIME_FX:
        this->delayTimeFX = value;
        delayLineFX.setDistanceReadWriteHead(delayTimeFX);
        pattern.calcDelayTimeSamples(delayTimeFX);
        break;
    case PARAM_PATTERN_TYPE:
        this->patternType = value;
        std::cout << "setting patterType to: " << value << "\n";
        pattern.setPattern(value);
        break;
    case PARAM_RANDOM_CHANCE:
        this->randomChance = value;
        pattern.setRandomChance(value);
        break;
    case PARAM_EUC_STEPS:
        this->eucSteps = value;
        pattern.generateEuclideanSequence(value, eucPulse, eucRota);
        break;
    case PARAM_EUC_PULSE:
        this->eucPulse = value;
            pattern.generateEuclideanSequence(eucSteps, value, eucRota);
        break;
    case PARAM_EUC_ROTATION:
        this->eucRota = value;
        pattern.generateEuclideanSequence(eucSteps, eucPulse, value);
        break;
    case PARAM_NTH:
        this->nth = value;
        pattern.generateNthSequence(value, nthRota);
        break;
    case PARAM_NTH_ROTATION:
        this->nthRota = value;
        pattern.generateNthSequence(nth, value);
        break;
    default:
        break;
    }
}

// -------------------------------------------------------------------
// methods
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// Process

void PatternDelay::activate()
{
    // plugin is activated
}

void PatternDelay::deactivate()
{
    // plugin is deactivated
}

/**
  Run/process function for plugins without MIDI input.
*/
void PatternDelay::run(const float** inputs, float** outputs, uint32_t nframes)
{
    const float* const input  = inputs[0];
    /* */ float* outputClean  = outputs[0];
    /* */ float* outputFX     = outputs[1];

    for (uint32_t currentFrame=0; currentFrame < nframes; ++currentFrame)
    {
        if (pattern.getCurrentValue())
        {
            delayLineFX.write(input[currentFrame] + delayLineFX.read() * feedbackFX);
        }
        else {
            delayLineClean.write(input[currentFrame] + delayLineClean.read() * feedbackClean);
        }

        outputClean[currentFrame] = input[currentFrame] + delayLineClean.read();
        outputFX[currentFrame] = delayLineFX.read();

        delayLineClean.tick();
        delayLineFX.tick();
        pattern.tick();
    }
}

// -------------------------------------------------------------------
// callbacks

/**
    Optional callback to inform the plugin about a sample rate change.
    This function will only be called when the plugin is deactivated.
*/
void PatternDelay::sampleRateChanged(double newSampleRate)
{
    (void)newSampleRate;
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new PatternDelay();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
