/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamPPFinalMultiDelayAudioProcessorEditor::SamPPFinalMultiDelayAudioProcessorEditor (SamPPFinalMultiDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1260, 480);
    auto& params = processor.getParameters();
    
    // Dry Gain Slider
    juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
    mDrySlider.setBounds(560, 130, 50, 230);
    mDrySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mDrySlider.setRange(audioParam->range.start, audioParam->range.end);
    mDrySlider.setValue(*audioParam);
    mDrySlider.addListener(this);
    addAndMakeVisible(mDrySlider);
    mDrySlider.setTextValueSuffix("%");
    mDrySlider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mDryLabel);
    mDryLabel.setText ("Dry", juce::dontSendNotification);
    mDryLabel.setJustificationType(juce::Justification::centred);
    mDryLabel.attachToComponent (&mDrySlider, false);
    
    // Wet Gain Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
    mWetSlider.setBounds(650, 130, 50, 230);
    mWetSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetSlider.setRange(audioParam->range.start, audioParam->range.end);
    mWetSlider.setValue(*audioParam);
    mWetSlider.addListener(this);
    addAndMakeVisible(mWetSlider);
    mWetSlider.setTextValueSuffix("%");
    mWetSlider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetLabel);
    mWetLabel.setText ("Wet", juce::dontSendNotification);
    mWetLabel.setJustificationType(juce::Justification::centred);
    mWetLabel.attachToComponent (&mWetSlider, false);
    
    // BPM Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
    mDelayBPMSlider.setBounds(540, 390, 180, 50);
    mDelayBPMSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mDelayBPMSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mDelayBPMSlider.setRange(audioParam->range.start, audioParam->range.end);
    mDelayBPMSlider.setValue(*audioParam);
    mDelayBPMSlider.addListener(this);
    addAndMakeVisible(mDelayBPMSlider);
    mDelayBPMSlider.setTextValueSuffix(" bpm");
    mDelayBPMSlider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mDelayBPMLabel);
    mDelayBPMLabel.setJustificationType(juce::Justification::centred);
    mDelayBPMLabel.attachToComponent (&mDelayBPMSlider, false);
    
    // Wet L1 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
    mWetL1Slider.setBounds(65, 110, 50, 180);
    mWetL1Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetL1Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetL1Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetL1Slider.setValue(*audioParam);
    mWetL1Slider.addListener(this);
    addAndMakeVisible(mWetL1Slider);
    mWetL1Slider.setTextValueSuffix("%");
    mWetL1Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetL1Label);
    mWetL1Label.setText ("Half", juce::dontSendNotification);
    mWetL1Label.setJustificationType(juce::Justification::centred);
    mWetL1Label.attachToComponent (&mWetL1Slider, false);
    
    // Wet L2 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(4);
    mWetL2Slider.setBounds(155, 110, 50, 180);
    mWetL2Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetL2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetL2Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetL2Slider.setValue(*audioParam);
    mWetL2Slider.addListener(this);
    addAndMakeVisible(mWetL2Slider);
    mWetL2Slider.setTextValueSuffix("%");
    mWetL2Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetL2Label);
    mWetL2Label.setText ("Quarter", juce::dontSendNotification);
    mWetL2Label.setJustificationType(juce::Justification::centred);
    mWetL2Label.attachToComponent (&mWetL2Slider, false);
    
    // Wet L3 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(5);
    mWetL3Slider.setBounds(245, 110, 50, 180);
    mWetL3Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetL3Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetL3Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetL3Slider.setValue(*audioParam);
    mWetL3Slider.addListener(this);
    addAndMakeVisible(mWetL3Slider);
    mWetL3Slider.setTextValueSuffix("%");
    mWetL3Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetL3Label);
    mWetL3Label.setText ("D. Eighth", juce::dontSendNotification);
    mWetL3Label.setJustificationType(juce::Justification::centred);
    mWetL3Label.attachToComponent (&mWetL3Slider, false);
    
    // Wet L4 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(6);
    mWetL4Slider.setBounds(335, 110, 50, 180);
    mWetL4Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetL4Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetL4Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetL4Slider.setValue(*audioParam);
    mWetL4Slider.addListener(this);
    addAndMakeVisible(mWetL4Slider);
    mWetL4Slider.setTextValueSuffix("%");
    mWetL4Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetL4Label);
    mWetL4Label.setText ("Eighth", juce::dontSendNotification);
    mWetL4Label.setJustificationType(juce::Justification::centred);
    mWetL4Label.attachToComponent (&mWetL4Slider, false);
    
    // Wet L5 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(7);
    mWetL5Slider.setBounds(425, 110, 50, 180);
    mWetL5Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetL5Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetL5Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetL5Slider.setValue(*audioParam);
    mWetL5Slider.addListener(this);
    addAndMakeVisible(mWetL5Slider);
    mWetL5Slider.setTextValueSuffix("%");
    mWetL5Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetL5Label);
    mWetL5Label.setText ("5/16", juce::dontSendNotification);
    mWetL5Label.setJustificationType(juce::Justification::centred);
    mWetL5Label.attachToComponent (&mWetL5Slider, false);
    
    // Wet R1 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(8);
    mWetR1Slider.setBounds(785, 110, 50, 180);
    mWetR1Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetR1Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetR1Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetR1Slider.setValue(*audioParam);
    mWetR1Slider.addListener(this);
    addAndMakeVisible(mWetR1Slider);
    mWetR1Slider.setTextValueSuffix("%");
    mWetR1Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetR1Label);
    mWetR1Label.setText ("Half", juce::dontSendNotification);
    mWetR1Label.setJustificationType(juce::Justification::centred);
    mWetR1Label.attachToComponent (&mWetR1Slider, false);
    
    // Wet R2 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(9);
    mWetR2Slider.setBounds(875, 110, 50, 180);
    mWetR2Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetR2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetR2Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetR2Slider.setValue(*audioParam);
    mWetR2Slider.addListener(this);
    addAndMakeVisible(mWetR2Slider);
    mWetR2Slider.setTextValueSuffix("%");
    mWetR2Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetR2Label);
    mWetR2Label.setText ("Quarter", juce::dontSendNotification);
    mWetR2Label.setJustificationType(juce::Justification::centred);
    mWetR2Label.attachToComponent (&mWetR2Slider, false);
    
    // Wet R3 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(10);
    mWetR3Slider.setBounds(965, 110, 50, 180);
    mWetR3Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetR3Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetR3Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetR3Slider.setValue(*audioParam);
    mWetR3Slider.addListener(this);
    addAndMakeVisible(mWetR3Slider);
    mWetR3Slider.setTextValueSuffix("%");
    mWetR3Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetR3Label);
    mWetR3Label.setText ("D. Eighth", juce::dontSendNotification);
    mWetR3Label.setJustificationType(juce::Justification::centred);
    mWetR3Label.attachToComponent (&mWetR3Slider, false);
    
    // Wet R4 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(11);
    mWetR4Slider.setBounds(1055, 110, 50, 180);
    mWetR4Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetR4Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetR4Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetR4Slider.setValue(*audioParam);
    mWetR4Slider.addListener(this);
    addAndMakeVisible(mWetR4Slider);
    mWetR4Slider.setTextValueSuffix("%");
    mWetR4Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetR4Label);
    mWetR4Label.setText ("Eighth", juce::dontSendNotification);
    mWetR4Label.setJustificationType(juce::Justification::centred);
    mWetR4Label.attachToComponent (&mWetR4Slider, false);
    
    // Wet R5 Slider
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(12);
    mWetR5Slider.setBounds(1145, 110, 50, 180);
    mWetR5Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mWetR5Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mWetR5Slider.setRange(audioParam->range.start, audioParam->range.end);
    mWetR5Slider.setValue(*audioParam);
    mWetR5Slider.addListener(this);
    addAndMakeVisible(mWetR5Slider);
    mWetR5Slider.setTextValueSuffix("%");
    mWetR5Slider.setNumDecimalPlacesToDisplay(0);

    addAndMakeVisible(mWetR5Label);
    mWetR5Label.setText ("5/16", juce::dontSendNotification);
    mWetR5Label.setJustificationType(juce::Justification::centred);
    mWetR5Label.attachToComponent (&mWetR5Slider, false);
    
    
    // FeedbackGain L1 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(13);
    mFeedbackGainL1Slider.setBounds(55, 370, 70, 70);
    mFeedbackGainL1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainL1Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainL1Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainL1Slider.setValue(*audioParam);
    mFeedbackGainL1Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainL1Slider);
    mFeedbackGainL1Slider.setTextValueSuffix("dB");
    mFeedbackGainL1Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain L2 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(14);
    mFeedbackGainL2Slider.setBounds(145, 370, 70, 70);
    mFeedbackGainL2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainL2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainL2Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainL2Slider.setValue(*audioParam);
    mFeedbackGainL2Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainL2Slider);
    mFeedbackGainL2Slider.setTextValueSuffix("dB");
    mFeedbackGainL2Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain L3 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(15);
    mFeedbackGainL3Slider.setBounds(235, 370, 70, 70);
    mFeedbackGainL3Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainL3Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainL3Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainL3Slider.setValue(*audioParam);
    mFeedbackGainL3Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainL3Slider);
    mFeedbackGainL3Slider.setTextValueSuffix("dB");
    mFeedbackGainL3Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain L4 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(16);
    mFeedbackGainL4Slider.setBounds(325, 370, 70, 70);
    mFeedbackGainL4Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainL4Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainL4Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainL4Slider.setValue(*audioParam);
    mFeedbackGainL4Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainL4Slider);
    mFeedbackGainL4Slider.setTextValueSuffix("dB");
    mFeedbackGainL4Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain L5 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(17);
    mFeedbackGainL5Slider.setBounds(415, 370, 70, 70);
    mFeedbackGainL5Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainL5Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainL5Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainL5Slider.setValue(*audioParam);
    mFeedbackGainL5Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainL5Slider);
    mFeedbackGainL5Slider.setTextValueSuffix("dB");
    mFeedbackGainL5Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain R1 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(18);
    mFeedbackGainR1Slider.setBounds(775, 370, 70, 70);
    mFeedbackGainR1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainR1Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainR1Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainR1Slider.setValue(*audioParam);
    mFeedbackGainR1Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainR1Slider);
    mFeedbackGainR1Slider.setTextValueSuffix("dB");
    mFeedbackGainR1Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain R2 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(19);
    mFeedbackGainR2Slider.setBounds(865, 370, 70, 70);
    mFeedbackGainR2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainR2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainR2Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainR2Slider.setValue(*audioParam);
    mFeedbackGainR2Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainR2Slider);
    mFeedbackGainR2Slider.setTextValueSuffix("dB");
    mFeedbackGainR2Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain R3 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(20);
    mFeedbackGainR3Slider.setBounds(955, 370, 70, 70);
    mFeedbackGainR3Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainR3Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainR3Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainR3Slider.setValue(*audioParam);
    mFeedbackGainR3Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainR3Slider);
    mFeedbackGainR3Slider.setTextValueSuffix("dB");
    mFeedbackGainR3Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain R4 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(21);
    mFeedbackGainR4Slider.setBounds(1045, 370, 70, 70);
    mFeedbackGainR4Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainR4Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainR4Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainR4Slider.setValue(*audioParam);
    mFeedbackGainR4Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainR4Slider);
    mFeedbackGainR4Slider.setTextValueSuffix("dB");
    mFeedbackGainR4Slider.setNumDecimalPlacesToDisplay(1);
    
    // FeedbackGain R5 Rotary
    audioParam = (juce::AudioParameterFloat*)params.getUnchecked(22);
    mFeedbackGainR5Slider.setBounds(1135, 370, 70, 70);
    mFeedbackGainR5Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackGainR5Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mFeedbackGainR5Slider.setRange(audioParam->range.start, audioParam->range.end);
    mFeedbackGainR5Slider.setValue(*audioParam);
    mFeedbackGainR5Slider.addListener(this);
    addAndMakeVisible(mFeedbackGainR5Slider);
    mFeedbackGainR5Slider.setTextValueSuffix("dB");
    mFeedbackGainR5Slider.setNumDecimalPlacesToDisplay(1);

}

SamPPFinalMultiDelayAudioProcessorEditor::~SamPPFinalMultiDelayAudioProcessorEditor()
{
}

//==============================================================================
void SamPPFinalMultiDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("Multi-Delay", 530, 30, 200, 50, juce::Justification::centred, 1);
    
    g.setFont (20.0f);
    g.drawFittedText ("Left Delay Mix", 170, 20, 200, 50, juce::Justification::centred, 1);
    g.drawFittedText ("Right Delay Mix", 890, 20, 200, 50, juce::Justification::centred, 1);
    g.drawFittedText ("Left Delay Feedback", 170, 315, 200, 50, juce::Justification::centred, 1);
    g.drawFittedText ("Right Delay Feedback", 890, 315, 200, 50, juce::Justification::centred, 1);
    
    g.setFont (10.0f);
    g.drawFittedText ("Samuel Pak", 1180, 0, 100, 20, juce::Justification::centred, 1);
}

void SamPPFinalMultiDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void SamPPFinalMultiDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    auto& params = processor.getParameters();
    if (slider == &mDrySlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(0);
        *audioParam = mDrySlider.getValue();
        DBG("Wet Slider Changed");
    } else if (slider == &mWetSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(1);
        *audioParam = mWetSlider.getValue();
        DBG("Wet Slider Changed");
    } else if (slider == &mDelayBPMSlider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(2);
        *audioParam = mDelayBPMSlider.getValue();
        DBG("BPM Slider Changed");
    } else if (slider == &mWetL1Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(3);
        *audioParam = mWetL1Slider.getValue();
        DBG("Wet L1 Changed");
    } else if (slider == &mWetL2Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(4);
        *audioParam = mWetL2Slider.getValue();
        DBG("Wet L2 Changed");
    } else if (slider == &mWetL3Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(5);
        *audioParam = mWetL3Slider.getValue();
        DBG("Wet L3 Changed");
    } else if (slider == &mWetL4Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(6);
        *audioParam = mWetL4Slider.getValue();
        DBG("Wet L4 Changed");
    } else if (slider == &mWetL5Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(7);
        *audioParam = mWetL5Slider.getValue();
        DBG("Wet L5 Changed");
    } else if (slider == &mWetR1Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(8);
        *audioParam = mWetR1Slider.getValue();
        DBG("Wet R1 Changed");
    } else if (slider == &mWetR2Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(9);
        *audioParam = mWetR2Slider.getValue();
        DBG("Wet R2 Changed");
    } else if (slider == &mWetR3Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(10);
        *audioParam = mWetR3Slider.getValue();
        DBG("Wet R3 Changed");
    } else if (slider == &mWetR4Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(11);
        *audioParam = mWetR4Slider.getValue();
        DBG("Wet R4 Changed");
    } else if (slider == &mWetR5Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(12);
        *audioParam = mWetR5Slider.getValue();
        DBG("Wet R5 Changed");
    } else if (slider == &mFeedbackGainL1Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(13);
        *audioParam = mFeedbackGainL1Slider.getValue();
        DBG("Feedback Gain L1 Changed");
    } else if (slider == &mFeedbackGainL2Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(14);
        *audioParam = mFeedbackGainL2Slider.getValue();
        DBG("Feedback Gain L2 Changed");
    } else if (slider == &mFeedbackGainL3Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(15);
        *audioParam = mFeedbackGainL3Slider.getValue();
        DBG("Feedback Gain L3 Changed");
    } else if (slider == &mFeedbackGainL4Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(16);
        *audioParam = mFeedbackGainL4Slider.getValue();
        DBG("Feedback Gain L4 Changed");
    } else if (slider == &mFeedbackGainL5Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(17);
        *audioParam = mFeedbackGainL5Slider.getValue();
        DBG("Feedback Gain L5 Changed");
    } else if (slider == &mFeedbackGainR1Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(18);
        *audioParam = mFeedbackGainR1Slider.getValue();
        DBG("Feedback Gain R1 Changed");
    } else if (slider == &mFeedbackGainR2Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(19);
        *audioParam = mFeedbackGainR2Slider.getValue();
        DBG("Feedback Gain R2 Changed");
    } else if (slider == &mFeedbackGainR3Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(20);
        *audioParam = mFeedbackGainR3Slider.getValue();
        DBG("Feedback Gain R3 Changed");
    } else if (slider == &mFeedbackGainR4Slider) {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(21);
        *audioParam = mFeedbackGainR4Slider.getValue();
        DBG("Feedback Gain R4 Changed");
    } else {
        juce::AudioParameterFloat* audioParam = (juce::AudioParameterFloat*)params.getUnchecked(22);
        *audioParam = mFeedbackGainR5Slider.getValue();
        DBG("Feedback Gain R5 Changed");
    }
}
