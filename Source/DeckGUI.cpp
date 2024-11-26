/*
  ==============================================================================

	DeckGUI.cpp
	Created: 13 Mar 2020 6:44:48pm
	Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
	WaveformDisplay* _waveformDisplay,
	AudioFormatManager& formatManagerToUse,
	AudioThumbnailCache& cacheToUse
) : player(_player),
waveformDisplay(_waveformDisplay),
deckControl(_player, formatManagerToUse, cacheToUse)

{	
	//set thumb of rotary slider to orange
	getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::orange);
	//make play button visible
	addAndMakeVisible(playButton);
	//make deckControl visible
	addAndMakeVisible(deckControl);
	//make stopButton visible
	addAndMakeVisible(stopButton);
	//make loadButton visible
	addAndMakeVisible(loadButton);
	//make volSlider visible
	addAndMakeVisible(volSlider);
	//make speedSlider visible
	addAndMakeVisible(speedSlider);
	//make posSlider visible
	addAndMakeVisible(posSlider);
	//make waveformDisplay visible
	addAndMakeVisible(waveformDisplay);

	//add listener to playButton
	playButton.addListener(this);
	//add listener to stopButton
	stopButton.addListener(this);
	//add listener to loadButton
	loadButton.addListener(this);
	//add listener to volSlider 
	volSlider.addListener(this);
	//add listener to speedSlider
	speedSlider.addListener(this);
	//add listener to posSlider
	posSlider.addListener(this);
	//add listener to volSlider
	volSlider.setRange(0.0, 1.0);
	//add listener to speedSlider
	speedSlider.setRange(0.0, 100.0);
	//add listener to posSlider
	posSlider.setRange(0.0, 1.0);

	startTimer(500);


}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::paint(Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(Colours::white);
	g.setFont(14.0f);
	
}

void DeckGUI::resized()
{	
	//split height of application into 18 parts
	double rowH = getHeight() / 18;
	//set position of playButton
	playButton.setBounds(0, 0, getWidth() /3, rowH * 5/3+2);
	//set position of loadButton
	loadButton.setBounds(0, rowH * 5 / 3, getWidth() / 3, rowH * 5 / 3 + 2);
	//set position of stopButton
	stopButton.setBounds(0, rowH*10/3, getWidth() / 3, rowH * 5/3+2);
	//set position of volSlider
	volSlider.setBounds(getWidth() / 2, rowH * 14, getWidth()/4, rowH*2.25);
	//set position of speedSlider
	speedSlider.setBounds(getWidth()*3/4, rowH * 14, getWidth() / 4, rowH*2.25);
	//set position of posSlider
	posSlider.setBounds(getWidth()*5/8, rowH * 16.25, getWidth() / 4, rowH*2.25);
	//set position of waveformDisplay
	waveformDisplay->setBounds(getWidth() / 3, 0, getWidth()*2 / 3, rowH * 5+2);
	//set position of deckCOntrol
	deckControl.setBounds(0, rowH * 14, getWidth() / 2, rowH * 4.5);
	//set style of volSlider to rotary
	volSlider.setSliderStyle(Slider::Rotary);
	//set style of speedSlider to rotary
	speedSlider.setSliderStyle(Slider::Rotary);
	//set style of posSlider to rotary
	posSlider.setSliderStyle(Slider::Rotary);
	//remove text box of volSlider
	volSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	//remove text box of speedSlider 
	speedSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	//remove text box of posSlider
	posSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	

}
//when specific button is clicked
void DeckGUI::buttonClicked(Button* button)
{	
	//when button is playButton
	if (button == &playButton)
	{
		std::cout << "Play button was clicked " << std::endl;
		//start playing audio on audio player
		player->start();
	}
	//when button is stopButton
	if (button == &stopButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		//stop playing audio on audio player
		player->stop();

	}
	//when button is loadButton
	if (button == &loadButton)
	{	
		//allow the option to select files
		auto fileChooserFlags =
			FileBrowserComponent::canSelectFiles;
		fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
			{	
				//get chosen result and load URL into player
				player->loadURL(URL{ chooser.getResult() });
				//get chosen result and load URL into waveform
				waveformDisplay->loadURL(URL{ chooser.getResult() });
			});
	}
	// if (button == &loadButton)
	// {
	//     FileChooser chooser{"Select a file..."};
	//     if (chooser.browseForFileToOpen())
	//     {
	//         player->loadURL(URL{chooser.getResult()});
	//         waveformDisplay.loadURL(URL{chooser.getResult()});

	//     }


	// }
}
//when slider value is changed
void DeckGUI::sliderValueChanged(Slider* slider)
{	
	//when slider is the volSlider
	if (slider == &volSlider)
	{	
		//set audio player to adjust volume by the slider value
		player->setGain(slider->getValue());
	}

	//when slider is the speedSlider
	if (slider == &speedSlider)
	{	
		//set audio player to adjust speed by the slider value
		player->setSpeed(slider->getValue());
	}
	
	//when slider is the posSlider
	if (slider == &posSlider)
	{	
		//set audio player to adjust position by the slider value
		player->setPositionRelative(slider->getValue());
	}

}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
	std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
	return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
	std::cout << "DeckGUI::filesDropped" << std::endl;
	if (files.size() == 1)
	{
		player->loadURL(URL{ File{files[0]} });
	}
}

void DeckGUI::timerCallback()
{
	//std::cout << "DeckGUI::timerCallback" << std::endl;
	waveformDisplay->setPositionRelative(
		player->getPositionRelative());
}




