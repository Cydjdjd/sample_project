/*
  ==============================================================================

    DeckControl.cpp
    Created: 14 Feb 2023 4:26:42pm
    Author:  fooch

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckControl.h"
#include <string>
//==============================================================================
DeckControl::DeckControl(DJAudioPlayer* _player, 
                         AudioFormatManager& _formatManager,
                         AudioThumbnailCache& cacheToUse) 
                         : player(_player),
                           formatManager(_formatManager)
                           
{
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    value = 0;
    //make completeRewindButton visible
    addAndMakeVisible(completeRewindButton);
    //make rewind button visible
    addAndMakeVisible(rewindButton);
    //make forward button visible
    addAndMakeVisible(forwardButton);
    //make completeForwardButton visible
    addAndMakeVisible(completeForwardButton);
    //make input box visible
    addAndMakeVisible(input2);
    //add completeRewindButton listener
    completeRewindButton.addListener(this);
    //add rewindButton listener
    rewindButton.addListener(this);
    //add forwardButton listener
    forwardButton.addListener(this);
    //add completeForwardButton listener
    completeForwardButton.addListener(this);
    //add input box listener
    input2.addListener(this);
}

DeckControl::~DeckControl()
{
}

void DeckControl::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background
    //set colour of button to darkblue
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    getLookAndFeel().setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkblue);
    //set input box background to darkblue
    getLookAndFeel().setColour(juce::TextEditor::backgroundColourId, juce::Colours::darkblue);
    //set words of input box to white
    getLookAndFeel().setColour(juce::TextEditor::textColourId, juce::Colours::white);
    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    g.setColour(Colours::white);
    g.setFont(14.0f);
    
}

void DeckControl::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //divide height of deckControl to 3
    double rowH = getHeight() / 3;
    //set position of completeRewindButton
    completeRewindButton.setBounds(0, 0, getWidth()/2, rowH);
    //set position of rewindButton
    rewindButton.setBounds(0, rowH, getWidth()/2, rowH);
    //set position of forwardButton
    forwardButton.setBounds(getWidth()/2, rowH, getWidth()/2, rowH);
    //set position of completeforwardButton
    completeForwardButton.setBounds(getWidth()/2, 0, getWidth()/2, rowH);
    //set position of input box
    input2.setBounds(0, rowH*2, getWidth(), rowH);
}

void DeckControl::buttonClicked(Button* button)
{   
    //when completeRewindButton is clicked
    if (button == &completeRewindButton)
    {
        std::cout << "completeRewindButton was clicked" << std::endl;
        //set position of audio to 0 
        player->setPosition(0);
    }
    // when rewind button is clicked
    if (button == &rewindButton)
    {
        std::cout << "rewindButton was clicked" << std::endl;
        //get current position of audio
        double currentPosition = player->getCurrentPosition();
        //set position of audio to rewind by amount indicated in input box
        player->setPosition(currentPosition-value);
    }
    //when completeforwardbutton is clicked
    if (button == &completeForwardButton)
    {
        std::cout << "completeForwardButton was clicked" << std::endl;
        //get position at the end of audio track
        double finalPosition = player->getLengthInSeconds();
        //set position of audio to rewind by amount indicated in input box
        player->setPosition(finalPosition);
    }
    //when forwardButton is clicked
    if (button == &forwardButton)
    {
        std::cout << "forwardButton was clicked" << std::endl;
        //get current position of audio player
        double currentPosition = player->getCurrentPosition();
        std::cout << currentPosition << std::endl;
        std::cout << value << std::endl;
        //forward audio player position by value put into input box
        player->setPosition(currentPosition + value);
    }
}
//when text is put into text editor
void DeckControl::textEditorTextChanged(TextEditor&) {
        //assign value variable to input text that is put into input box        
        value = input2.getText().getDoubleValue();
        
}


