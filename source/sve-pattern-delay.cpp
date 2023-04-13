#include "sve-pattern-delay.hpp"

START_NAMESPACE_DISTRHO

   /**
      Plugin class constructor.
      You must set all parameter values to their defaults, matching the value in initParameter().
    */
PatternDelay::PatternDelay()
: Plugin(PARAM_COUNT, 0, 0),
  gain(0.0f),
  feedbackClean(0.5f),
  delayTimeClean(500),
  feedbackFX(0.5f),
  delayTimeFX(500),
  delayLineClean(getSampleRate(), 2),
  delayLineFX(getSampleRate(), 2)
{
    /**
      Initialize all our parameters to their defaults.
      In this example all parameters have 0 as default, so we can simply zero them.
    */
    patternGenerator.generateEuclideanSequence(0,0,0);
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

    switch (index)
    {
        // MASTER PARAMS
        case PARAM_GAIN:
            setParamProps(parameter, { .automatable=true, .min=-90.0f, .max=24.0f, .def=0.0f, .name="Gain", .symbol="gain"});
            break;
        case PARAM_FEEDBACK_CLEAN:
            setParamProps(parameter, { .automatable=true, .min=0.0f, .max=0.9f, .def=0.5f, .name="Feedback Clean", .symbol="feedbackClean"});
            break;
        case PARAM_DELAYTIME_CLEAN:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=100, .max=2000, .def=500, .name="Delay Time Clean", .symbol="delayTimeClean"});
            delayLineClean.setDistanceReadWriteHead(delayTimeClean);
            break;
        case PARAM_FEEDBACK_FX:
            setParamProps(parameter, { .automatable=true, .min=0.0f, .max=0.9f, .def=0.5f, .name="Feedback", .symbol="feedback FX"});
            break;
        case PARAM_DELAYTIME_FX:
            setParamProps(parameter, { .automatable=true, .integer=true, .min=100, .max=2000, .def=500, .name="Delay Time FX", .symbol="delayTimeFX"});
            delayLineFX.setDistanceReadWriteHead(delayTimeFX);
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
        // PARAMS
        case PARAM_GAIN:
            return gain;
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
    case PARAM_GAIN:
        gain = value;
        break;
    case PARAM_FEEDBACK_CLEAN:
        feedbackClean = value;
        break;
    case PARAM_DELAYTIME_CLEAN:
        delayTimeClean = value;
        delayLineClean.setDistanceReadWriteHead(delayTimeClean);
        break;
    case PARAM_FEEDBACK_FX:
        feedbackFX = value;
        break;
    case PARAM_DELAYTIME_FX:
        delayTimeFX = value;
        delayLineFX.setDistanceReadWriteHead(delayTimeFX);
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
  Run/process function for plugins with MIDI input.
*/
void PatternDelay::run(const float** inputs, float** outputs, uint32_t nframes)
{
    const float* const input  = inputs[0];
    /* */ float* const output = outputs[0];

    const float gainCoefficient = DB_CO(gain);

    for (uint32_t currentFrame=0; currentFrame < nframes; ++currentFrame)
    {
        delayLineClean.write(input[currentFrame] + delayLineClean.read() * feedbackClean);
        delayLineFX.write(input[currentFrame] + delayLineFX.read() * feedbackFX);

        output[currentFrame] = input[currentFrame] + delayLineClean.read() + delayLineFX.read();

        delayLineClean.tick();
        delayLineFX.tick();
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
