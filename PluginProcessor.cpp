/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamPPFinalMultiDelayAudioProcessor::SamPPFinalMultiDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(dryParam = new juce::AudioParameterFloat("Dry Mix", // parameterID,
          "Dry", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          50.0f)); // defaultValue
    addParameter(wetParam = new juce::AudioParameterFloat("Wet Mix", // parameterID,
          "Wet", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          50.0f)); // defaultValue
    addParameter(mDelayBPMParam = new juce::AudioParameterFloat("Delay Time (bpm)", // parameterID,
         "DelayTime", // parameterName,
         60.0f, // minValue,
         180.0f, // maxValue,
         120.0f)); // defaultValue
    addParameter(wetParamL1 = new juce::AudioParameterFloat("Wet Mix (L1)", // parameterID,
          "Wet L1", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamL2 = new juce::AudioParameterFloat("Wet Mix (L2)", // parameterID,
          "Wet L2", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamL3 = new juce::AudioParameterFloat("Wet Mix (L3)", // parameterID,
          "Wet L3", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamL4 = new juce::AudioParameterFloat("Wet Mix (L4)", // parameterID,
          "Wet L4", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamL5 = new juce::AudioParameterFloat("Wet Mix (L5)", // parameterID,
          "Wet L5", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamR1 = new juce::AudioParameterFloat("Wet Mix (R1)", // parameterID,
          "Wet R1", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamR2 = new juce::AudioParameterFloat("Wet Mix (R2)", // parameterID,
          "Wet R2", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamR3 = new juce::AudioParameterFloat("Wet Mix (R3)", // parameterID,
          "Wet R3", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamR4 = new juce::AudioParameterFloat("Wet Mix (R4)", // parameterID,
          "Wet R4", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(wetParamR5 = new juce::AudioParameterFloat("Wet Mix (R5)", // parameterID,
          "Wet R5", // parameterName,
          0.0f, // minValue,
          100.0f, // maxValue,
          0.0f)); // defaultValue
    addParameter(mFeedbackDbParamL1 = new juce::AudioParameterFloat("Feedback Db, Dotted Quarter (L)", // parameterID,
        "FB L1", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamL2 = new juce::AudioParameterFloat("Feedback Db, Quarter (L)", // parameterID,
        "FB L2", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamL3 = new juce::AudioParameterFloat("Feedback Db, Dotted Eighth (L)", // parameterID,
        "FB L3", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamL4 = new juce::AudioParameterFloat("Feedback Db, Eighth (L)", // parameterID,
        "FB L4", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamL5 = new juce::AudioParameterFloat("Feedback Db, Five Sixteenths (L)", // parameterID,
        "FB L5", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamR1 = new juce::AudioParameterFloat("Feedback Db, Dotted Quarter (R)", // parameterID,
        "FB R1", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamR2 = new juce::AudioParameterFloat("Feedback Db, Quarter (R)", // parameterID,
        "FB R2", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamR3 = new juce::AudioParameterFloat("Feedback Db, Dotted Eighth (R)", // parameterID,
        "FB R3", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamR4 = new juce::AudioParameterFloat("Feedback Db, Eighth (R)", // parameterID,
        "FB R4", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    addParameter(mFeedbackDbParamR5 = new juce::AudioParameterFloat("Feedback Db, Five Sixteenths (R)", // parameterID,
        "FB R5", // parameterName,
        -60.0f, // minValue,
        -1.0f, // maxValue,
        -60.0f)); // defaultValue
    
}

SamPPFinalMultiDelayAudioProcessor::~SamPPFinalMultiDelayAudioProcessor()
{
}

//==============================================================================
const juce::String SamPPFinalMultiDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamPPFinalMultiDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SamPPFinalMultiDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SamPPFinalMultiDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SamPPFinalMultiDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamPPFinalMultiDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SamPPFinalMultiDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamPPFinalMultiDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SamPPFinalMultiDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void SamPPFinalMultiDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
int SamPPFinalMultiDelayAudioProcessor::calcMsecToSamps(float msec, float samp)
{
    return (msec/1000)*samp;
}

int SamPPFinalMultiDelayAudioProcessor::calcBPMToSamps(float bpm, float samp)
{
    return 60*samp/bpm;
}

void SamPPFinalMultiDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    mFs = sampleRate;
    int maxSamps = calcMsecToSamps(MAXDELAYMSEC, mFs);

    mDelayL1.setMaximumDelay(maxSamps);
    mDelayL2.setMaximumDelay(maxSamps);
    mDelayL3.setMaximumDelay(maxSamps);
    mDelayL4.setMaximumDelay(maxSamps);
    mDelayL5.setMaximumDelay(maxSamps);
    mDelayR1.setMaximumDelay(maxSamps);
    mDelayR2.setMaximumDelay(maxSamps);
    mDelayR3.setMaximumDelay(maxSamps);
    mDelayR4.setMaximumDelay(maxSamps);
    mDelayR5.setMaximumDelay(maxSamps);
}

void SamPPFinalMultiDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SamPPFinalMultiDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SamPPFinalMultiDelayAudioProcessor::calcAlgorithmParams()
{
    mDryGain = dryParam->get()/100.0;
    mWetGain = wetParam->get()/100.0;
    
    mWetGainL1 = wetParamL1->get()/100.0;
    mWetGainL2 = wetParamL2->get()/100.0;
    mWetGainL3 = wetParamL3->get()/100.0;
    mWetGainL4 = wetParamL4->get()/100.0;
    mWetGainL5 = wetParamL5->get()/100.0;
    mWetGainR1 = wetParamR1->get()/100.0;
    mWetGainR2 = wetParamR2->get()/100.0;
    mWetGainR3 = wetParamR3->get()/100.0;
    mWetGainR4 = wetParamR4->get()/100.0;
    mWetGainR5 = wetParamR5->get()/100.0;

    //set delays
    int samps = calcBPMToSamps(mDelayBPMParam->get(), mFs);
    mDelayL1.setDelay(samps);
    mDelayL2.setDelay(samps);
    mDelayL3.setDelay(samps*0.75);
    mDelayL4.setDelay(samps*0.50);
    mDelayL5.setDelay(samps*1.25);
    mDelayR1.setDelay(samps);
    mDelayR2.setDelay(samps);
    mDelayR3.setDelay(samps*0.75);
    mDelayR4.setDelay(samps*0.50);
    mDelayR5.setDelay(samps*1.25);

    //set feedback gain
    mFeedbackGainLinL1 = powf(10.0, mFeedbackDbParamL1->get() * 0.05);
    mFeedbackGainLinL2 = powf(10.0, mFeedbackDbParamL2->get() * 0.05);
    mFeedbackGainLinL3 = powf(10.0, mFeedbackDbParamL3->get() * 0.05);
    mFeedbackGainLinL4 = powf(10.0, mFeedbackDbParamL4->get() * 0.05);
    mFeedbackGainLinL5 = powf(10.0, mFeedbackDbParamL5->get() * 0.05);
    mFeedbackGainLinR1 = powf(10.0, mFeedbackDbParamR1->get() * 0.05);
    mFeedbackGainLinR2 = powf(10.0, mFeedbackDbParamR2->get() * 0.05);
    mFeedbackGainLinR3 = powf(10.0, mFeedbackDbParamR3->get() * 0.05);
    mFeedbackGainLinR4 = powf(10.0, mFeedbackDbParamR4->get() * 0.05);
    mFeedbackGainLinR5 = powf(10.0, mFeedbackDbParamR5->get() * 0.05);
}

void SamPPFinalMultiDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    calcAlgorithmParams();


    float feedL1, feedL2, feedL3, feedL4, feedL5;
    float feedR1, feedR2, feedR3, feedR4, feedR5;
    float origL, origR, delayL, delayR;
    float delayedL1, delayedL2, delayedL3, delayedL4, delayedL5;
    float delayedR1, delayedR2, delayedR3, delayedR4, delayedR5;

    // Get the left and right audio buffers
    auto* channelDataLeft = buffer.getWritePointer(0);
    auto* channelDataRight = buffer.getWritePointer(1);
    
        
    for (int samp = 0; samp < buffer.getNumSamples(); samp++)
    {
        // future + feedback gain
        feedL1 = mDelayL1.lastOut() * mFeedbackGainLinL1;
        feedL2 = mDelayL2.lastOut() * mFeedbackGainLinL2;
        feedL3 = mDelayL3.lastOut() * mFeedbackGainLinL3;
        feedL4 = mDelayL4.lastOut() * mFeedbackGainLinL4;
        feedL5 = mDelayL5.lastOut() * mFeedbackGainLinL5;
        feedR1 = mDelayR1.lastOut() * mFeedbackGainLinR1;
        feedR2 = mDelayR2.lastOut() * mFeedbackGainLinR2;
        feedR3 = mDelayR3.lastOut() * mFeedbackGainLinR3;
        feedR4 = mDelayR4.lastOut() * mFeedbackGainLinR4;
        feedR5 = mDelayR5.lastOut() * mFeedbackGainLinR5;
        
        // combine with original + dry
        origL = channelDataLeft[samp] * mDryGain;
        origR = channelDataRight[samp] * mDryGain;
        
        // combine with delayed + wet
        delayedL1 = mDelayL1.tick(channelDataLeft[samp] + feedL1) * mWetGainL1;
        delayedL2 = mDelayL2.tick(channelDataLeft[samp] + feedL2) * mWetGainL2;
        delayedL3 = mDelayL3.tick(channelDataLeft[samp] + feedL3) * mWetGainL3;
        delayedL4 = mDelayL4.tick(channelDataLeft[samp] + feedL4) * mWetGainL4;
        delayedL5 = mDelayL5.tick(channelDataLeft[samp] + feedL5) * mWetGainL5;
        delayedR1 = mDelayR1.tick(channelDataLeft[samp] + feedR1) * mWetGainR1;
        delayedR2 = mDelayR2.tick(channelDataLeft[samp] + feedR2) * mWetGainR2;
        delayedR3 = mDelayR3.tick(channelDataLeft[samp] + feedR3) * mWetGainR3;
        delayedR4 = mDelayR4.tick(channelDataLeft[samp] + feedR4) * mWetGainR4;
        delayedR5 = mDelayR5.tick(channelDataLeft[samp] + feedR5) * mWetGainR5;
        
        delayL = (delayedL1 + delayedL2 + delayedL3 + delayedL4 + delayedL5) * mWetGain;
        delayR = (delayedR1 + delayedR2 + delayedR3 + delayedR4 + delayedR5) * mWetGain;

        channelDataLeft[samp] = origL + delayL;
        channelDataRight[samp] = origR + delayR;
//        channelDataLeft[samp] = origL + delayedL1;
//        channelDataRight[samp] = origR + delayedR1;
    }
}

//==============================================================================
bool SamPPFinalMultiDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SamPPFinalMultiDelayAudioProcessor::createEditor()
{
    return new SamPPFinalMultiDelayAudioProcessorEditor (*this);
}

//==============================================================================
void SamPPFinalMultiDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SamPPFinalMultiDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamPPFinalMultiDelayAudioProcessor();
}
