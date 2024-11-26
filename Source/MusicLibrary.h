/*
  ==============================================================================

    MusicLibrary.h
    Created: 6 Feb 2023 1:54:09pm
    Author:  fooch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include <fstream>;
#include "DeckGUI.h"
//==============================================================================
/*
*/
class MusicLibrary  : public juce::Component,
                      public TableListBoxModel,
                      public Button::Listener,
                      public TextEditor::Listener
{
public:
    //MusicLibrary constructor
    MusicLibrary(DeckGUI* _deckGUI1,
        DeckGUI* _deckGUI2);
    //MusicLibrary destructor
    ~MusicLibrary() override;
    //paint function initialisation
    void paint (Graphics&) override;
    //resized function initialisation
    void resized() override;
    //get no of rows
    int getNumRows() override;
    //paintRowBackGround initialisation
    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height, 
        bool rowIsSelected) override;
    //paintCell function initialisation
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;
    //refreshComponentForCell function initialisation
    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;
    //buttonClicked initialisation
    void buttonClicked(Button* button) override;
    //getSource initialisation
    File getSource();
    //loadVectors initialisation
    void loadVectors();
    //file 1 initialisation
    std::fstream file1;
    //file 2 initialisation
    std::fstream file2;
    //resourceFile1 initialisation
    File resourceFile1;
    //resourceFile2 initialisation
    File resourceFile2;
    //inputFile1 initialisation
    FileInputStream inputFile1;
    //inputFile2 initialisation
    FileInputStream inputFile2;
    //outputFile1 initialisation
    FileOutputStream outputFile1;
    //outputFile2 initialisation
    FileOutputStream outputFile2;
    int count;
    //nthOccurence initialisation
    int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
    //deckGUI1 initialisation
    DeckGUI* deckGUI1;
    //deckGUI2 initialisation
    DeckGUI* deckGUI2;
    //textEditorTextChanged initialisation
    void textEditorTextChanged(TextEditor &);
    //saveTracks initialisation
    void saveTracks();
private:
    //tableComponent initialisation
    TableListBox tableComponent;
    //trackTItles initialisation
    std::vector<std::string> trackTitles;
    //trackTitles2 initialisation
    std::vector<std::string> trackTitles2;
    //absolutePaths initialisation
    std::vector<std::string> absolutePaths;
    //searchButton initialisation
    TextButton searchButton{ "Search" };
    //input1 initialisation
    TextEditor input1;
    //fchoose initialisation
    FileChooser fChooser{ "Select a file..." };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibrary)
};
