/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SamPPFinalMultiDelayAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    SamPPFinalMultiDelayAudioProcessorEditor (SamPPFinalMultiDelayAudioProcessor&);
    ~SamPPFinalMultiDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    // slider change
    void sliderValueChanged(juce::Slider * slider) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SamPPFinalMultiDelayAudioProcessor& audioProcessor;
    
    juce::Slider mDrySlider;
    juce::Slider mWetSlider;
    juce::Slider mDelayBPMSlider;
    
    juce::Slider mWetL1Slider;
    juce::Slider mWetL2Slider;
    juce::Slider mWetL3Slider;
    juce::Slider mWetL4Slider;
    juce::Slider mWetL5Slider;
    juce::Slider mWetR1Slider;
    juce::Slider mWetR2Slider;
    juce::Slider mWetR3Slider;
    juce::Slider mWetR4Slider;
    juce::Slider mWetR5Slider;
    
    juce::Slider mFeedbackGainL1Slider;
    juce::Slider mFeedbackGainL2Slider;
    juce::Slider mFeedbackGainL3Slider;
    juce::Slider mFeedbackGainL4Slider;
    juce::Slider mFeedbackGainL5Slider;
    juce::Slider mFeedbackGainR1Slider;
    juce::Slider mFeedbackGainR2Slider;
    juce::Slider mFeedbackGainR3Slider;
    juce::Slider mFeedbackGainR4Slider;
    juce::Slider mFeedbackGainR5Slider;

    juce::Label mDryLabel;
    juce::Label mWetLabel;
    juce::Label mDelayBPMLabel;
    
    juce::Label mWetL1Label;
    juce::Label mWetL2Label;
    juce::Label mWetL3Label;
    juce::Label mWetL4Label;
    juce::Label mWetL5Label;
    juce::Label mWetR1Label;
    juce::Label mWetR2Label;
    juce::Label mWetR3Label;
    juce::Label mWetR4Label;
    juce::Label mWetR5Label;

    juce::Label mFeedbackGainL1Label;
    juce::Label mFeedbackGainL2Label;
    juce::Label mFeedbackGainL3Label;
    juce::Label mFeedbackGainL4Label;
    juce::Label mFeedbackGainL5Label;
    juce::Label mFeedbackGainR1Label;
    juce::Label mFeedbackGainR2Label;
    juce::Label mFeedbackGainR3Label;
    juce::Label mFeedbackGainR4Label;
    juce::Label mFeedbackGainR5Label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamPPFinalMultiDelayAudioProcessorEditor)
};
