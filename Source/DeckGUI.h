/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "DeckControl.h"
//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
                   
{
public:
    //DeckGUI constructor
    DeckGUI(DJAudioPlayer* _player,
        WaveformDisplay* _waveformDisplay,
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse
    );
    //DeckGUI destructor
    ~DeckGUI();
    //paint function initialisation
    void paint (Graphics&) override;
    //resized function initialisation
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;
    //Files drag function
    bool isInterestedInFileDrag (const StringArray &files) override;
    //filesDropped function initialisation
    void filesDropped (const StringArray &files, int x, int y) override; 
    //timerCallback initialisation
    void timerCallback() override; 
    //waveformDisplay initialisation
    WaveformDisplay* waveformDisplay;
    //player initialisation
    DJAudioPlayer* player;
private:
    //playButton initialisation
    TextButton playButton{"PLAY"};
    //stopButton initialisation
    TextButton stopButton{"STOP"};
    //loadButton initialisation
    TextButton loadButton{"LOAD"};
    //volSlider initialisation
    Slider volSlider; 
    //speedSlider initialisation
    Slider speedSlider;
    //posSlider initialisation
    Slider posSlider;
    //fchooser initialisation
    FileChooser fChooser{"Select a file..."};
    //deckControl initialisation
    DeckControl deckControl;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
