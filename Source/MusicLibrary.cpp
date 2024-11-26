/*
  ==============================================================================

	MusicLibrary.cpp
	Created: 6 Feb 2023 1:54:09pm
	Author:  fooch

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MusicLibrary.h"
#include <fstream>;
#include <string>
#include <sstream>
//==============================================================================
MusicLibrary::MusicLibrary(DeckGUI* _deckGUI1,
	DeckGUI* _deckGUI2)
	:deckGUI1(_deckGUI1),
	deckGUI2(_deckGUI2),
	resourceFile1(getSource().getFullPathName().toStdString() + "/file1.txt"),
	resourceFile2(getSource().getFullPathName().toStdString() + "/file2.txt"),
	inputFile1(resourceFile1),
	inputFile2(resourceFile2),
	outputFile1(resourceFile1),
	outputFile2(resourceFile2)
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	//set input box background colour to dark blue
	getLookAndFeel().setColour(juce::TextEditor::backgroundColourId, juce::Colours::darkblue);
	//set input box text colour to white
	getLookAndFeel().setColour(juce::TextEditor::textColourId, juce::Colours::white);
	//set up 4 columns for table components
	tableComponent.getHeader().addColumn("Track title", 1, 200);
	tableComponent.getHeader().addColumn("", 2, 200);
	tableComponent.getHeader().addColumn("", 3, 200);
	tableComponent.getHeader().addColumn("", 4, 100);
	tableComponent.setModel(this);
	//make tableComponent visible
	addAndMakeVisible(tableComponent);
	//make searchButton visible
	addAndMakeVisible(searchButton);
	//make input box visible
	addAndMakeVisible(input1);
	//add listener to searchButton
	searchButton.addListener(this);
	//add listener to input box
	input1.addListener(this);
	//load vectors when application starts
	loadVectors();

}

MusicLibrary::~MusicLibrary()
{
}

void MusicLibrary::paint(juce::Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(14.0f);
	g.drawText("MusicLibrary", getLocalBounds(),
		juce::Justification::centred, true);   // draw some placeholder text
}

void MusicLibrary::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	//set position of tableComponent
	tableComponent.setBounds(0, 20, getWidth(), getHeight() - 20);
	//set position of searchButton
	searchButton.setBounds(0, 0, getWidth() / 2, 20);
	//set position of input box
	input1.setBounds(getWidth() / 2, 0, getWidth() / 2, 20);
}

int MusicLibrary::getNumRows() {
	return trackTitles.size();
}
void MusicLibrary::paintRowBackground(Graphics& g,
	int rowNumber,
	int width,
	int height,
	bool rowIsSelected)
{	//fill row colour to be darkorange regardless of whether it is selected
	if (rowIsSelected)
	{
		g.fillAll(juce::Colours::darkorange);
	}
	else {
		g.fillAll(juce::Colours::darkorange);
	}

}
void MusicLibrary::paintCell(Graphics& g,
	int rowNumber,
	int columnId,
	int width,
	int height,
	bool rowIsSelected)
{
	/*std::cout << "paintcell called" << std::endl;*/
	g.setFillType(juce::Colours::white);
	//draw text of tableCompoenent
	g.drawText(trackTitles[rowNumber], 2, 0, width - 4, height, Justification::centredLeft, true);
}

Component* MusicLibrary::refreshComponentForCell(int rowNumber,
	int columnId,
	bool isRowSelected,
	Component* existingComponentToUpdate)
{
	std::cout << "refreshComponentForCell call" << std::endl;
	//draw buttons to load audio into deck 1
	if (columnId == 2)
	{
		if (existingComponentToUpdate == nullptr)
		{
			TextButton* btn = new TextButton("Load into deck 1");
			String id{ std::to_string(columnId) + std::to_string(rowNumber) };
			std::cout << std::to_string(rowNumber) << std::endl;
			btn->setComponentID(id);
			btn->addListener(this);
			existingComponentToUpdate = btn;
		}
	}
	//draw buttons to load audio into deck 2
	if (columnId == 3)
	{
		if (existingComponentToUpdate == nullptr)
		{
			TextButton* btn = new TextButton("Load into deck 2");
			String id{ std::to_string(columnId) + std::to_string(rowNumber) };
			std::cout << std::to_string(rowNumber) << std::endl;
			btn->setComponentID(id);
			btn->addListener(this);

			existingComponentToUpdate = btn;
		}
	}
	//draw buttons to selete audio from music library
	if (columnId == 4) {
		if (existingComponentToUpdate == nullptr)
		{
			TextButton* btn = new TextButton("Delete");
			String id{ std::to_string(columnId) + std::to_string(rowNumber) };
			std::cout << std::to_string(rowNumber) << std::endl;
			btn->setComponentID(id);
			btn->addListener(this);

			existingComponentToUpdate = btn;
		}
	}
	return existingComponentToUpdate;
}
//function to supplement nth Occurrence of string
int MusicLibrary::nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
	size_t  pos = -1;
	int     cnt = 0;

	while (cnt != nth)
	{
		pos += 1;
		pos = str.find(findMe, pos);
		if (pos == std::string::npos)
			return -1;
		cnt++;
	}
	return pos;
}
//function to load trackTitles vector
void MusicLibrary::loadVectors() {
	Array<File> FileList;


	std::cout << inputFile1.openedOk() << std::endl;
	//when inputFile1 is opened
	if (inputFile1.openedOk()) {
		int start = 4;
		int j = 1;
		std::string delimiter = ",";
		//read entire file
		std::string s = inputFile1.readEntireStreamAsString().toStdString();
		//if s is not an empty string
		if (s != "") {
			//run for loop to second last character
			for (int i = 0; i < s.length() - 1; i++) {
				/*std::cout << start << std::endl;
				std::cout << i << std::endl;
				std::cout << s[i] << std::endl;*/
				//when , is detected
				if (s[i] == ',') {
					//set value of z
					int z = j - 2;
					//when tracktitles is empty or when tracktitles element is not equal to string extracted
					if (trackTitles.empty() || (!trackTitles.empty() && (trackTitles[z] != s.substr(start, i - start))))
					{	
						//push string into trackTitles
						trackTitles.push_back(s.substr(start, i - start));
						/*std::cout << s.substr(start, i - start) << std::endl;*/
					}
					//set value of start
					start = nthOccurrence(s, ",", j) + 5;
					//increment j by 1
					j++;
					//when trackTitles size is 16, stop the loop
					if (trackTitles.size() == 16) {
						break;
					}
				}
			}
		}
	}
	//when inputFile2 is opened
	if (inputFile2.openedOk()) {
		int start = 3;
		int j = 1;
		std::string delimiter = ",";
		//read entire file
		std::string s = inputFile2.readEntireStreamAsString().toStdString();
		//if s is not an empty string
		if (s != "") {
			//run for loop to second last character
			for (int i = 0; i < s.length() - 1; i++) {
				/*std::cout << start << std::endl;
				std::cout << i << std::endl;
				std::cout << s[i] << std::endl;*/
				//when , is detected
				if (s[i] == ',') {
					//set value of z
					int z = j - 2;
					//if absolutePaths is empty or when it is not empty and not equal to substring
					if (absolutePaths.empty() || (!absolutePaths.empty() && (absolutePaths[z] != s.substr(start, i - start)))) {
						//push substring into absolutePaths
						absolutePaths.push_back(s.substr(start, i - start));
						/*std::cout << s.substr(start, i - start) << std::endl;*/
					}
					//set start value
					start = nthOccurrence(s, ",", j) + 5;
					//increment j
					j++;
					//when absolutePaths size is equal to 16,break the loop
					if (absolutePaths.size() == 16) {
						break;
					}
				}
			}

		}

	}
	//update tableComponent
	tableComponent.updateContent();
}
//when button is clicked
void MusicLibrary::buttonClicked(Button* button)
{

	//when trackTitles is not empty and button clicked is not searchbutton
	if (!trackTitles.empty() && button != &searchButton) {
		//assign columnId
		std::string columnId = button->getComponentID().toStdString()[0] + "";
		//assign id
		int id = std::stoi(button->getComponentID().toStdString().substr(1, button->getComponentID().toStdString().length() - 1));
		/*std::cout << id << std::endl;
		std::cout << "MusicLibrary::buttonClicked " << trackTitles[id] << std::endl;*/
	}
	//when searchButton is clicked
	if (button == &searchButton)
	{
		std::cout << "searchButton was clicked" << std::endl;
		//allow multiple files to be opened
		fChooser.browseForMultipleFilesToOpen();
		//get results from fChooser
		Array<File> FileList = fChooser.getResults();
		//run for loop
		for (File fileName : FileList) {
			//assign iterator
			std::vector<std::string>::iterator it = std::find(trackTitles.begin(), trackTitles.end(), fileName.getFileNameWithoutExtension().toStdString());
			//when filename selected is not in trackTitles 
			if ((it == trackTitles.end() && fileName != FileList[0]) || trackTitles.empty()) {
				std::cout << fileName.getFileNameWithoutExtension().toStdString() << std::endl;
				//push chosen filename into trackTitles vector
				trackTitles.push_back(fileName.getFileNameWithoutExtension().toStdString());
				//push absolutePath into absolutePaths vector
				absolutePaths.push_back(fileName.getFullPathName().toStdString());
				//write fileName into file1.txt
				outputFile1.writeText(fileName.getFileNameWithoutExtension().toStdString() + "," + "\n", true, true, nullptr);
				outputFile1.setNewLineString("\n");
				outputFile1.flush();
				//write absolute path into file2.txt
				outputFile2.writeText(fileName.getFullPathName().toStdString() + "," + "\n", true, true, nullptr);
				outputFile2.setNewLineString("\n");
				outputFile2.flush();
			}


		}
		//update tableComponent
		tableComponent.updateContent();

	}
	//when button clicked is not searchButton
	if (button != &searchButton) {
		//assign columnId
		char columnId = button->getComponentID().toStdString()[0];
		//assign id
		int id = std::stoi(button->getComponentID().toStdString().substr(1, button->getComponentID().toStdString().length() - 1));
		std::cout << button->getComponentID().toStdString()[0] << std::endl;
		std::cout << button->getComponentID().toStdString().substr(1, button->getComponentID().toStdString().length() - 1) << std::endl;
		//run for loop
		for (int i = 0; i < trackTitles.size(); i++) {
			//if file2 is opened or if trackTitles with index of id is equal to trackTitles with index of i
			if (trackTitles[id] == trackTitles[i]) {
				std::cout << trackTitles[id] << std::endl;
				std::cout << trackTitles[i] << std::endl;
				std::cout << sizeof(trackTitles) / sizeof(File) << std::endl;
				//assign absolutePath
				std::string absolutePath = absolutePaths[i];

				std::cout << absolutePath << std::endl;
				//get file with absolutePath
				File g(absolutePath);
				//if it is 2nd column loadURL into player and waveformDisplay of deckGUI1
				if (columnId == '2') {
					deckGUI1->player->loadURL(URL{ g });
					deckGUI1->waveformDisplay->loadURL(URL{ g });
				}
				//if it is 3rd column loadURL into player and waveformDisplay of deckGUI2
				if (columnId == '3') {
					deckGUI2->player->loadURL(URL{ g });
					deckGUI2->waveformDisplay->loadURL(URL{ g });
				}
				//if it is 4th column delete audio from music library
				if (columnId == '4') {
					trackTitles.erase(trackTitles.begin() + i);
					absolutePaths.erase(absolutePaths.begin() + i);
					tableComponent.updateContent();
				}
			}
		}


	}
}
//get root URL of source folder
File MusicLibrary::getSource()
{


	auto start = File::getSpecialLocation(File::currentExecutableFile);
	while (start.exists() && !start.isRoot() && start.getFileName() != "Builds")
		start = start.getParentDirectory();

	if (start.getFileName() == "Builds")
	{
		auto resources = start.getSiblingFile("Resources");
		if (resources.isDirectory())
			return resources;

		auto sources = start.getSiblingFile("Source");
		if (sources.isDirectory())
			return sources;
	}
}
//when text in searchbar is changed
void MusicLibrary::textEditorTextChanged(TextEditor&)
{
	//run for loop
	for (int i = 0; i < trackTitles.size(); i++) {
		//when text typed into search bar is changed
		if (input1.getText().toStdString() == trackTitles[i]) {
			//trackTitles2 is not empty
			if (!trackTitles2.empty()) {
				//clear trackTitles2
				trackTitles2.clear();

			}
			//run for loop
			for (int j = 0; j < trackTitles.size(); j++) {
				//push tracktitle into trackTitles2 vector
				trackTitles2.push_back(trackTitles[j]);
			}
			//clear trackTitles
			trackTitles.clear();
			//push trackTitles2 with element of index i into trackTitles
			trackTitles.push_back(trackTitles2[i]);
		}
		else {
			//when trackTitles2 is not empty
			if (!trackTitles2.empty()) {
				//clear trackTitles
				trackTitles.clear();
				//run for loop
				for (int z = 0; z < trackTitles2.size(); z++) {
					//push element in trackTitles2 into trackTitles
					trackTitles.push_back(trackTitles2[z]);
				}
			}
		}
	}
	//update tableComponent
	tableComponent.updateContent();

}
