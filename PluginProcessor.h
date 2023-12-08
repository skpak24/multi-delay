/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StkLite-4.6.2/Delay.h"
#define MAXDELAYMSEC 2000.0

//==============================================================================
/**
*/
class SamPPFinalMultiDelayAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    SamPPFinalMultiDelayAudioProcessor();
    ~SamPPFinalMultiDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamPPFinalMultiDelayAudioProcessor)
    
    void calcAlgorithmParams();
    int calcMsecToSamps(float msec, float samp);
    int calcBPMToSamps(float bpm, float samp);

    juce::AudioParameterFloat* dryParam;
    juce::AudioParameterFloat* wetParam;
    juce::AudioParameterFloat* mDelayBPMParam;
    
    juce::AudioParameterFloat* wetParamL1;
    juce::AudioParameterFloat* wetParamL2;
    juce::AudioParameterFloat* wetParamL3;
    juce::AudioParameterFloat* wetParamL4;
    juce::AudioParameterFloat* wetParamL5;
    juce::AudioParameterFloat* wetParamR1;
    juce::AudioParameterFloat* wetParamR2;
    juce::AudioParameterFloat* wetParamR3;
    juce::AudioParameterFloat* wetParamR4;
    juce::AudioParameterFloat* wetParamR5;

    juce::AudioParameterFloat* mFeedbackDbParamL1;
    juce::AudioParameterFloat* mFeedbackDbParamL2;
    juce::AudioParameterFloat* mFeedbackDbParamL3;
    juce::AudioParameterFloat* mFeedbackDbParamL4;
    juce::AudioParameterFloat* mFeedbackDbParamL5;
    juce::AudioParameterFloat* mFeedbackDbParamR1;
    juce::AudioParameterFloat* mFeedbackDbParamR2;
    juce::AudioParameterFloat* mFeedbackDbParamR3;
    juce::AudioParameterFloat* mFeedbackDbParamR4;
    juce::AudioParameterFloat* mFeedbackDbParamR5;

    stk::Delay mDelayL1;
    stk::Delay mDelayL2;
    stk::Delay mDelayL3;
    stk::Delay mDelayL4;
    stk::Delay mDelayL5;
    stk::Delay mDelayR1;
    stk::Delay mDelayR2;
    stk::Delay mDelayR3;
    stk::Delay mDelayR4;
    stk::Delay mDelayR5;
    
    float mWetGain, mDryGain;
    float mFs;
    
    float mWetGainL1;
    float mWetGainL2;
    float mWetGainL3;
    float mWetGainL4;
    float mWetGainL5;
    float mWetGainR1;
    float mWetGainR2;
    float mWetGainR3;
    float mWetGainR4;
    float mWetGainR5;

    float mFeedbackGainLinL1;
    float mFeedbackGainLinL2;
    float mFeedbackGainLinL3;
    float mFeedbackGainLinL4;
    float mFeedbackGainLinL5;
    float mFeedbackGainLinR1;
    float mFeedbackGainLinR2;
    float mFeedbackGainLinR3;
    float mFeedbackGainLinR4;
    float mFeedbackGainLinR5;

};
