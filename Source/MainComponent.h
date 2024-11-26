/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "MusicLibrary.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    
private:
    //==============================================================================
    // Your private member variables go here...
     
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 
    DJAudioPlayer player1{formatManager};
    WaveformDisplay waveformDisplay1{ formatManager,thumbCache};
    
    DJAudioPlayer player2{formatManager};
    WaveformDisplay waveformDisplay2{ formatManager,thumbCache };
    DeckGUI deckGUI1{ &player1,&waveformDisplay1, formatManager, thumbCache };
    DeckGUI deckGUI2{ &player2,&waveformDisplay2, formatManager, thumbCache };
    MusicLibrary musicLibrary{ &deckGUI1, &deckGUI2 };
    MixerAudioSource mixerSource; 
    
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
