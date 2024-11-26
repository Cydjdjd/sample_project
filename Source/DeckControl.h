/*
  ==============================================================================

    DeckControl.h
    Created: 14 Feb 2023 4:26:42pm
    Author:  fooch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
//==============================================================================
/*
*/
class DeckControl  : public Component,
                     public Button::Listener,
                     public TextEditor::Listener
{
public:
    //DeckControl constructor
    DeckControl(DJAudioPlayer* _player,
        AudioFormatManager& _formatManager,
        AudioThumbnailCache& cacheToUse);
    //DeckCOntrol destructor
    ~DeckControl() override;
    //paint function initialisation
    void paint (juce::Graphics&) override;
    //resized function initialisation
    void resized() override;
    //buttonClicked function initialisation
    void buttonClicked(Button* button) override;
    //function for when input box text is changed
    void textEditorTextChanged(TextEditor&);
    //value to forward and rewind by
    double value;
private:
    //rewindButton initialisation
    TextButton rewindButton{ "Rewind" };
    //forwardButton
    TextButton forwardButton{ "Forward" };
    //completeRewindButton initialisation
    TextButton completeRewindButton{ "completeRewind" };
    //completeForwardButton initialisation
    TextButton completeForwardButton{ "completeForward" };
    //input box initialisation
    TextEditor input2;
    //audio player initialisation
    DJAudioPlayer* player;
    //formatManager initialisation
    AudioFormatManager& formatManager;
    //transportSource initialisation
    AudioTransportSource transportSource;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckControl)
};
